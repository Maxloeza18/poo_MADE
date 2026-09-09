---
Fecha de creación: 2026-09-09
Fecha de terminación: 2026-09-28
Estado: En progreso
tags:
  - ESP32
  - electronica
  - programacion-orientada-a-objetos
---

# ESP32 — Circuito y Esquema de Conexión

## Resumen del Proyecto

Sistema de control con ESP32 que integra sensores (temperatura LM35 y LDR) y actuadores (ventilador DC y LED de potencia) controlados por PWM. El motor y el LED se manejan a través de transistores/MOSFET para proteger el microcontrolador.

---

## 1. Diagrama de Componentes

### Sensores (Entradas)

| Componente | Pin ESP32 | Conexión |
| --- | --- | --- |
| LM35 (Temp) | GPIO 34 (ADC1) | Vout → Pin 34, VCC → 3.3V, GND → GND |
| LDR | GPIO 32 (ADC1) | Divisor de voltaje: LDR entre 3.3V y Pin 32, resistencia fija (10kΩ) entre Pin 32 y GND |

### Actuadores (Salidas PWM)

**⚠️ IMPORTANTE:** Ni el motor ni el LED se conectan directamente al ESP32. Se usan transistores/MOSFET como buffers de potencia.

---

## 2. Ventilador (Motor DC) — Pin 18 → MOSFET

```
GPIO 18 ────[1kΩ]────┬──── Gate
                       │
                   IRLZ44N (N-MOSFET)
                       │
                  Drain ──── Motor (−)
                               │
                          Motor (+) ──── Fuente 12V/5V
                               │
                          ┤├  Diodo 1N4007 (en paralelo con motor, cátodo a +)
                               │
                       Source ──── GND
```

**Por qué MOSFET y no relay:**
- El relay es lento (~5ms) y no sirve para PWM a 5kHz
- El MOSFET conmuta en microsegundos, ideal para control de velocidad
- No mecánico, sin chispas, sin ruido

**Componentes necesarios:**
- MOSFET de canal N con Vgs(th) bajo (IRLZ44N o similar "logic-level")
- Resistencia Gate 1kΩ (limita corriente del ESP32)
- Diodo flyback 1N4007 o 1N5819 (protege contra picos del motor)

---

## 3. LED de Potencia — Pin 19 → Transistor

```
GPIO 19 ────[220Ω]────┬──── Base
                       │
                   2N2222 (NPN BJT)
                       │
                  Collector ────[Resistencia LED]──── LED (−)
                                                       │
                                                  LED (+) ──── Fuente 5V/12V
                       │
                  Emitter ──── GND
```

**Si el LED es de alta potencia (>1W):** usar MOSFET en vez de BJT, mismo esquema que el motor.

**Cálculo de resistencia del LED:**

$$R = \frac{V_{fuente} - V_{LED} - V_{CE(sat)}}{I_{LED}}$$

---

## 4. Diagrama de Placa (Vista Superior)

```
                    ┌──────────────┐
         3.3V ─────┤ 34    GPIO18 ├────[1kΩ]────┤Gate
         GND  ─────┤ GND   GPIO19 ├────[220Ω]───┤Base
                    │              │              │
   ┌──── LM35      │     ESP32     │         ┌────┘
   │  Vout→34      │              │      IRLZ44N    2N2222
   │  VCC→3.3V     │              │      Drain──Motor──12V
   │  GND→GND      │              │      Source──GND
   └───────────────┤              ├────[10kΩ]──LDR──3.3V
                    └──────────────┘      │
                                       GPIO32
```

---

## 5. Notas Importantes

- **GPIO 34** es solo entrada (no tiene pull-up interno) — correcto para el LM35
- **GPIO 32** también es solo entrada ADC1 — correcto para el LDR
- Ambos sensores están en el bloque ADC1, así que no hay conflicto con WiFi
- El MOSFET IRLZ44N funciona bien con 3.3V en el Gate (Vgs(th) ≈ 1-2V)
- Si usas un MOSFET normal (IRF540N), necesitas un driver de gate o convertidor de nivel porque Vgs(th) ≈ 4V y el ESP32 solo da 3.3V
- El diodo flyback es **obligatorio** — sin él, el spike del motor puede destruir el MOSFET o el ESP32

---

## 6. Comunidad GitHub

| Usuario | Rol | Enlace |
| --- | --- | --- |
| | | |
| | | |
| | | |

---
