# Programación Orientada a Objetos

Repositorio de la asignatura **Programación Orientada a Objetos**, donde se documentan y entregan las prácticas del curso. El eje temático del semestre es la **automatización de microclimas agrícolas**: un *Invernadero Inteligente* controlado por nodos sensores y actuadores.

El objetivo es aplicar los cuatro pilares de la POO —**abstracción, encapsulamiento, herencia y polimorfismo**— sobre sistemas embebidos (ESP32-S3) y simulaciones en Python.

## Contenido del repositorio

```text
.
├── .gitignore
├── AUTHORS.md
├── practica-01/
│   ├── src/          # Firmware C++ (ESP32-S3) + HMI/SCADA en Python
│   └── docs/         # Reporte y evidencias en PDF
└── practica-02/
    ├── src/          # Clases padre/hijas + bucle polimórfico (Python)
    └── docs/         # Reporte_Evidencias_P2 (PDF)
```

- **`.gitignore`** — archivos excluidos del control de versiones.
- **`AUTHORS.md`** — lista de autores del repositorio.
- Cada carpeta `practica-0X/` mantiene separado el **código fuente** (`src/`) de la **documentación** (`docs/`).

## Prácticas

### Práctica 1 — ESP32-S3 (Firmware Arduino + Panel HMI/SCADA)

Control de un sistema con **sensores** (DHT11 y LDR) y **actuadores** (ventilador por relé y LED con PWM) sobre un ESP32-S3, comunicados por puerto serial en formato **JSON**.

| Aspecto | Firmware (ESP32-S3) | Panel HMI (PC) |
| --- | --- | --- |
| Lenguaje | C++ (Arduino) | Python 3 |
| Rol | Lee sensores y mueve actuadores | Envía comandos y muestra lecturas |
| Dependencias | ArduinoJson, DHT | `pyserial` |
| Concurrencia | `loop()` secuencial | Hilos (`threading`) + `Lock` |

Clases del HMI: `Actuador` y `SensorReal`, con métodos `encender()`, `apagar()`, `ajustar()`, `leer_valor_actual()` e `info()`.

> Nota de la cursada: [[Practica 1 - ESP32-S3 (Arduino y MicroPython)]] · [[UML - Diagrama de Clases ESP32]] · [[ESP32 - Circuito y Esquema]]

### Práctica 2 — Sistema Modular de Nodos IoT (Herencia y Polimorfismo en Python)

**100 % simulación en Python.** Se refactoriza lo hecho en la Práctica 1: en lugar de clases sueltas, se agrupa todo bajo una **superclase padre** (`NodoIoT`) para reutilizar código, y se controla la red completa con un **bucle polimórfico** sin usar `if/else` para identificar el tipo de dispositivo.

**¿Qué cambia respecto a la Práctica 1?**

| Práctica 1 | Práctica 2 |
| --- | --- |
| Clases sueltas e independientes | Jerarquía con clase padre `NodoIoT` |
| Código repetido | Reutilización vía `super()` |
| Identificación con `if/else` | Bucle polimórfico |

#### Jerarquía de clases

**1. Superclase — `NodoIoT`**

- Atributos compartidos: `id_dispositivo`, `ip`, `ubicacion`, `conectado`.
- Métodos base: `conectar()`, `enviar_telemetria()`.

**2. `NodoSensor` (hereda de `NodoIoT`)**

- Reutiliza el constructor del padre con `super()`.
- Encapsulamiento: atributo privado `__limite_alerta` y un *setter* que valida rangos numéricos reales.
- Sobrescribe `enviar_telemetria()` para mostrar la lectura (temperatura / humedad / luz).

**3. `NodoActuador` (hereda de `NodoIoT`)**

- Atributos privados `__estado_activo` y `__potencia_pwm`.
- Métodos `encender()` y `apagar()`.
- Sobrescribe `enviar_telemetria()` para reportar el estado del relé o motor.

#### Bucle polimórfico

La red se recorre sin condicionales por tipo; cada objeto responde según su propia clase:

```python
red_iot = [sensor_temp, actuador_ventilador, sensor_luz]

for dispositivo in red_iot:
    dispositivo.enviar_telemetria()
```

#### Checklist de entrega (Práctica 2)

- [ ] **Diagrama UML** incluido en el reporte PDF (`docs/`), con visibilidades (`+` público, `-` privado), tipos de datos y flechas de herencia hacia `NodoIoT`.
- [ ] **Código Python** con herencia (`super()`), encapsulamiento (validación en *setters*) y bucle polimórfico (sin `if/else` por tipo de objeto).
- [ ] **Reporte PDF** (`Reporte_Evidencias_P2`) con capturas de la consola HMI y enlace a video demostrativo público (máx. 3 minutos).
- [ ] **Repositorio en GitHub** con las carpetas `src/` y `docs/` correctamente estructuradas.

> La integración física en hardware (ESP32 en C++) se aborda en la **Práctica 3**.

## Requisitos

- **Python 3.10 o superior** (Práctica 2).
- Para la Práctica 1: **Arduino IDE** (core ESP32) y `pyserial` en el Python del sistema.

```bash
pip install pyserial
```

## Cómo ejecutar (Práctica 2)

```bash
cd practica-02/src
python main.py
```

## Autores

Ver el archivo [AUTHORS.md](AUTHORS.md)


## Licencia

Proyecto académico. El uso y la distribución se rigen por lo indicado en el archivo de licencia (o por las políticas de la asignatura).
