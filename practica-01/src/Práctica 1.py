#!/usr/init/env python3
"""
Panel HMI SCADA con Comunicación Serial para ESP32-S3
Controla: Ventilador (Pin 3 - Digital ON/OFF), LED de Potencia (Pin 21 - PWM)
Lee: Sensor DHT11 (Pin 12) y Sensor LDR (Pin 4)
"""

import os
import json
import threading
import time
import serial

# ==============================================================================
# CONFIGURACIÓN SERIAL (Modifica 'COM9' por tu puerto correspondiente)
# ==============================================================================
PUERTO_SERIAL = 'COM9'  # En Linux/Mac suele ser '/dev/ttyUSB0' o '/dev/cu.usbserial-xxx'
BAUD_RATE = 115200

try:
    ser = serial.Serial(PUERTO_SERIAL, BAUD_RATE, timeout=1)
    time.sleep(2) # Esperar a que se establezca la conexión
except Exception as e:
    print(f"[⚠️ ERROR CRÍTICO] No se pudo abrir el puerto serie: {e}")
    exit(1)

# Variables globales compartidas para almacenar la última lectura de la ESP32
datos_hardware = {
    "temp": 0.0,
    "ldr": 0
}
serial_lock = threading.Lock()

# Lista global para simular un registrador de eventos (Event Logger) tipo SCADA/HMI
historial_eventos = []

def registrar_evento(mensaje: str):
    """Agrega un evento al historial y mantiene solo los últimos 5."""
    historial_eventos.append(mensaje)
    if len(historial_eventos) > 5:
        historial_eventos.pop(0)

def limpiar_pantalla():
    """Limpia la terminal según el sistema operativo."""
    os.system('cls' if os.name == 'nt' else 'clear')


# ==============================================================================
# HILO DE ESCUCHA SERIAL (BACKGROUND)
# ==============================================================================
def leer_serial_background():
    """Escucha continuamente los paquetes JSON enviados por la ESP32-S3."""
    global datos_hardware
    while True:
        try:
            if ser.in_waiting > 0:
                linea = ser.readline().decode('utf-8').strip()
                if linea.startswith("{") and linea.endswith("}"):
                    data = json.loads(linea)
                    with serial_lock:
                        if "temp" in data:
                            datos_hardware["temp"] = float(data["temp"])
                        if "ldr" in data:
                            datos_hardware["ldr"] = int(data["ldr"])
        except Exception:
            pass
        time.sleep(0.01)

# Iniciar hilo de lectura en segundo plano
hilo_serial = threading.Thread(target=leer_serial_background, daemon=True)
hilo_serial.start()


# ==============================================================================
# 1. CLASE ACTUADOR (Vinculada físicamente al ESP32)
# ==============================================================================
class Actuador:
    def __init__(self, nombre: str, tipo_control: str):
        self.nombre = nombre
        self.tipo_control = tipo_control # "ventilador" (digital) o "led" (pwm)
        self.rango_min = 0.0
        self.rango_max = 100.0
        self.estado = False
        self.punto_operacion = 0.0       # Porcentaje (0 - 100%) para LED, o Estado para Ventilador

    def encender(self):
        self.estado = True
        self.punto_operacion = 100.0
        self._enviar_comando_hardware()
        if self.tipo_control == "ventilador":
            registrar_evento(f"[+] {self.nombre} -> ENCENDIDO")
        else:
            registrar_evento(f"[+] {self.nombre} -> ENCENDIDO (100%)")

    def apagar(self):
        self.estado = False
        self.punto_operacion = 0.0
        self._enviar_comando_hardware()
        if self.tipo_control == "ventilador":
            registrar_evento(f"[-] {self.nombre} -> APAGADO")
        else:
            registrar_evento(f"[-] {self.nombre} -> APAGADO (0%)")

    def ajustar(self, valor: float):
        if self.tipo_control == "ventilador":
            registrar_evento(f"[⚠️ ERROR] {self.nombre} es de tipo ON/OFF. Usa 'encender' o 'apagar'.")
            return

        if self.rango_min <= valor <= self.rango_max:
            self.punto_operacion = valor
            self.estado = valor > 0
            self._enviar_comando_hardware()
            registrar_evento(f"[⚙] {self.nombre} -> Ajustado al {self.punto_operacion:.1f}%")
        else:
            registrar_evento(f"[⚠️ ERROR] {self.nombre} -> Valor {valor}% fuera de rango (0% - 100%).")

    def _enviar_comando_hardware(self):
        """Envía el comando correspondiente por Serial a la ESP32."""
        comando_json = {}
        
        if self.tipo_control == "ventilador":
            # Envía booleano (true/false) para el pin digital del ventilador
            comando_json["fan_state"] = 1 if self.estado else 0
        elif self.tipo_control == "led":
            # Envía PWM (0-255) para el LED
            duty_cycle = int((self.punto_operacion / 100.0) * 255)
            comando_json["led_duty"] = duty_cycle
            
        try:
            ser.write((json.dumps(comando_json) + "\n").encode('utf-8'))
        except Exception as e:
            registrar_evento(f"[⚠ ERROR SERIAL] Fallo al enviar: {e}")

    def info(self) -> str:
        estado_str = "ON" if self.estado else "OFF"
        if self.tipo_control == "ventilador":
            return f"{self.nombre:<20} | Estado: {estado_str:<3}"
        else:
            return f"{self.nombre:<20} | Estado: {estado_str:<3} | Potencia: {self.punto_operacion:>5.1f}%"


# ==============================================================================
# 2. CLASE SENSOR (Vinculada al hardware real de la ESP32)
# ==============================================================================
class SensorReal:
    def __init__(self, nombre: str, variable_fisica: str, clave_medicion: str, unidad: str):
        self.nombre = nombre
        self.variable_fisica = variable_fisica
        self.clave_medicion = clave_medicion # "temp" o "ldr"
        self.unidad = unidad

    def leer_valor_actual(self) -> float:
        with serial_lock:
            valor = datos_hardware.get(self.clave_medicion, 0.0)
        
        lectura_str = f"{valor} {self.unidad}"
        registrar_evento(f"[📊 LECTURA REAL] {self.nombre}: {lectura_str}")
        return valor

    def info(self) -> str:
        with serial_lock:
            val_actual = datos_hardware.get(self.clave_medicion, 0.0)
        return f"{self.nombre:<20} | Var: {self.variable_fisica:<18} | Actual: {val_actual:>6.1f} {self.unidad}"


# ==============================================================================
# INTERFAZ HMI (TABLERO DE CONTROL)
# ==============================================================================
def mostrar_interfaz_hmi(actuadores, sensores):
    print("=" * 85)
    print("         PANEL HMI INDUSTRIAL (ESP32-S3) ")
    print("=" * 85)
    
    # 1. Sección de Actuadores
    print(" [ACTUADORES (Hardware ESP32)]")
    for key, act in actuadores.items():
        print(f"    ► [{key:<10}] {act.info()}")
    print("-" * 85)
    
    # 2. Sección de Sensores (Lecturas en tiempo real desde la ESP32)
    print(" [SENSORES FÍSICOS EN TIEMPO REAL]")
    for key, sen in sensores.items():
        print(f"    ► [{key:<11}] {sen.info()}")
    print("=" * 85)
    
    # 3. Sección de Registro de Eventos
    print(" [REGISTRO DE EVENTOS EN VIVO (SCADA)]")
    if not historial_eventos:
        print("    (Sin actividad reciente)")
    else:
        for ev in historial_eventos:
            print(f"    {ev}")
    print("=" * 85)
    
    # 4. Sección de Comandos
    print(" COMANDOS DISPONIBLES:")
    print("    • encender <ventilador/led>      (Ej: encender ventilador)")
    print("    • apagar <ventilador/led>        (Ej: apagar led)")
    print("    • ajustar <led> <val>            (Ej: ajustar led 75.5)")
    print("    • leer <temperatura/ldr>         (Ej: leer temperatura)")
    print("    • terminar                       (Finaliza la simulación)")
    print("=" * 85)


# ==============================================================================
# BUCLE INTERACTIVO PRINCIPAL
# ==============================================================================
def main():
    # Creación de Actuadores mapeados al hardware de la ESP32-S3
    ventilador = Actuador("Ventilador (Pin 3)", "ventilador")
    led_potencia = Actuador("LED Potencia (Pin 21)", "led")

    # Creación de Sensores mapeados a las lecturas reales
    sensor_temp = SensorReal(
        nombre="Sensor DHT11 (Pin 12)",
        variable_fisica="Temperatura Amb.",
        clave_medicion="temp",
        unidad="°C"
    )

    sensor_ldr = SensorReal(
        nombre="Sensor LDR (Pin 4)",
        variable_fisica="Intensidad Lumínica",
        clave_medicion="ldr",
        unidad="ADC"
    )

    actuadores = {
        "ventilador": ventilador,
        "led": led_potencia
    }
    
    sensores = {
        "temperatura": sensor_temp,
        "ldr": sensor_ldr
    }

    while True:
        limpiar_pantalla()
        mostrar_interfaz_hmi(actuadores, sensores)
        
        try:
            entrada = input("Ingrese comando >> ").strip()
        except (EOFError, KeyboardInterrupt):
            print("\n\n[+] Programa terminado.")
            break

        if not entrada:
            continue

        if entrada.lower() == "terminar":
            print("\n[+] Cerrando sistema... Apagando actuadores de seguridad.")
            try:
                # Apagar ambos pines de forma segura al salir
                ser.write((json.dumps({"fan_state": 0, "led_duty": 0}) + "\n").encode('utf-8'))
                ser.close()
            except:
                pass
            break

        partes = entrada.split()
        comando = partes[0].lower()

        if comando == "encender":
            if len(partes) < 2:
                registrar_evento("[⚠️ ERROR] Uso: encender <ventilador/led>")
                continue
            target = partes[1].lower()
            if target in actuadores:
                actuadores[target].encender()
            else:
                registrar_evento(f"[⚠️ ERROR] Actuador '{target}' no existe. Opciones: ventilador, led")

        elif comando == "apagar":
            if len(partes) < 2:
                registrar_evento("[⚠️ ERROR] Uso: apagar <ventilador/led>")
                continue
            target = partes[1].lower()
            if target in actuadores:
                actuadores[target].apagar()
            else:
                registrar_evento(f"[⚠️ ERROR] Actuador '{target}' no existe. Opciones: ventilador, led")

        elif comando == "ajustar":
            if len(partes) < 3:
                registrar_evento("[⚠️ ERROR] Uso: ajustar <led> <valor 0-100>")
                continue
            target = partes[1].lower()
            try:
                valor = float(partes[2])
                if target in actuadores:
                    actuadores[target].ajustar(valor)
                else:
                    registrar_evento(f"[⚠️ ERROR] Actuador '{target}' no existe.")
            except ValueError:
                registrar_evento("[⚠️ ERROR] El valor de ajuste debe ser numérico.")

        elif comando == "leer":
            if len(partes) < 2:
                registrar_evento("[⚠️ ERROR] Uso: leer <temperatura/ldr>")
                continue
            target = partes[1].lower()
            if target in sensores:
                sensores[target].leer_valor_actual()
            else:
                registrar_evento(f"[⚠️ ERROR] Sensor '{target}' no existe. Opciones: temperatura, ldr")

        else:
            registrar_evento(f"[⚠️ ERROR] Comando '{comando}' no reconocido.")
        
        time.sleep(0.1) # Pequeña pausa visual

if __name__ == "__main__":
    main()