# Arquitectura Base del Sistema: Superclase `NodoIoT`

En esta sección se presenta la estructura base para la gestión de componentes de hardware en el sistema del invernadero. El archivo de cabecera `include/NodoIoT.h` actúa como la **plantilla abstracta principal** de la cual heredarán todos los dispositivos físicos (sensores de humedad, temperatura, relés, actuadores, etc.).

---

## 1. Código Fuente (`include/NodoIoT.h`)

```cpp
#ifndef NODO_IOT_H
#define NODO_IOT_H

#include <Arduino.h>

class NodoIoT {
protected:
    // Atributos protegidos: accesibles por esta clase y sus subclases derivadas
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

    // Destructor virtual: evita fugas de memoria al destruir objetos derivados
    // mediante punteros a la clase base.
    virtual ~NodoIoT() {}

    // Método virtual con implementación por defecto
    virtual void iniciar() {
        // La configuración de pinMode se definirá en las clases hijas según su tipo
    }

    // Método virtual puro: define la interfaz y convierte a NodoIoT en clase abstracta
    virtual void ejecutarAccion() = 0; 
};

#endif // NODO_IOT_H
```

---

## 2. Análisis Arquitectónico y Fundamentos de POO

###  Uso de Acceso Protegido (`protected`)
Los atributos `idDispositivo`, `pin` y `conectado` se declaran bajo la visibilidad `protected`. 
* **Ventaja:** Permite que las clases derivadas (como `NodoSensorFisico` o `NodoActuador`) accedan y modifiquen directamente estas variables sin necesidad de utilizar *getters* y *setters* internos.
* **Encapsulamiento:** Mantiene estos atributos ocultos para el código externo o módulos ajenos a la jerarquía de clases.

###  Inicialización mediante el Constructor
El constructor asigna el identificador único (`String`) y el pin físico del microcontrolador (ESP32). El estado inicial de conectividad (`conectado`) se define por defecto como `false` hasta que se valide su comunicación.

###  Métodos Virtuales (`virtual`)
Al marcar el método `iniciar()` con la palabra reservada `virtual`, se permite el **método de reemplazo (overriding)**. Cada sensor o actuador futuro puede implementar su propia lógica de configuración inicial (por ejemplo, `pinMode(pin, INPUT)` frente a `pinMode(pin, OUTPUT)`).

###  Polimorfismo Base y Clases Abstractas (`= 0`)
La declaración `virtual void ejecutarAccion() = 0;` convierte a `NodoIoT` en una **clase abstracta pura**:
1. **Imposibilidad de instanciación:** No es posible crear un objeto genérico del tipo `NodoIoT` en el programa principal.
2. **Contrato de interfaz:** Obliga al compilador a exigir que cualquier clase derivada implemente de forma obligatoria su propia versión de `ejecutarAccion()`.

---

## 3. Implementación en Nodos Físicos

###  Herencia Pública (`public NodoIoT`)
Las clases derivadas heredan automáticamente la estructura de la clase base, reutilizando código y conservando los atributos comunes sin redundancia.

###  Encapsulamiento de Métodos y Control de Errores
En implementaciones concretas (por ejemplo, `NodoSensorFisico`), los atributos específicos como `_umbralAlerta` se mantienen estrictamente en ámbito `private`. 
* **Validación de datos:** La modificación de dichos atributos se realiza mediante métodos públicos (p. ej., `setUmbralAlerta()`).
* **Límite de Hardware (ADC ESP32):** El método valida que los valores se encuentren en el rango correcto del convertidor analógico-digital (0 a 4095 en 12 bits), evitando lecturas anómalas o comportamientos erráticos.

###  Polimorfismo en Acción (`override`)
Aunque la superclase exige la existencia de `ejecutarAccion()`, el comportamiento cambia según la naturaleza del hardware:
* **En Sensores:** Ejecuta lecturas de datos (`analogRead(pin)` o lecturas por I2C/OneWire).
* **En Actuadores:** Modifica estados de salidas digitales o modulación (`digitalWrite(pin, estado)` / `ledcWrite(...)`).