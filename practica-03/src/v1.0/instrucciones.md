Superclase NodoIoT.h
Para este primer commit, introducimos el archivo de cabecera include/NodoIoT.h. Este script actúa como la plantilla principal de la cual heredarán todos los componentes de hardware del invernadero (sensores de humedad, temperatura, relés, ventiladores).

Código del Script 1
C++
#ifndef NODO_IOT_H
#define NODO_IOT_H
#include <Arduino.h>

class NodoIoT {
protected:
    // Atributos protegidos: accesibles solo para esta clase y sus subclases hijas
    String idDispositivo;
    int pin;
    bool conectado;

public:
    // Constructor de la superclase
    NodoIoT(String id, int pinHardware) {
        idDispositivo = id;
        pin = pinHardware;
        conectado = false;
    }
    
    // Destructor virtual: Fundamental en C++ para evitar fugas de memoria 
    // al destruir objetos derivados usando punteros a la clase base.
    virtual ~NodoIoT() {}

    // Método virtual con implementación por defecto
    virtual void iniciar() {
        // La configuración del pinMode se definirá en las clases hijas
    }
    
    // Método virtual puro (Polimorfismo base)
    virtual void ejecutarAccion() = 0; 
};

#endif
¿Cómo funciona esta arquitectura base?
Uso de protected en lugar de private: Los atributos idDispositivo, pin y conectado se declaran como protegidos. Esto permite que las futuras subclases (como NodoSensorFisico) hereden estas variables y puedan interactuar con ellas directamente, pero las mantiene ocultas y seguras del resto del código externo (encapsulamiento).

El Constructor: Se encarga de inicializar el identificador en formato string y el pin físico del ESP32 donde se conectará el dispositivo. Por defecto, el estado de red inicia como false.

Métodos Virtuales (virtual): Al usar la palabra reservada virtual en iniciar(), permitimos que cada sensor o actuador futuro sobrescriba esta función con su propia lógica (por ejemplo, definir si el pin es INPUT o OUTPUT).

Método Virtual Puro (= 0): La línea virtual void ejecutarAccion() = 0; convierte a NodoIoT en una clase abstracta. Esto significa que no podemos instanciar un "NodoIoT" genérico en el código principal; sirve estrictamente como un molde. Cualquier clase hija que herede de ella estará obligada por el compilador de PlatformIO a crear su propia versión de ejecutarAccion() (ya sea para leer un ADC o activar un PWM).



Nodos fisicos:
Herencia (: public NodoIoT): Al indicar que ambas clases heredan de NodoIoT, automáticamente obtienen los atributos protegidos de ayer (idDispositivo, pin, conectado) sin necesidad de volver a escribirlos.

Encapsulamiento y Protección: En NodoSensorFisico, el atributo _umbralAlerta es estrictamente private. La única forma de modificarlo desde el código principal es a través de setUmbralAlerta(), el cual actúa como un filtro de seguridad. Como el ESP32 tiene un ADC de 12 bits, el método rechaza cualquier valor fuera del rango de 0 a 4095, evitando comportamientos erráticos en el sistema del invernadero.

Polimorfismo (override): La superclase exigía que existiera una función ejecutarAccion(), pero no decía qué hacía. Aquí, el polimorfismo permite que esa misma orden signifique cosas distintas: para el sensor, significa ejecutar un analogRead(pin); para el actuador, significa aplicar un digitalWrite(pin, estado)