---
Fecha: 2026-10-14
Estado: En progreso
tags:
  - programacion-orientada-a-objetos
  - avances
  - herencia
  - polimorfismo
  - python
---

# Avances — Práctica 2: Sistema Modular de Nodos IoT (Herencia y Polimorfismo en Python)

## Objetivo

Refactorizar las clases sueltas de la Práctica 1 agrupándolas bajo una **superclase padre** (`NodoIoT`) para reutilizar código, y controlar toda la red con un **bucle polimórfico** sin usar `if/else` para identificar el tipo de dispositivo. Práctica 100 % en Python (simulación).

## Conceptos aplicados

- [x] **Abstracción** — modelar sensores y actuadores como nodos de una red IoT.
- [x] **Herencia** — `NodoSensor` y `NodoActuador` heredan de `NodoIoT` con `super()`.
- [x] **Encapsulamiento** — atributos privados (`__limite_alerta`, `__estado_activo`, `__potencia_pwm`) con *setters* que validan.
- [x] **Polimorfismo** — bucle `for` sobre `red_iot` invocando `enviar_telemetria()` sin condicionales por tipo.

## Lo hecho

- `src/nodo_iot.py` — superclase `NodoIoT` con `id_dispositivo`, `ip`, `ubicacion`, `conectado`, y métodos `conectar()` / `enviar_telemetria()`.
- `src/nodo_sensor.py` — subclase `NodoSensor` con `super()`, atributo privado `__limite_alerta` y su *setter* con validación; sobrescribe `enviar_telemetria()`.
- `src/nodo_actuador.py` — subclase `NodoActuador` con atributos privados `__estado_activo` y `__potencia_pwm`; métodos `encender()` / `apagar()`; sobrescribe `enviar_telemetria()`.
- `src/main.py` — script principal con la lista mixta `red_iot` y el bucle polimórfico.

## Evidencias

- [ ] Capturas de la consola (salida del bucle polimórfico).
- [ ] Enlace al video demostrativo público (máx. 3 minutos).
- [ ] Archivos guardados en `evidencias/`.

## Pendientes

- [ ] Diseñar e incluir el **diagrama UML** en el reporte PDF.
- [ ] Tomar capturas de la consola y grabar el video.
- [ ] Generar `Reporte_Evidencias_P2` en PDF dentro de `docs/`.

## Checklist de entrega

- [x] Código en `src/` con herencia, encapsulamiento y polimorfismo.
- [ ] Reporte en `docs/` (`Reporte_Evidencias_P2.pdf`).
- [ ] Evidencias en `evidencias/`.
- [x] `README.md` de la práctica actualizado.
