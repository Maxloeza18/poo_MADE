# REPORTE DE EVIDENCIAS – PRÁCTICA 1

## Sistemas de Control con Python y aplicación en ESP32

**Documento:** Avance de Evidencias – Semana 1  
**Práctica:** Práctica 1  
**Asignatura:** Programación Orientada a Objetos
**Equipo:** Equipo 7 Made
**Integrantes:**  
- Hernández Loeza José Maximiliano – s23013991 – MaxLoeza18
- Pérez Viveros Emmanuel – s23013933 – EPV612
- Izquierdo Hernández Daniel Isaac– s23013986 – DaniLeft

**Fecha:** [07/08/2026]  
**Repositorio GitHub:** [https://github.com/Maxloeza18/poo_MADE.git]

---

# 1. Propósito del reporte

El presente documento constituye el **primer avance del Reporte de Evidencias de la Práctica 1**, correspondiente a la primera semana de desarrollo.

Su finalidad es documentar de manera progresiva las evidencias técnicas que permitirán comprobar el cumplimiento de los requerimientos establecidos para las dos etapas principales del proyecto:

1. **Versión 1.0.0:** Simulador de reactor desarrollado en Python.
2. **Versión 2.0.0:** Micro-Invernadero Inteligente implementado físicamente mediante ESP32.

Este reporte se desarrolla tomando como referencia principal los requerimientos establecidos en el apartado **4. Entregables y Rúbrica de Evaluación**, con el objetivo de que las evidencias sean recopiladas desde las primeras etapas del proyecto y posteriormente integradas en el archivo final:

`/practica-01/docs/Reporte_Evidencias_P1.pdf`

Durante esta primera semana se da prioridad a la preparación del repositorio, organización de las evidencias y desarrollo inicial de la **Versión 1.0.0 en Python**.

---

# 2. Estado general del proyecto – Semana 1

| Elemento evaluado | Estado | Evidencia Semana 1 |
|---|---|---|
| Repositorio `/practica-01` | 🟡 En desarrollo | Estructura inicial creada |
| Archivo `.gitignore` | 🟢 Implementado | Captura / enlace al archivo |
| Archivo `AUTHORS.md` | 🟢 Implementado | Captura / enlace al archivo |
| Control de versiones Git | 🟢 Activo | Historial inicial de commits |
| Simulador Python V1.0.0 | 🟡 En desarrollo | Primera ejecución del programa |
| Modo Manual | 🟡 En desarrollo | Pruebas iniciales |
| Modo Automático | ⚪ Pendiente / parcial | Se implementará progresivamente |
| Modo de Pruebas | ⚪ Pendiente | Programado para siguiente etapa |
| Interlocks de seguridad | 🟡 En desarrollo | Lógica inicial definida |
| HMI en consola | 🟡 En desarrollo | Primera interfaz funcional |
| Hardware ESP32 V2.0.0 | ⚪ Pendiente | Etapa posterior |
| Diagrama esquemático | ⚪ Pendiente | Etapa posterior |
| Video Simulador Python | ⚪ Pendiente | Se grabará al finalizar V1.0.0 |
| Video Hardware ESP32 | ⚪ Pendiente | Se grabará al finalizar V2.0.0 |

**Leyenda:**

- 🟢 Implementado
- 🟡 En desarrollo
- ⚪ Pendiente

---

# 3. Organización inicial del repositorio

Como primera actividad se preparó la estructura del repositorio de acuerdo con los requisitos establecidos para la práctica.

La estructura de trabajo utilizada es:

```text
/practica-01
│
├── .gitignore
├── AUTHORS.md
├── README.md
│
├── src/
│   ├── python/
│   └── esp32/
│
├── docs/
│   └── evidencias/
│
└── tests/
```

Esta organización permitirá separar el código correspondiente al simulador desarrollado en Python, el programa para ESP32 y la documentación técnica del proyecto.

## 3.1 Evidencia de la estructura del repositorio

**Evidencia 01 – Estructura inicial de `/practica-01`**

![Estructura inicial del repositorio](./evidencias/semana1_01_estructura_repositorio.png)

**Descripción:**  
Captura de pantalla donde se observa la creación de la estructura principal del proyecto y las carpetas destinadas al código fuente, documentación, pruebas y evidencias.

---

# 4. Evidencia de configuración para evaluación

Debido a que el repositorio será procesado mediante un **Analizador de Contribuciones**, durante esta primera semana se verificó la existencia de los archivos requeridos para garantizar la correcta identificación de los integrantes y evitar la incorporación de archivos innecesarios.

## 4.1 Archivo `.gitignore`

Se configuró el archivo `.gitignore` para excluir archivos generados automáticamente por los entornos de desarrollo.

Como mínimo se consideran:

```gitignore
__pycache__/
.ipynb_checkpoints/
.vscode/
*.pyc
*.exe
*.bin
```

**Evidencia 02 – Archivo `.gitignore`**

![Configuración del archivo gitignore](./evidencias/semana1_02_gitignore.png)

**Resultado:**  
Se comprobó que el repositorio cuenta con las exclusiones solicitadas y que los archivos temporales o binarios no serán incluidos innecesariamente dentro del historial de Git.

---

## 4.2 Archivo `AUTHORS.md`

Se creó el archivo `AUTHORS.md` respetando el formato requerido por el analizador.

| Nombre | Matrícula | GitHub |
|---|---|---|
| [Nombre integrante 1] | [Matrícula] | @usuario |
| [Nombre integrante 2] | [Matrícula] | @usuario |
| [Nombre integrante 3] | [Matrícula] | @usuario |

Se verificará que cada nombre de usuario de GitHub coincida **exactamente**, incluyendo mayúsculas y minúsculas, con la cuenta utilizada para realizar los commits.

**Evidencia 03 – Archivo `AUTHORS.md`**

![Archivo AUTHORS](./evidencias/semana1_03_authors.png)

---

# 5. Evidencia del control de versiones

Uno de los criterios importantes de evaluación corresponde a la evolución técnica del proyecto mediante Git.

La rúbrica establece tres criterios principales:

| Métrica | Ponderación | Acción implementada |
|---|---:|---|
| Frecuencia de commits | 40 % | Realizar commits durante cada etapa de desarrollo |
| Significancia | 40 % | Registrar modificaciones técnicas relevantes |
| Distribución temporal | 20 % | Distribuir los commits durante diferentes días |

Durante la primera semana se inició el historial de contribuciones procurando evitar concentrar todo el desarrollo en un único commit.

## 5.1 Commits registrados

| Fecha | Autor | Commit | Descripción |
|---|---|---|---|
| [Fecha] | [Integrante] | `[hash]` | Creación de estructura inicial |
| [Fecha] | [Integrante] | `[hash]` | Configuración de `.gitignore` y `AUTHORS.md` |
| [Fecha] | [Integrante] | `[hash]` | Inicio del simulador del reactor |
| [Fecha] | [Integrante] | `[hash]` | Desarrollo inicial de HMI |

**Evidencia 04 – Historial de commits**

![Historial inicial de commits](./evidencias/semana1_04_commits.png)

**Observación:**  
Se continuará distribuyendo el desarrollo durante las siguientes jornadas con el objetivo de generar un historial que demuestre la evolución real del proyecto y no únicamente la entrega final del código.

---

# 6. Evidencias de la Versión 1.0.0 – Simulador en Python

Durante la primera semana se inició la construcción del modelo de control correspondiente al reactor químico simulado.

El sistema considera las siguientes variables principales:

| Variable | Rango |
|---|---:|
| Temperatura | 0 – 150 °C |
| Presión | 0 – 15 Bar |
| Bomba de enfriamiento | 0 – 100 % |
| Válvula de alivio | 0 / 1 |

---

## 6.1 Primera ejecución del simulador

Se realizó una primera ejecución del programa desde consola para comprobar el funcionamiento básico de la aplicación.

**Evidencia 05 – Ejecución inicial del simulador**

![Primera ejecución Python](./evidencias/semana1_05_simulador_python.png)

**Resultado observado:**

- El programa inicia correctamente.
- Se muestran las variables principales del reactor.
- Se establece la base para la selección de modos de operación.
- Se inicia la implementación de la interfaz HMI mediante consola.

---

# 7. Evidencia inicial de la HMI

De acuerdo con los requerimientos de la práctica, la interfaz debe operar desde consola y mantener una visualización limpia mediante el borrado periódico de pantalla.

La implementación considera:

```python
import os

os.system('cls' if os.name == 'nt' else 'clear')
```

Con esta instrucción se evita el desplazamiento continuo de información en la terminal.

La HMI deberá permitir visualizar como mínimo:

```text
========================================
       SISTEMA DE CONTROL DEL REACTOR
========================================

Modo: MANUAL

Temperatura:        XX.XX °C
Presión:            XX.XX Bar
Bomba:              XXX %
Válvula de alivio:  ABIERTA / CERRADA

Estado:
SISTEMA OPERANDO NORMALMENTE

========================================
Ingrese comando:
```

**Evidencia 06 – Prototipo inicial de HMI**

![Panel HMI](./evidencias/semana1_06_hmi.png)

---

# 8. Evidencia del Modo Manual

Durante esta etapa se inició la programación del **Modo Manual**, mediante el cual el usuario podrá modificar directamente el estado de los actuadores.

Las funciones contempladas son:

- Modificación de la bomba de enfriamiento.
- Apertura y cierre de la válvula de alivio.
- Consulta de variables.
- Lectura de temperatura.
- Lectura de presión.

Entre los comandos requeridos se consideran:

```text
leer caudal
leer manometro
```

**Evidencia 07 – Prueba inicial del Modo Manual**

![Modo manual](./evidencias/semana1_07_modo_manual.png)

**Resultado:**  
La consola recibe las primeras instrucciones del usuario y modifica las variables de operación correspondientes.

---

# 9. Desarrollo del sistema de seguridad

Uno de los elementos críticos que deberá demostrarse en el reporte final corresponde a los **interlocks de seguridad**.

La lógica requerida establece que:

```text
SI Temperatura > 85.0 °C
O
SI Presión > 12.0 Bar
```

el sistema deberá ejecutar automáticamente:

```text
Bomba de enfriamiento = 100 %
Válvula de alivio = ABIERTA
```

Esta lógica tendrá prioridad sobre cualquier instrucción enviada manualmente por el operador.

La estructura inicial considerada es:

```python
if temperatura > 85.0 or presion > 12.0:
    bomba = 100
    valvula_alivio = True
```

## 9.1 Evidencia preliminar

**Evidencia 08 – Desarrollo inicial del interlock**

![Interlock de seguridad](./evidencias/semana1_08_interlock.png)

En las siguientes semanas se realizará una prueba controlada aumentando artificialmente las variables de temperatura y presión para demostrar que el sistema ignora las instrucciones manuales cuando existe una condición crítica.

---

# 10. Evidencias requeridas para el reporte final

Para asegurar el cumplimiento del punto 4 de la práctica se utilizará la siguiente matriz de control durante todo el proyecto.

| No. | Evidencia requerida | Semana 1 | Evidencia final |
|---:|---|:---:|:---:|
| 1 | Estructura del repositorio | ✅ | ✅ |
| 2 | `.gitignore` | ✅ | ✅ |
| 3 | `AUTHORS.md` | ✅ | ✅ |
| 4 | Historial de commits | ✅ | ✅ |
| 5 | HMI del simulador | 🟡 | ⬜ |
| 6 | Modo Manual | 🟡 | ⬜ |
| 7 | Modo Automático | ⬜ | ⬜ |
| 8 | Modo Pruebas | ⬜ | ⬜ |
| 9 | Activación del interlock por temperatura | ⬜ | ⬜ |
| 10 | Activación del interlock por presión | ⬜ | ⬜ |
| 11 | Circuito físico ESP32 | ⬜ | ⬜ |
| 12 | Sensor de temperatura | ⬜ | ⬜ |
| 13 | Sensor LDR | ⬜ | ⬜ |
| 14 | Ventilador PWM | ⬜ | ⬜ |
| 15 | LED PWM | ⬜ | ⬜ |
| 16 | Monitor Serie | ⬜ | ⬜ |
| 17 | Diagrama esquemático | ⬜ | ⬜ |
| 18 | Video demostración Python | ⬜ | ⬜ |
| 19 | Video demostración ESP32 | ⬜ | ⬜ |

Esta matriz será actualizada semanalmente hasta completar la totalidad de las evidencias requeridas.

---

# 11. Planeación de evidencia fotográfica

Para evitar que al finalizar el proyecto falten elementos requeridos por la rúbrica, se definió desde esta primera semana una nomenclatura para las imágenes.

Ejemplo:

```text
/docs/evidencias/

semana1_01_estructura_repositorio.png
semana1_02_gitignore.png
semana1_03_authors.png
semana1_04_commits.png
semana1_05_simulador_python.png
semana1_06_hmi.png
semana1_07_modo_manual.png
semana1_08_interlock.png
```

Para etapas posteriores:

```text
semana2_modo_automatico.png
semana2_modo_pruebas.png

semana3_esp32_protoboard.jpg
semana3_monitor_serial.png

semana4_control_temperatura.jpg
semana4_control_ldr.jpg
semana4_diagrama_esquematico.png
```

Esta estrategia permitirá mantener trazabilidad entre el desarrollo realizado y las evidencias incluidas en el reporte técnico.

---

# 12. Planeación de las evidencias en video

Los videos no serán almacenados directamente en el repositorio GitHub.

Al finalizar las pruebas se incorporarán enlaces públicos dentro del reporte.

## Video 1 – Simulador de Reactor en Python

**Duración máxima:** 3 minutos

**Enlace:**  
[Pendiente de generación]

El video deberá demostrar:

- HMI funcionando.
- Borrado automático de pantalla.
- Modo Manual.
- Modo Automático.
- Modo de Pruebas.
- Activación de interlocks.
- Respuesta automática del sistema.

---

## Video 2 – Sistema físico con ESP32

**Duración máxima:** 3 minutos

**Enlace:**  
[Pendiente de generación]

El video deberá demostrar:

- Circuito físico.
- ESP32.
- Sensores.
- Actuadores.
- Monitor Serie.
- Comandos enviados al sistema.
- Activación del ventilador por temperatura.
- Variación del LED mediante el sensor LDR.

Antes de realizar la entrega final se comprobará que ambos enlaces puedan abrirse sin solicitar autorización al usuario.

---

# 13. Avances obtenidos durante la Semana 1

Durante la primera semana se establecieron las bases técnicas y documentales necesarias para el desarrollo de la práctica.

Los principales avances fueron:

1. Creación de la estructura inicial del repositorio.
2. Configuración del archivo `.gitignore`.
3. Elaboración de `AUTHORS.md`.
4. Inicio del historial de commits.
5. Organización de la carpeta destinada a evidencias.
6. Desarrollo inicial del simulador del reactor en Python.
7. Diseño preliminar de la HMI en consola.
8. Inicio del Modo Manual.
9. Definición de la lógica de los interlocks de seguridad.
10. Creación de una matriz para controlar las evidencias requeridas por la rúbrica.

---

# 14. Actividades para la siguiente etapa

En la siguiente etapa se continuará principalmente con la **Versión 1.0.0 del simulador**, contemplando:

- Completar el Modo Manual.
- Implementar el Modo Automático.
- Aplicar la ecuación dinámica:

```text
ΔT = (+1.5 °C) - (0.05 °C × % Operación Bomba)
```

- Implementar el Modo de Pruebas.
- Inyectar condiciones anormales de temperatura.
- Inyectar condiciones anormales de presión.
- Validar la prioridad de los interlocks.
- Mejorar la HMI.
- Registrar nuevos commits distribuidos temporalmente.
- Incorporar nuevas capturas al reporte.

---

# 15. Conclusión de la Semana 1

La primera semana permitió establecer la infraestructura necesaria para desarrollar la Práctica 1 de forma organizada y verificable.

Además del inicio de la programación del simulador, se estableció desde esta etapa un mecanismo de recopilación de evidencias alineado con los requisitos del entregable final.

La documentación progresiva permitirá que el archivo `Reporte_Evidencias_P1.pdf` no sea elaborado únicamente al finalizar el proyecto, sino que represente de manera cronológica la evolución del sistema, las pruebas realizadas y las contribuciones efectuadas por los integrantes del equipo.

El avance actual constituye la base para continuar con la implementación completa del sistema de control simulado y posteriormente realizar su transición hacia el sistema físico basado en ESP32.

---

# ANEXO A. Control de evidencias

| Código | Evidencia | Archivo | Estado |
|---|---|---|---|
| EV-S1-01 | Estructura repositorio | `semana1_01_estructura_repositorio.png` | ✅ |
| EV-S1-02 | `.gitignore` | `semana1_02_gitignore.png` | ✅ |
| EV-S1-03 | `AUTHORS.md` | `semana1_03_authors.png` | ✅ |
| EV-S1-04 | Historial Git | `semana1_04_commits.png` | ✅ |
| EV-S1-05 | Ejecución Python | `semana1_05_simulador_python.png` | 🟡 |
| EV-S1-06 | HMI | `semana1_06_hmi.png` | 🟡 |
| EV-S1-07 | Modo Manual | `semana1_07_modo_manual.png` | 🟡 |
| EV-S1-08 | Interlock | `semana1_08_interlock.png` | 🟡 |

---

**Fin del Reporte de Avance – Semana 1**
