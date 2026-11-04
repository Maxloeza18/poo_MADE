# Reporte final de evidencias — Práctica 2

## Sistema de Control Distribuido de Microclimas Agrícolas
### Arquitectura modular de nodos IoT con herencia y polimorfismo en Python

**Asignatura:** Programación Orientada a Objetos  
**Periodo documentado:** Semanas 1, 2 y 3  
**Fecha de inicio de la bitácora:** 14 de octubre de 2026  
**Fecha de actualización:** 4 de noviembre de 2026  
**Fecha de entrega indicada:** 7 de noviembre de 2026  
**Modalidad:** Simulación en Python, sin implementación física con ESP32.  
**Estado de la entrega:** Implementación POO verificada con ajuste de compatibilidad; interfaz gráfica, histéresis y video demostrativo no acreditados por los archivos aportados.

**Integrantes**

| Nombre | Matrícula | GitHub |
|:--|:--|:--|
| Jose Maximiliano Hernandez Loeza | S23013991 | `Maxloeza18` |
| Emmanuel Perez Viveros | S23013933 | `Emma612-bit` |
| Daniel Isaac Izquierdo Hernandez | S23013986 | `DaniLeft` |

---

## Resumen ejecutivo

En esta práctica se desarrolló una simulación de una red IoT destinada al monitoreo de variables y a la actuación básica sobre un invernadero. El trabajo reutiliza los conceptos de programación orientada a objetos mediante una **superclase `NodoIoT`** y las subclases **`NodoSensor`** y **`NodoActuador`**. Los dispositivos se crean en un script de simulación, se actualizan sus estados y se recorren en una colección heterogénea con el método común `enviar_telemetria()`.

La revisión final se efectuó sobre los tres archivos Python proporcionados. **Todos superaron la comprobación sintáctica**. La ejecución inicial falló porque el archivo se recibió como `nodo_IoT.py`, mientras que el código lo importa como `nodo_iot`. En una copia de trabajo donde únicamente se corrigió el nombre, la simulación funcionó y produjo una alerta de temperatura, un aviso de luminosidad, el encendido de un ventilador y tres mensajes de telemetría. No se afirma que el diseño de pantalla suministrado se encuentre implementado en estos scripts: la pantalla se incorpora como **referencia visual** para una futura interfaz HMI.

## 1. Introducción y problemática

Un invernadero necesita conocer variables como temperatura, iluminación y humedad, y responder mediante dispositivos de control. Cuando cada sensor o actuador se programa de manera aislada, se repiten atributos, se complica agregar nuevos nodos y el código puede llenarse de decisiones por tipo de dispositivo.

Para atender esta situación, se diseñó una estructura común. Cada nodo dispone de identificación, dirección IP simulada, ubicación y estado de conexión. Los sensores añaden lecturas y límites; los actuadores añaden encendido y potencia. Este enfoque permite demostrar, con un caso agrícola, cómo **la herencia disminuye repetición**, **el encapsulamiento controla modificaciones** y **el polimorfismo simplifica el recorrido de dispositivos**.

La simulación se ejecuta en una terminal. Las direcciones IP se usan como datos de los objetos; el código revisado **no establece comunicación de red real** ni utiliza sensores físicos.

## 2. Objetivos

**Objetivo general.** Implementar y verificar una arquitectura modular de nodos IoT en Python, aplicando herencia, encapsulamiento y polimorfismo en una simulación de microclima agrícola.

**Objetivos específicos.**

1. Centralizar los atributos compartidos en la superclase `NodoIoT`.
2. Especializar sensores y actuadores mediante `NodoSensor` y `NodoActuador` con `super()`.
3. Controlar el límite de alerta y los estados internos mediante atributos privados y métodos públicos.
4. Ejecutar una lista mixta `red_iot` invocando `enviar_telemetria()` sin condicionales por clase.
5. Verificar una alerta de sensor, un actuador encendido y un nodo desconectado.
6. Contrastar el prototipo de consola con el panel visual propuesto para el sistema.

## 3. Metodología y recursos

Se desarrolló una **simulación de software** y se revisó el código fuente de los módulos. Los recursos verificables son Python, tres archivos `.py`, un diagrama de clases derivado del código, una salida de consola obtenida en una prueba local y una imagen de referencia del monitor del invernadero. No se documentan conexiones eléctricas ni montaje con microcontroladores.

La verificación siguió esta secuencia: inspección de archivos, compilación sintáctica, prueba de ejecución tal como fueron entregados, corrección **solo del nombre del módulo** en una copia temporal, repetición de la ejecución y casos exploratorios sobre límites y PWM. La imagen de monitoreo se analizó por separado, pues representa un alcance más amplio que el código recibido.

## 4. Desarrollo por semanas

### 4.1 Semana 1 — Análisis y diseño

Durante la primera etapa se delimitó el problema de representar múltiples nodos sin duplicar información. Se definieron tres responsabilidades: identidad/conexión, medición y actuación. Como resultado se propuso `NodoIoT` como clase padre, además de dos clases derivadas para datos de sensores y controles de salida.

Se acordó usar los conceptos siguientes:

- **Abstracción:** representar sensores y actuadores como nodos con datos compartidos.
- **Herencia:** construir las subclases a partir de `NodoIoT`.
- **Encapsulamiento:** mantener privados los límites y estados internos que no deben modificarse de forma directa.
- **Polimorfismo:** permitir que un método con el mismo nombre produzca información diferente según el objeto.

**Producto de la semana:** propuesta de clases, relaciones de herencia y organización por módulos. El UML mostrado en la sección 5 se actualizó posteriormente para coincidir con el código real.

### 4.2 Semana 2 — Implementación orientada a objetos

En la segunda etapa se trasladó el diseño a Python. `nodo_iot.py` aporta los datos comunes y el método `conectar()`; `nodos_invernadero.py` define las clases especializadas y sobrescribe la telemetría; `simulacion_invernadero.py` construye los objetos y los recorre.

En `NodoSensor`, la propiedad `limite_alerta` permite asignar valores numéricos entre `0` y `100`; al actualizar la lectura se compara el dato contra el límite y se imprime un aviso cuando se supera. En `NodoActuador`, los métodos `encender(potencia)` y `apagar()` actualizan los atributos privados `__estado_activo` y `__potencia_pwm`. El encendido acota la potencia al intervalo `0`–`255`, aunque **no valida estrictamente que sea un entero**.

**Producto de la semana:** tres módulos fuente con herencia, propiedades, control de estado y telemetría diferenciada. Su contenido fue comprobado durante la revisión final.

### 4.3 Semana 3 — Integración y simulación del invernadero

La tercera etapa reúne un sensor de temperatura, un ventilador extractor y un sensor de luz en `red_iot`. El script configura un umbral de temperatura de `35.0`, conecta dos nodos, deja el sensor de luminosidad desconectado de manera intencional, carga lecturas simuladas y enciende el ventilador.

Se generó una imagen de referencia de un monitor más completo, con humedad de suelo, temperatura, humedad relativa, luminosidad, riego, ventilación y alumbrado. Esa imagen propone una interfaz de supervisión y lógica de histéresis, pero **ninguno de esos paneles gráficos o algoritmos de histéresis aparece en los tres scripts actuales**.

**Producto de la semana:** escenario integrado de consola y propuesta visual de ampliación. La validación de consola figura en la sección 7; las diferencias respecto al panel se detallan en la sección 8.

## 5. Arquitectura de clases

![Diagrama UML verificado con el código entregado](evidencias/Diagrama_UML_Practica_02.png)

*Figura 1. Diagrama de clases construido a partir de los tres archivos revisados. El símbolo `+` indica interfaz pública y `-` identifica atributos privados de Python.*

| Clase | Responsabilidad confirmada | Elementos relevantes |
|:--|:--|:--|
| `NodoIoT` | Mantener identidad y conexión simulada. | `id_dispositivo`, `ip`, `ubicacion`, `conectado`, `conectar()`, `enviar_telemetria()` |
| `NodoSensor` | Almacenar lectura, configurar umbral y reportar telemetría de medición. | `tipo_sensor`, `lectura_actual`, `__limite_alerta`, `limite_alerta`, `actualizar_lectura()` |
| `NodoActuador` | Administrar encendido, apagado y potencia PWM. | `tipo_actuador`, `__estado_activo`, `__potencia_pwm`, `encender()`, `apagar()` |

Las dos subclases llaman al constructor común con `super().__init__(id_dispositivo, ip, ubicacion)`. Además, redefinen `enviar_telemetria()` para imprimir mensajes adecuados a cada dispositivo. En el código recibido, **el método imprime el resultado y devuelve `None`**; por lo tanto, no se debe envolver su llamada en `print()` esperando una cadena de retorno.

### 5.1 Ejemplo real de polimorfismo

```python
red_iot = [sensor_temp, actuador_ventilador, sensor_luz]

for dispositivo in red_iot:
    dispositivo.enviar_telemetria()
    time.sleep(0.5)
```

El ciclo no consulta `isinstance()` ni utiliza `if/else` para distinguir sensores y actuadores. La elección del método ocurre automáticamente según la clase del objeto. El retardo de `0.5` segundos separa mensajes; **no implica adquisición periódica continua**.

## 6. Configuración de la simulación

| Dispositivo | Clase | Ubicación | IP simulada | Configuración |
|:--|:--|:--|:--|:--|
| `SENS-TEMP` | `NodoSensor` | Sector A | `192.168.1.10` | Conectado, límite `35.0`, lectura `36.5` |
| `ACT-VENT` | `NodoActuador` | Sector A | `192.168.1.11` | Conectado, encendido, PWM `200` |
| `SENS-LUZ` | `NodoSensor` | Techo | `192.168.1.12` | Desconectado, lectura `45.0`, límite inicial `0.0` |

La simulación sigue este orden: se crean las instancias, se configura el límite de temperatura, se conectan el sensor de temperatura y el ventilador, se actualizan dos lecturas, se enciende el actuador y se genera una sola ronda de telemetría. **La alerta de luminosidad se produce por comparar `45.0` contra el límite predeterminado `0.0`**, no por el hecho de que el sensor esté fuera de línea.

El PWM de `200/255` equivale aproximadamente a **78.4 %** de la escala de 8 bits. Este dato corresponde al script revisado y no debe confundirse con el **75 %** mostrado en la imagen conceptual.

## 7. Pruebas y resultados obtenidos

La ejecución se probó en un entorno Python local el **4 de noviembre de 2026**. Se conservan diferenciados el resultado con los nombres originales y el resultado tras normalizar únicamente el nombre del archivo.

| Verificación | Resultado | Interpretación |
|:--|:--|:--|
| Compilación sintáctica de tres módulos | **Correcta** | No se detectaron errores de sintaxis. |
| Ejecución sin modificar nombres | **Falló** | `ModuleNotFoundError: No module named 'nodo_iot'`. |
| Ejecución con archivo renombrado a `nodo_iot.py` | **Correcta** | Se imprimieron alertas, encendido y telemetría. |
| Sensor de temperatura: lectura `36.5`, límite `35.0` | **Correcta** | Se activó alerta de temperatura. |
| Estado de sensor de luz | **Correcta** | Telemetría con estado `Offline`. |
| Lista mixta `red_iot` | **Correcta** | Se procesaron tres instancias mediante el mismo método. |
| Límite de sensor `-1` o `101` | **Rechazado** | El setter genera `ValueError`. |
| PWM `-5` o `300` | **Acotado** | El valor se convierte a `0` o `255`, respectivamente. |

**Transcripción de la salida real**, obtenida al ejecutar los archivos en una copia de prueba con el nombre del módulo corregido:

```text
[SENS-TEMP] Conectado a la red web en IP: 192.168.1.10
[ACT-VENT] Conectado a la red web en IP: 192.168.1.11
¡ALERTA SENS-TEMP! Temperatura excedió el límite: 36.5
¡ALERTA SENS-LUZ! Luminosidad excedió el límite: 45.0
[ACT-VENT] Ventilador de extracción ENCENDIDO (PWM: 200).

--- Ejecutando Bucle Polimórfico ---
[SENS-TEMP | Online] Temperatura: 36.5
[ACT-VENT | Online] Ventilador de extracción: ON a 200 PWM
[SENS-LUZ | Offline] Luminosidad: 45.0
```

Esta transcripción constituye **evidencia de una prueba técnica local**; no sustituye las capturas originales de terminal o el video que solicite la guía de entrega. El archivo `.txt` correspondiente se adjunta en `docs/evidencias/`.

### 7.1 Casos de prueba adicionales y observaciones

Se comprobó que el setter del sensor acepta `0`, `35` y `100`; rechaza valores fuera de rango, cadenas de texto e infinitos. Sin embargo, también acepta `True` porque en Python `bool` es subtipo de `int`. El actuador admite valores fraccionarios como `72.5` en PWM, por lo que la restricción a enteros de 8 bits todavía no está completa. Un texto como potencia genera `TypeError`.

Estos casos no invalidan la demostración principal de herencia y polimorfismo, pero deben considerarse si la simulación va a ampliarse o evaluarse con entradas imprevistas.

## 8. Panel de supervisión y control con histéresis: alcance de la referencia visual

![Diseño de referencia del monitor de microclimas agrícolas](evidencias/referencia_monitor_iot.png)

*Figura 2. Imagen proporcionada del monitor de microclimas. Es una referencia visual; no se acredita como captura generada por los tres módulos Python revisados.*

En el diseño se observan cinco nodos (`S001`, `S002`, `A001`, `A002` y `A003`), indicadores de humedad de suelo, temperatura, humedad relativa y luz, así como electroválvula, ventilador, iluminación y registros. Los valores representados incluyen **68 %** de humedad del suelo, **24.5 °C**, **72 %** de humedad relativa y **320 lux**.

| Función | En la imagen | En el código revisado |
|:--|:--|:--|
| Lista de nodos y estado de conexión | Sí, cinco nodos | Sí, tres nodos en consola |
| Temperatura y luminosidad | Sí | Sí, como lecturas simuladas |
| Humedad de suelo y humedad relativa | Sí | **No implementadas** en el escenario entregado |
| Actuador de ventilación | Sí | Sí, con PWM `200` |
| Electroválvula e iluminación | Sí | **No instanciadas** en la simulación |
| Panel visual de indicadores | Sí | **No implementado** en los `.py` |
| Lógica automática con histéresis | Representada gráficamente | **No implementada** en los `.py` |
| Marca de tiempo en telemetría | Representada gráficamente | **No generada** por el código actual |

La histéresis propone dos umbrales para evitar encendidos y apagados repetitivos. Como **ejemplo de diseño** para riego: encender al bajar a `60 %` de humedad, apagar al subir a `75 %` y mantener el estado previo entre ambos. Este comportamiento requiere guardar el estado anterior y aún no aparece codificado. En el panel de ventilación se muestran porcentajes para umbrales descritos como temperatura; cuando se implemente, deberán expresarse en **°C**, sin confundirlos con el porcentaje PWM.

## 9. Organización de archivos y reproducibilidad

```text
practica-02/
├── src/
│   ├── nodo_iot.py
│   ├── nodos_invernadero.py
│   └── simulacion_invernadero.py
└── docs/
    ├── Reporte_Evidencias_P2.pdf
    ├── Reporte_Final_Practica_02.md
    └── evidencias/
        ├── Diagrama_UML_Practica_02.png
        ├── referencia_monitor_iot.png
        └── salida_consola_verificada.txt
```

**Nota de compatibilidad:** el archivo original se recibió como `nodo_IoT.py`, pero `nodos_invernadero.py` contiene `from nodo_iot import NodoIoT`. Para ejecutar el proyecto en sistemas sensibles a mayúsculas se requiere el nombre `nodo_iot.py`. En el paquete de entrega del reporte se incluye una copia con ese nombre, **sin cambiar el contenido del código**.

Para reproducir la simulación desde la carpeta `src/`:

```bash
python simulacion_invernadero.py
```

Se requiere Python 3; los módulos empleados (`time`) forman parte de la biblioteca estándar. El código no necesita conexión de red ni hardware externo para imprimir la telemetría.

## 10. Limitaciones detectadas y mejoras recomendadas

1. **Nombre del módulo:** unificar `nodo_iot.py` y la sentencia `import` para asegurar compatibilidad.
2. **Validación de sensor:** asignar umbrales apropiados según magnitud y evitar que el valor por defecto `0.0` cause alertas no deseadas; validar también lecturas.
3. **Validación de PWM:** rechazar tipos no enteros y valores inválidos si se exige una escala digital de 8 bits, en vez de aceptar fracciones o recortar silenciosamente.
4. **Telemetría:** incorporar unidades y marca de tiempo cuando se busquen registros históricos; definir claramente si `enviar_telemetria()` imprime o devuelve datos.
5. **Conexión:** diferenciar el estado lógico `Online/Offline` de una comunicación de red real, que no se implementa aquí.
6. **Control automático:** programar histéresis si el proyecto final pretende reaccionar automáticamente a mediciones.
7. **Interfaz gráfica:** vincular cualquier HMI futura con datos producidos por la simulación, evitando que la imagen y la consola presenten nodos o estados incompatibles.
8. **Evidencias complementarias:** obtener captura auténtica de ejecución, video demostrativo público (si la guía mantiene ese requisito) y enlace al repositorio.

## 11. Conclusiones

La práctica permitió demostrar el uso de programación orientada a objetos en un escenario sencillo y comprensible: una red de microclima agrícola simulada. La **herencia** concentra los datos comunes, el **encapsulamiento** restringe el acceso a ciertos atributos y el **polimorfismo** permite manejar sensores y actuadores con una sola instrucción de telemetría dentro de `red_iot`.

Tras corregir la diferencia de mayúsculas en el nombre del módulo, la ejecución confirmó que los tres nodos generan mensajes según sus clases y estados. La prueba también reveló oportunidades de mejora en la validación de límites, la potencia PWM y el tratamiento de sensores desconectados. La imagen de monitorización aporta una ruta de ampliación, pero la histéresis y la HMI gráfica **no forman parte del código entregado**.

En consecuencia, se considera **verificado el núcleo académico de herencia, encapsulamiento y polimorfismo**, mientras que la entrega integral aún requiere incorporar las evidencias audiovisuales y, si así lo exige el docente, las funciones avanzadas que aparecen en el diseño visual.

## 12. Lista de comprobación para la entrega

| Elemento | Situación al cierre de la revisión |
|:--|:--|
| Clase base `NodoIoT` y subclases | Verificadas en código |
| Uso de `super()` | Verificado |
| Atributos privados y propiedad con setter | Verificados con observaciones |
| Método sobrescrito `enviar_telemetria()` | Verificado |
| Bucle polimórfico `red_iot` | Verificado en ejecución |
| Diagrama UML actualizado | Incluido |
| Transcripción de consola de prueba local | Incluida |
| Imagen del monitor | Incluida como referencia, no como ejecución |
| Captura auténtica de terminal del equipo | Pendiente de proporcionar |
| Video demostrativo y URL pública | Pendiente de proporcionar |
| HMI gráfica e histéresis funcional | No acreditadas por el código adjunto |
| Reporte final PDF | Generado |

---

**Fuentes internas revisadas:** `nodo_IoT.py`, `nodos_invernadero.py`, `simulacion_invernadero.py`, bitácora de semanas 1–3 e imagen del panel de microclimas proporcionados durante el desarrollo. **No se usaron fuentes externas ni se inventaron pruebas de hardware.**
