# Archivo: nodo_iot.py

class NodoIoT:
    def __init__(self, id_dispositivo, ip, ubicacion):
        # Atributos compartidos por cualquier dispositivo en la red
        self.id_dispositivo = id_dispositivo
        self.ip = ip
        self.ubicacion = ubicacion
        self.conectado = False

    def conectar(self):
        # Método base
        self.conectado = True
        print(f"[{self.id_dispositivo}] Conectado a la red ({self.ip}) en {self.ubicacion}.")

    def enviar_telemetria(self):
        # Polimorfismo: Obliga a las subclases a sobrescribir este método
        raise NotImplementedError("Las subclases deben implementar la telemetría específica.")