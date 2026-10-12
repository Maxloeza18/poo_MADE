# Práctica 01 · Sistemas de Control con Python y ESP32

> Diseño e implementación de sistemas de control de lazo cerrado mediante simulación en **Python** y aplicación física en **ESP32 con C++**.

## Descripción

Esta práctica aborda el desarrollo de dos sistemas de control relacionados por los principios de **adquisición de datos, toma de decisiones, actuación y retroalimentación**:

- **Versión 1.0.0 — Simulador de reactor químico:** modelo térmico y barométrico en Python, con operación manual, automática y de pruebas, además de mecanismos prioritarios de seguridad (*interlocks*).
- **Versión 2.0.0 — Microinvernadero inteligente:** implementación física con ESP32, sensores de temperatura e iluminación y actuadores controlados mediante PWM.

El trabajo también contempla la organización técnica del repositorio, el uso de Git y la presentación de evidencias verificables.

## Objetivos

1. Diseñar sistemas de **lazo cerrado** en un entorno simulado y en hardware real.
2. Implementar sensores, actuadores, algoritmos de control y mecanismos de seguridad.
3. Organizar un repositorio de acuerdo con los requisitos de evaluación y trazabilidad del proyecto.
4. Documentar la evolución del software mediante contribuciones significativas y distribuidas en el tiempo.
5. Validar el comportamiento del sistema con pruebas, fotografías, esquemas y videos demostrativos.

## Tecnologías y herramientas

| Tecnología o herramienta | Uso en la práctica |
| --- | --- |
| Python 3 | Simulación del reactor y HMI por consola |
| C++ / Arduino para ESP32 | Control y adquisición de señales en el microcontrolador |
| ESP32 | Lectura ADC, salidas PWM y comunicación serie |
| Arduino IDE o PlatformIO | Edición, compilación y carga del firmware |
| Git y GitHub | Control de versiones, colaboración y entrega |
| Protoboard y componentes electrónicos | Montaje y pruebas del microinvernadero |

## Estructura del repositorio

Los archivos de identificación y exclusión se conservan en la **raíz del repositorio**, mientras que el código y las evidencias de esta práctica se organizan bajo `practica-01/`.

```text
repositorio/
├── .gitignore
├── AUTHORS.md
├── README.md
└── practica-01/
    ├── src/
    │   ├── simulador/
    │   │   └── main.py             # Código del reactor en Python
    │   └── esp32/
    │       └── main.ino            # Firmware del microinvernadero
    └── docs/
        └── Reporte_Evidencias_P1.pdf
```

> **Nota:** Los nombres `main.py`, `main.ino` y las subcarpetas dentro de `src/` son una **propuesta de organización**; deben ajustarse a los archivos reales del proyecto. La ubicación de `practica-01/docs/Reporte_Evidencias_P1.pdf` es obligatoria.

### Archivo `.gitignore`

Debe excluir al menos los archivos temporales y artefactos indicados en la guía:

```gitignore
# Python
__pycache__/
*.py[cod]
.ipynb_checkpoints/

# Editor
.vscode/

# Compilaciones y archivos generados
*.o
*.obj
*.elf
*.bin
*.hex
*.exe
.pio/
```

### Archivo `AUTHORS.md`

Utilizar exactamente los encabezados exigidos por el analizador:

```md
| Nombre | Matrícula | GitHub |
| --- | --- | --- |
| Nombre del integrante | S20XXXXXX | @usuario_github |
```

El nombre de usuario en la columna **GitHub** debe coincidir exactamente, incluyendo mayúsculas y minúsculas, con la cuenta asociada a los commits. Sustituir los datos de ejemplo por los datos reales del equipo.

---

## Versión 1.0.0 · Simulador de reactor químico

El simulador modela el comportamiento de un reactor mediante sensores virtuales y actuadores que modifican las condiciones del proceso.

### Variables y dispositivos simulados

| Dispositivo | Variable | Rango | Método |
| --- | --- | --- | --- |
| Sensor de temperatura | Temperatura | 0 a 150.0 °C | Muestreo analógico simulado |
| Sensor de presión | Presión | 0 a 15.0 bar | Muestreo analógico simulado |
| Bomba de enfriamiento | Potencia | 0 a 100 % | Control proporcional |
| Válvula de alivio | Estado | 0 o 1 | Control ON/OFF |

### Modos de funcionamiento

**Modo manual.** El usuario establece los estados de la bomba y de la válvula desde la consola. Las órdenes están sujetas a las protecciones de seguridad.

**Modo automático.** El simulador actualiza periódicamente el estado del reactor y ejecuta el control según las lecturas obtenidas. La variación de temperatura por ciclo de simulación se define como:

\[
\Delta T = 1.5 - (0.05 \times P_{bomba})
\]

Donde `P_bomba` representa el porcentaje de operación de la bomba en la escala de **0 a 100**. Por ejemplo, una bomba al 0 % implica un cambio de +1.5 °C por ciclo; al 100 %, un cambio de −3.5 °C por ciclo. Estos son valores de **simulación**, no mediciones físicas.

**Modo de pruebas.** Permite introducir lecturas artificiales o condiciones anómalas para comprobar límites, alarmas e interlocks.

> La guía no define una ecuación de evolución de la presión ni el tiempo de cada ciclo: esos aspectos deben establecerse y documentarse en la implementación, sin presentar un modelo supuesto como requisito oficial.

### Interlocks de seguridad

Los interlocks tienen **prioridad sobre los tres modos de funcionamiento** y sobre cualquier instrucción del usuario.

| Condición detectada | Respuesta obligatoria |
| --- | --- |
| Temperatura **> 85.0 °C** | Bomba al **100 %** y válvula **abierta** |
| Presión **> 12.0 bar** | Bomba al **100 %** y válvula **abierta** |
| Ambas condiciones simultáneas | Mantener ambas acciones de seguridad |

En ambos casos se deben forzar **simultáneamente** los dos actuadores. Los umbrales se especifican como comparaciones estrictas (`>`), no como `>=`.

### Interfaz HMI por consola

La interfaz debe mostrar de manera clara los valores del proceso, los actuadores, el modo activo y las posibles alarmas.

Comandos de lectura obligatorios:

```text
leer caudal
leer manometro
```

`leer manometro` consulta la presión simulada. Como la guía no define un sensor de caudal, el significado y cálculo de `leer caudal` debe documentarse en el código; no debe confundirse una estimación basada en la bomba con una medición real.

Para actualizar la pantalla sin despliegue infinito de líneas, emplear el borrado de consola indicado por el sistema operativo:

```python
import os

os.system("cls" if os.name == "nt" else "clear")
```

### Comportamientos que deben verificarse

- Cambio de estados de los actuadores en modo manual.
- Actualización de sensores y control del reactor en modo automático.
- Activación de las dos medidas de seguridad cuando se supera cualquiera de los umbrales.
- Inyección de fallos y visualización de alertas en modo de pruebas.
- Refresco de la HMI sin scroll infinito.

---

## Versión 2.0.0 · Microinvernadero inteligente con ESP32

El microinvernadero incorpora entradas físicas de temperatura y luz ambiental y dos salidas PWM para ventilación e iluminación artificial.

### Asignación de pines

| Elemento | GPIO | Señal | Requisito |
| --- | --- | --- | --- |
| Sensor térmico analógico compatible (p. ej., LM35) | **34** | ADC | Resolución de 12 bits |
| Sensor LDR (con divisor resistivo) | **32** | ADC | Medir iluminación ambiental |
| Ventilador o motor DC (mediante etapa de potencia) | **18** | PWM | Control `ledc` a **5 kHz** |
| LED de potencia (mediante etapa adecuada) | **19** | PWM | Brillo inversamente proporcional a la luz ambiental, según calibración |

**Importante sobre LM35 y DHT:** la guía menciona «LM35/DHT» para el GPIO 34, pero **GPIO 34 es solo de entrada** y se reserva aquí para medición analógica. Un DHT utiliza una interfaz digital que requiere una línea bidireccional, por lo que **no puede sustituir directamente al LM35 manteniendo ese mismo pin y tipo de señal**. Para respetar la asignación estricta, utilizar un sensor analógico compatible; un DHT requeriría un GPIO apropiado y autorización para cambiar la asignación.

### Algoritmos de control

**Control térmico**

- Leer la temperatura del sensor conectado al GPIO 34.
- Si la temperatura **supera 30 °C**, activar el ventilador al **100 % de PWM**.
- Si no supera ese umbral, aplicar el estado normal definido por la implementación.

**Control de iluminación**

- Leer el nivel de iluminación mediante la LDR conectada al GPIO 32.
- Ajustar el **duty cycle** del LED con una relación inversa: menor iluminación ambiental, mayor brillo artificial.
- Calibrar el divisor resistivo para garantizar que la lectura crezca o decrezca en el sentido esperado; una LDR puede producir tendencias opuestas según cómo se conecte.

### Salidas PWM

La guía exige el uso de las funciones `ledcSetup`, `ledcAttachPin` y `ledcWrite`, con una frecuencia de **5 kHz** para el ventilador.

```cpp
// Ejemplo conceptual para Arduino-ESP32 2.x
const int PIN_VENTILADOR = 18;
const int CANAL_VENTILADOR = 0;
const int FRECUENCIA_PWM = 5000;
const int RESOLUCION_PWM = 8;

void configurarVentilador() {
    ledcSetup(CANAL_VENTILADOR, FRECUENCIA_PWM, RESOLUCION_PWM);
    ledcAttachPin(PIN_VENTILADOR, CANAL_VENTILADOR);
}

void establecerPotenciaVentilador(bool encendido) {
    ledcWrite(CANAL_VENTILADOR, encendido ? 255 : 0);
}
```

> **Compatibilidad:** las funciones exigidas corresponden a la API tradicional de **Arduino-ESP32 2.x**. En el core **3.x**, la API LEDC cambió. Es necesario utilizar una versión compatible con la rúbrica o adaptar el firmware según autorización del docente; no asumir que el ejemplo compilará sin cambios en todas las versiones.

### Monitor Serie

Configurar la comunicación serie para recibir comandos de diagnóstico y mostrar lecturas. La guía solicita demostrar los comandos `encender`, `ajustar` y `leer` en la versión física.

Se recomienda una salida consistente, por ejemplo, JSON:

```json
{
  "temperatura_c": 28.5,
  "ldr_adc": 1200,
  "ventilador_pct": 0,
  "led_pwm": 180
}
```

> El JSON es **un ejemplo de formato**, no una lectura registrada del proyecto. La velocidad del puerto serie y la sintaxis concreta de los argumentos deben documentarse según el firmware desarrollado.

### Consideraciones eléctricas

- Respetar los niveles de tensión admitidos por los GPIO y entradas ADC del ESP32.
- No alimentar un motor directamente desde un GPIO: utilizar transistor, MOSFET o controlador apropiado, fuente adecuada y protección contra transitorios inductivos.
- Usar una etapa de potencia y limitación de corriente apropiadas para el LED.
- Conectar las tierras comunes cuando el circuito y los controladores lo requieran.
- Verificar la alimentación y el acondicionamiento del sensor térmico seleccionado.

---

## Ejecución y validación

### Simulador en Python

1. Instalar Python 3.
2. Abrir una terminal en la carpeta correspondiente a `practica-01/src/simulador/`.
3. Ejecutar el archivo de entrada del proyecto. Si se utiliza la estructura propuesta:

   ```bash
   python main.py
   ```

4. Probar los modos **Manual**, **Automático** y **Pruebas**.
5. Verificar los comandos de lectura, el refresco de pantalla y la prioridad de los interlocks.

### Firmware ESP32

1. Abrir el código de `practica-01/src/esp32/` en Arduino IDE o PlatformIO.
2. Seleccionar la tarjeta ESP32 y el puerto serie correspondientes.
3. Comprobar la versión del core Arduino-ESP32 y su compatibilidad con LEDC.
4. Cablear los sensores y actuadores conforme al esquema elaborado.
5. Compilar y cargar el firmware.
6. Abrir el Monitor Serie a la velocidad configurada en el programa.
7. Probar los comandos, el control térmico y la compensación de iluminación.

---

## Control de versiones y evaluación de contribuciones

La evaluación del historial Git considera los siguientes factores:

| Métrica | Peso | Criterio |
| --- | ---: | --- |
| Frecuencia | **40 %** | Volumen de commits en relación con el total del equipo |
| Significancia | **40 %** | Cambios sustanciales; al menos **2 commits con cambios extensos** para el puntaje máximo de este componente |
| Distribución temporal | **20 %** | Actividad distribuida idealmente en **7 días**, con máximo de **14 días** según la guía |

Buenas prácticas para mantener un historial transparente:

- Hacer commits al completar avances técnicos reales y verificables.
- Redactar mensajes que describan el cambio concreto.
- Distribuir naturalmente la implementación, pruebas y documentación a lo largo del periodo de trabajo.
- Asegurar que cada participante utilice su identidad correcta en Git y que se corresponda con `AUTHORS.md`.
- Evitar acumular todo el trabajo en un único commit o en una sola jornada.

Ejemplos de mensajes descriptivos:

```text
feat: agregar modelo térmico del reactor
feat: implementar interlocks de temperatura y presión
test: validar inyección de fallos del simulador
feat: integrar lectura ADC y control PWM en ESP32
docs: incorporar esquema y reporte de evidencias
```

---

## Entregables y evidencias

El archivo principal de evidencias debe denominarse exactamente:

```text
practica-01/docs/Reporte_Evidencias_P1.pdf
```

### Contenido del reporte PDF

**Versión 1.0.0 — Simulador Python**

- Capturas de la HMI en modo manual, con cambios de actuadores.
- Capturas del modo automático y activación de interlocks.
- Capturas del modo de pruebas, con fallos inyectados y alarmas.

**Versión 2.0.0 — ESP32**

- Fotografías claras del montaje sobre protoboard.
- Identificación visible del ESP32, sensores y actuadores.
- Diagrama esquemático de las conexiones eléctricas.

### Videos demostrativos

Se requieren **dos videos**, cada uno con duración máxima de **3 minutos**. El repositorio **no debe contener archivos de video** como `.mp4`, `.mov` o `.avi`. En su lugar, el PDF debe incluir enlaces públicos y funcionales a YouTube, Vimeo o Google Drive con acceso habilitado para cualquier persona con el enlace.

| Video | Demostración requerida | Enlace |
| --- | --- | --- |
| **1. Simulador Python** | HMI estática; modo manual; funcionamiento automático; interlocks; inyección de fallos | Pendiente de agregar al PDF |
| **2. ESP32** | Circuito armado; Monitor Serie con `encender`, `ajustar` y `leer`; activación térmica del ventilador a más de 30 °C; aumento de luz LED al cubrir la LDR | Pendiente de agregar al PDF |

## Checklist de entrega

### Código y funcionamiento

- [ ] Simulador Python con lecturas y actuadores virtuales.
- [ ] Modos **Manual**, **Automático** y **Pruebas**.
- [ ] Interlocks con prioridad sobre las órdenes del usuario.
- [ ] Comandos `leer caudal` y `leer manometro`.
- [ ] HMI con limpieza de consola y actualización legible.
- [ ] ESP32 con lectura de temperatura por GPIO 34 y LDR por GPIO 32.
- [ ] Ventilador PWM en GPIO 18 a 5 kHz y control por temperatura.
- [ ] LED PWM en GPIO 19 con compensación inversa a la luz ambiental.
- [ ] Comunicación serie para comandos y telemetría.
- [ ] Pruebas físicas documentadas de ambos lazos de control.

### Repositorio y evidencias

- [ ] `.gitignore` en la raíz con las exclusiones obligatorias.
- [ ] `AUTHORS.md` con encabezados exactos e identidades verificadas.
- [ ] Código de ambas versiones dentro de `practica-01/src/`.
- [ ] `practica-01/docs/Reporte_Evidencias_P1.pdf` con capturas, fotografías y esquema.
- [ ] Enlace público al video del simulador (máximo 3 minutos).
- [ ] Enlace público al video del hardware (máximo 3 minutos).
- [ ] Ningún archivo de video pesado subido directamente al repositorio.
- [ ] Historial de commits real, significativo y distribuido temporalmente.

---

## Integrantes

Los nombres, matrículas y cuentas oficiales del equipo deben registrarse en [`AUTHORS.md`](AUTHORS.md), respetando estrictamente el formato solicitado para su evaluación.

## Estado del proyecto

**Documentación de requisitos de la práctica.** Las casillas anteriores deben marcarse únicamente después de implementar y verificar cada apartado. Este README no constituye por sí solo evidencia de que la simulación o el circuito físico ya funcionen.

---

*Práctica 01 — Sistemas de Control con Python y ESP32.*
