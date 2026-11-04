# simulacion_invernadero.py
from nodos_invernadero import NodoSensor, NodoActuador
import time

# 1. Instanciación de los dispositivos del invernadero
sensor_temp = NodoSensor(id_dispositivo="SENS-TEMP", ip="192.168.1.10", ubicacion="Sector A", tipo_sensor="Temperatura")
actuador_ventilador = NodoActuador(id_dispositivo="ACT-VENT", ip="192.168.1.11", ubicacion="Sector A", tipo_actuador="Ventilador de extracción")
sensor_luz = NodoSensor(id_dispositivo="SENS-LUZ", ip="192.168.1.12", ubicacion="Techo", tipo_sensor="Luminosidad")

# 2. Configuración inicial y conexión simulada
sensor_temp.limite_alerta = 35.0
sensor_temp.conectar()
actuador_ventilador.conectar()
# sensor_luz se deja desconectado a propósito para probar el estado "Offline"

# Modificamos algunas lecturas y estados para la simulación
sensor_temp.actualizar_lectura(36.5)  # Disparará la alerta al superar el límite de 35.0
sensor_luz.actualizar_lectura(45.0)
actuador_ventilador.encender(potencia=200)

print("\n--- Ejecutando Bucle Polimórfico ---")

# Crea una lista mixta con tus dispositivos: red_iot = [sensor_temp, actuador_ventilador, sensor_luz][cite: 2].
red_iot = [sensor_temp, actuador_ventilador, sensor_luz]

# Recórrela con un bucle for invocando dispositivo.enviar_telemetria()[cite: 2]. 
for dispositivo in red_iot:
    # Cada objeto responderá según su clase automáticamente[cite: 2].
    dispositivo.enviar_telemetria()
    time.sleep(0.5)