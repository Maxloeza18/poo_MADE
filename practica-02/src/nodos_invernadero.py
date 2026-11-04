# nodos_invernadero.py
from nodo_iot import NodoIoT

class NodoSensor(NodoIoT):
    def __init__(self, id_dispositivo, ip, ubicacion, tipo_sensor):
        # Reutiliza el constructor del padre mediante la función super()[cite: 1]
        super().__init__(id_dispositivo, ip, ubicacion)
        self.tipo_sensor = tipo_sensor
        self.lectura_actual = 0.0
        # Protege sus límites con un atributo privado[cite: 1]
        self.__limite_alerta = 0.0  

    # Método de asignación (setter) que valida rangos numéricos reales[cite: 1]
    @property
    def limite_alerta(self):
        return self.__limite_alerta

    @limite_alerta.setter
    def limite_alerta(self, valor):
        # Validación: Evita que el límite se configure con valores absurdos (ej. humedad negativa)
        if isinstance(valor, (int, float)) and 0 <= valor <= 100:
            self.__limite_alerta = valor
        else:
            raise ValueError("Error: El límite debe estar entre 0 y 100.")

    def actualizar_lectura(self, valor):
        self.lectura_actual = valor
        if self.lectura_actual > self.__limite_alerta:
            print(f"¡ALERTA {self.id_dispositivo}! {self.tipo_sensor} excedió el límite: {self.lectura_actual}")

    def enviar_telemetria(self):
        # Sobrescribe el método base para mostrar la lectura actual[cite: 1]
        estado_red = "Online" if self.conectado else "Offline"
        print(f"[{self.id_dispositivo} | {estado_red}] {self.tipo_sensor}: {self.lectura_actual}")


class NodoActuador(NodoIoT):
    def __init__(self, id_dispositivo, ip, ubicacion, tipo_actuador):
        # Reutiliza el constructor del padre[cite: 1]
        super().__init__(id_dispositivo, ip, ubicacion)
        self.tipo_actuador = tipo_actuador
        # Atributos privados para el estado y potencia[cite: 1]
        self.__estado_activo = False 
        self.__potencia_pwm = 0      

    def encender(self, potencia):
        # Valida que el PWM esté en el rango de 8 bits del ESP32 (0-255)
        self.__estado_activo = True
        self.__potencia_pwm = max(0, min(255, potencia))
        print(f"[{self.id_dispositivo}] {self.tipo_actuador} ENCENDIDO (PWM: {self.__potencia_pwm}).")

    def apagar(self):
        self.__estado_activo = False
        self.__potencia_pwm = 0
        print(f"[{self.id_dispositivo}] {self.tipo_actuador} APAGADO.")

    def enviar_telemetria(self):
        # Sobrescribe el método base para mostrar el estado del relé o motor[cite: 1]
        estado_red = "Online" if self.conectado else "Offline"
        estado_hw = "ON" if self.__estado_activo else "OFF"
        print(f"[{self.id_dispositivo} | {estado_red}] {self.tipo_actuador}: {estado_hw} a {self.__potencia_pwm} PWM")