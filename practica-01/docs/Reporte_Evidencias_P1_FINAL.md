---
fecha_creacion: 2026-09-09
fecha_terminacion: 2026-09-28
estado: Finalizado
tags:
  - ESP32
  - electronica
  - programacion-orientada-a-objetos
  - HMI
  - SCADA
  - control
---

# REPORTE DE EVIDENCIAS – PRÁCTICA 1

## Sistemas de Control con Python y aplicación en ESP32

**Asignatura:** Programación Orientada a Objetos  
**Periodo de trabajo:** 07/09/2026 al 28/09/2026  
**Entregable final:** `Reporte_Evidencias_P1.pdf`  
**Ubicación requerida:** `/practica-01/docs/Reporte_Evidencias_P1.pdf`

---

## Integrantes del equipo

| Nombre | Matrícula | Usuario GitHub |
|---|---|---|
| Jose Maximiliano Hernandez Loeza | S23013991 | Maxloeza18 |
| Emmanuel Perez Viveros | S23013933 | Emma612-bit |
| Daniel Isaac Izquierdo Hernandez | S23013986 | DaniLeft |

---

# 1. Introducción

La Práctica 1 tuvo como objetivo desarrollar un sistema de control en dos etapas. La primera correspondió a una implementación en Python orientada a objetos, utilizando una interfaz HMI estática en consola para representar sensores, actuadores y eventos del proceso. La segunda etapa consistió en trasladar los conceptos de adquisición de datos y actuación a un sistema físico basado en ESP32, integrando sensores, actuadores y comunicación serial bidireccional con Python.

El desarrollo se realizó de forma progresiva. Primero se utilizó un HMI de prueba para validar la organización del código, las clases, los objetos, el registro de eventos y el procesamiento de comandos. Posteriormente se adaptó el HMI a las variables propias de la práctica y, finalmente, se desarrolló la integración con hardware real.

Este reporte reúne las evidencias disponibles del diseño, implementación física y funcionamiento del sistema. La demostración dinámica de operación se complementa mediante un **video de funcionamiento preparado por el equipo**, cuyo enlace deberá colocarse en el apartado correspondiente antes de generar el PDF definitivo.

---

# 2. Objetivos de la práctica

Los objetivos desarrollados durante la práctica fueron:

- Aplicar Programación Orientada a Objetos para representar sensores y actuadores.
- Desarrollar una interfaz HMI estática en consola.
- Implementar un registro de eventos tipo SCADA/HMI.
- Simular variables de proceso en Python.
- Integrar sensores físicos con un ESP32.
- Controlar actuadores desde el microcontrolador.
- Establecer comunicación serial bidireccional entre Python y ESP32.
- Intercambiar datos y comandos mediante mensajes JSON.
- Documentar la evolución del diseño mediante esquemáticos, fotografías y evidencias de funcionamiento.

---

# 3. Versión 1.0.0 – Simulación y HMI en Python

## 3.1 HMI de prueba

La primera etapa consistió en validar una interfaz HMI estática en consola. El programa base permitió comprobar la estructura orientada a objetos mediante clases de sensores y actuadores, así como el uso de comandos escritos por el usuario.

Las principales funciones probadas fueron:

- encendido de actuadores;
- apagado de actuadores;
- ajuste de punto de operación;
- lectura de sensores simulados;
- limpieza de pantalla;
- registro de eventos;
- finalización controlada del programa.

La pantalla se redibuja en cada ciclo mediante la instrucción correspondiente al sistema operativo, evitando el desplazamiento continuo de información y manteniendo un panel estático.

## 3.2 Adaptación a las variables de la práctica

El HMI evolucionó hacia una versión específica para el sistema planteado en la práctica, empleando las siguientes variables:

| Elemento | Tipo | Rango / condición |
|---|---|---|
| Temperatura | Sensor simulado | 0 a 150 °C |
| Presión | Sensor simulado | 0 a 15 Bar |
| Bomba de enfriamiento | Actuador | 0 a 100 % |
| Válvula de alivio | Actuador | Estado de operación |
| HMI | Interfaz | Consola estática |
| Registro | Event Logger | Eventos recientes |

En esta etapa, las lecturas de los sensores se obtuvieron mediante valores simulados dentro de los rangos establecidos, permitiendo validar el comportamiento del software antes de conectar hardware real.

## 3.3 Operación manual, automática y de pruebas

La guía de la práctica establece tres escenarios que deben mostrarse en la demostración:

### Modo Manual

El usuario puede ejecutar comandos directamente desde el HMI para modificar el estado de los actuadores y consultar sensores.

### Modo Automático

El sistema debe responder automáticamente a las condiciones definidas por la lógica de control, sin depender de una instrucción manual continua.

### Modo de Pruebas

El sistema debe permitir forzar o simular condiciones anormales con el objetivo de comprobar el comportamiento de las protecciones y de la lógica de seguridad.

> **Evidencia dinámica:** la demostración de estos modos se complementa con el video de funcionamiento del equipo.

**Enlace del video de la Versión 1.0.0:**  
`[INSERTAR ENLACE PÚBLICO AL VIDEO]`

---

# 4. Versión 2.0.0 – Implementación física con ESP32

## 4.1 Desarrollo del diseño

La segunda etapa trasladó los conceptos del simulador a hardware real. El sistema físico integra un ESP32, sensor de temperatura, sensor de iluminación, LED, motor DC y una etapa de potencia para el accionamiento del motor.

Durante el desarrollo existieron variantes de diseño. La propuesta preliminar contempló un LM35 y un LDR como sensores, mientras que las pruebas físicas documentadas posteriormente utilizaron un sensor DHT11 junto con un LDR. Esta evolución se conserva en el reporte debido a que forma parte del proceso de diseño e implementación del equipo.

---

# 5. Esquemático del micro-invernadero

El esquemático se utilizó como referencia para definir la interconexión entre sensores, actuadores, controlador y etapa de potencia.

## Evidencia 1 – Diagrama esquemático

![Diagrama esquemático del micro-invernadero](./evidencias/01_esquematico_invernadero.png)

En el diagrama se observan:

- ESP32 como controlador principal;
- sensor de temperatura;
- sensor de iluminación;
- LED;
- motor DC;
- módulo L298N como etapa de potencia para el motor;
- conexiones de alimentación y tierra.

El esquemático permitió establecer una base previa al montaje físico sobre protoboard y reducir errores durante la interconexión.

---

# 6. Integración del hardware

## 6.1 ESP32

El ESP32 funciona como elemento central del sistema. Su función es adquirir las señales de los sensores, procesar los datos, transmitir telemetría a Python y ejecutar las órdenes recibidas desde la interfaz HMI.

## 6.2 Sensor de temperatura

Durante las pruebas físicas se utilizó un sensor DHT11 para obtener la temperatura ambiente.

### Evidencia 2 – Sensor DHT11

![Sensor DHT11](./evidencias/08_dht11.jpeg)

El sensor se conecta al ESP32 mediante alimentación, tierra y una línea de datos digital.

## 6.3 Sensor de iluminación LDR

El LDR se utiliza para detectar cambios en la iluminación ambiental.

### Evidencia 3 – Sensor LDR

![Sensor LDR](./evidencias/09_ldr.jpeg)

La señal del LDR permite representar la intensidad luminosa mediante un valor de adquisición que posteriormente se muestra en el HMI.

## 6.4 Driver de motor L298N

Para evitar conectar el motor directamente al ESP32 se utilizó un módulo L298N como etapa de potencia.

### Evidencia 4 – Módulo L298N

![Módulo L298N](./evidencias/04_driver_l298n.jpeg)

El módulo permite separar la etapa lógica de la etapa de potencia del motor y proporciona una interfaz adecuada para su accionamiento.

## 6.5 Motor DC

El motor DC representa el ventilador del micro-invernadero. Su función es proporcionar ventilación cuando la lógica de control así lo requiera.

## 6.6 LED

El LED representa el elemento de compensación de iluminación. Su intensidad puede ser modificada mediante una señal PWM en las versiones de control desarrolladas.

---

# 7. Montaje físico sobre protoboard

## Evidencia 5 – Vista general del montaje

![Montaje general del sistema](./evidencias/05_montaje_general.jpeg)

En esta fotografía se observa la integración física de:

- ESP32;
- sensor DHT11;
- sensor LDR;
- LED;
- módulo L298N;
- motor DC;
- cableado de alimentación y señales;
- conexión USB utilizada para programación y comunicación serial.

Esta evidencia permite identificar de forma conjunta los principales elementos empleados durante las pruebas de hardware.

## Evidencia 6 – Detalle del ESP32 y sensores

![ESP32, DHT11 y LDR](./evidencias/06_esp32_dht11_ldr.jpeg)

La fotografía muestra con mayor detalle el ESP32 montado en protoboard junto con el sensor DHT11 y el LDR.

## Evidencia 7 – Vista alternativa del montaje

![Vista alternativa del montaje](./evidencias/07_esp32_dht11_ldr_alt.jpeg)

Esta vista complementaria permite observar la distribución física de conexiones y componentes sobre la protoboard.

---

# 8. Comunicación Serial Python – ESP32

La integración entre Python y el ESP32 utiliza comunicación serial a **115200 baudios**.

El intercambio de información se realiza mediante mensajes JSON.

## 8.1 Telemetría del ESP32 hacia Python

El microcontrolador transmite los valores de los sensores con una estructura similar a:

```json
{"temp": 30.8, "ldr": 747}
```

Python recibe estas variables y las muestra dentro del HMI.

## 8.2 Comandos desde Python hacia el ESP32

Python puede transmitir órdenes al microcontrolador. En la versión de prueba con el HMI integrado se utilizaron comandos equivalentes a:

```json
{"fan_state": 1}
```

y:

```json
{"led_duty": 128}
```

La primera orden controla el estado del ventilador y la segunda establece el valor de operación del LED.

---

# 9. HMI conectado al ESP32-S3

## Evidencia 8 – Panel HMI con lecturas reales

![HMI conectado al ESP32-S3](./evidencias/02_hmi_esp32_s3.png)

La captura del panel HMI muestra la integración entre la aplicación de Python y el ESP32-S3.

Durante la evidencia mostrada se registraron:

| Variable | Valor observado |
|---|---|
| Temperatura | 30.8 °C |
| LDR | 747 ADC |
| Ventilador | OFF |
| LED | OFF |
| Potencia LED | 0.0 % |

Además, la interfaz presenta:

- sección de actuadores;
- sección de sensores físicos en tiempo real;
- registro de eventos;
- lista de comandos disponibles;
- campo de ingreso de comandos.

Esta captura permite comprobar que la interfaz recibe información del hardware y la presenta de forma estructurada.

---

# 10. Evolución del diseño

Durante el desarrollo se realizaron ajustes entre el diseño preliminar y la configuración empleada en las pruebas físicas.

| Elemento | Diseño preliminar | Prueba física documentada |
|---|---|---|
| Sensor de temperatura | LM35 | DHT11 |
| Sensor de iluminación | LDR | LDR |
| Etapa de motor | L298N / etapa de potencia | L298N |
| Motor | Motor DC / ventilador | Motor DC |
| LED | LED de potencia | LED |
| Controlador | ESP32 | ESP32-S3 |
| Comunicación | Planeada | Serial JSON implementada |

Esta evolución representa el proceso de adaptación realizado durante la construcción y validación del prototipo.

---

# 11. Evidencia en video

La guía establece que los videos no deben almacenarse directamente en el repositorio. Por esta razón, el equipo adjuntará enlaces públicos a la evidencia dinámica.

## Video 1 – Simulación en Python

El video deberá mostrar:

- funcionamiento del HMI;
- operación manual;
- operación automática;
- pruebas de condiciones anormales;
- respuesta del sistema.

**Enlace:**  
`[INSERTAR ENLACE PÚBLICO]`

## Video 2 – Hardware con ESP32

El video deberá mostrar:

- circuito físico;
- sensores;
- actuadores;
- comunicación con el HMI;
- lectura de temperatura;
- lectura del LDR;
- accionamiento del ventilador;
- actuación del LED.

**Enlace:**  
`[INSERTAR ENLACE PÚBLICO]`

Antes de la entrega deberán verificarse los permisos de ambos enlaces para que puedan abrirse sin solicitar autorización.

---

# 12. Matriz de evidencias

| Código | Evidencia | Estado |
|---|---|---|
| EV-01 | Esquemático del invernadero | ✅ |
| EV-02 | Sensor DHT11 | ✅ |
| EV-03 | Sensor LDR | ✅ |
| EV-04 | Driver L298N | ✅ |
| EV-05 | Montaje físico general | ✅ |
| EV-06 | ESP32 y sensores en protoboard | ✅ |
| EV-07 | Vista complementaria del montaje | ✅ |
| EV-08 | HMI conectado al ESP32-S3 | ✅ |
| EV-09 | Video de simulación Python | 🔗 Por insertar |
| EV-10 | Video de hardware ESP32 | 🔗 Por insertar |

---

# 13. Resultados

A partir de las evidencias reunidas se logró documentar la transición desde un entorno de simulación en Python hasta una implementación física basada en ESP32.

El sistema desarrollado permitió:

- estructurar sensores y actuadores mediante Programación Orientada a Objetos;
- visualizar variables mediante una interfaz HMI;
- mantener un registro de eventos;
- adquirir valores de sensores físicos;
- transmitir telemetría mediante comunicación serial;
- utilizar JSON como formato de intercambio;
- controlar actuadores desde Python;
- integrar una etapa de potencia para el motor;
- documentar el circuito mediante fotografías y esquemático.

La evidencia fotográfica confirma la integración de los principales elementos del prototipo, mientras que el video complementa la demostración de funcionamiento dinámico.

---

# 14. Conclusiones

La Práctica 1 permitió aplicar conceptos de Programación Orientada a Objetos, adquisición de datos, control de actuadores, interfaces HMI y comunicación entre software y hardware.

El desarrollo progresivo facilitó validar primero la lógica del programa y posteriormente trasladarla a un entorno físico con ESP32. La utilización de mensajes JSON simplificó la comunicación entre Python y el microcontrolador, mientras que la incorporación de sensores y actuadores permitió observar el comportamiento del sistema en condiciones reales.

El esquemático, las fotografías del prototipo, la captura del HMI y los videos de demostración constituyen la evidencia técnica del trabajo realizado durante el periodo comprendido entre el **07/09/2026 y el 28/09/2026**.

Para la entrega definitiva, este documento deberá convertirse a:

```text
Reporte_Evidencias_P1.pdf
```

y almacenarse en:

```text
/practica-01/docs/
```

---

# ANEXO A. Archivos de evidencia

```text
/practica-01/docs/
│
├── Reporte_Evidencias_P1.md
├── Reporte_Evidencias_P1.pdf
│
└── evidencias/
    ├── 01_esquematico_invernadero.png
    ├── 02_hmi_esp32_s3.png
    ├── 04_driver_l298n.jpeg
    ├── 05_montaje_general.jpeg
    ├── 06_esp32_dht11_ldr.jpeg
    ├── 07_esp32_dht11_ldr_alt.jpeg
    ├── 08_dht11.jpeg
    └── 09_ldr.jpeg
```
