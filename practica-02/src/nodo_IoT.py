# nodo_iot.py

class NodoIoT:
    def __init__(self, id_dispositivo, ip, ubicacion):
        # Atributos compartidos por todos los nodos
        self.id_dispositivo = id_dispositivo
        self.ip = ip
        self.ubicacion = ubicacion
        self.conectado = False  # Por defecto inicia desconectado[cite: 1]

    def conectar(self):
        """Simula o ejecuta la conexión del nodo a la red."""
        self.conectado = True
        print(f"[{self.id_dispositivo}] Conectado a la red web en IP: {self.ip}")

    def enviar_telemetria(self):
        """Método base que será sobrescrito por las clases hijas[cite: 1]."""
        pass