---
Fecha: 2026-10-14
Estado: En desarrollo
tags:
  - programacion-orientada-a-objetos
  - poe
  - herencia
  - polimorfismo
  - python
---

# Bitácora de Avances — Práctica 2: Arquitectura Modular de Nodos IoT (Herencia y Polimorfismo en Python)

## 🎯 Objetivo de la Práctica

Refactorizar las clases independientes de la Práctica 1 integrándolas bajo una **superclase base** (`NodoIoT`). Esto permite optimizar la reutilización de código y gestionar la red completa mediante un **bucle polimórfico**, eliminando el uso de estructuras condicionales (`if/else`) para identificar la naturaleza de cada dispositivo. Simulación desarrollada íntegramente en Python.

---

## 🧩 Conceptos Clave Aplicados

- [x] **Abstracción** — Representación conceptual de sensores y actuadores como elementos unificados dentro de una red IoT.
- [x] **Herencia** — Implementación de `NodoSensor` y `NodoActuador` derivando de `NodoIoT` mediante el uso de `super()`.
- [x] **Encapsulamiento** — Protección de datos internos (`__limite_alerta`, `__estado_activo`, `__potencia_pwm`) gestionados a través de *setters* con validación de entradas.
- [x] **Polimorfismo** — Iteración limpia con un ciclo `for` sobre la estructura `red_iot`, invocando `enviar_telemetria()` de forma universal sin evaluar tipos de objetos.

---

## 🛠️ Avances Realizados (Código Implementado)

- `src/nodo_iot.py` — Creación de la clase madre `NodoIoT` con atributos comunes (`id_dispositivo`, `ip`, `ubicacion`, `conectado`) y métodos base como `conectar()` y `enviar_telemetria()`.
- `src/nodo_sensor.py` — Desarrollo de la subclase `NodoSensor`, integrando `super()`, el atributo privado `__limite_alerta` con validación de rango, y la sobrescritura (*override*) del método `enviar_telemetria()`.
- `src/nodo_actuador.py` — Estructuración de la subclase `NodoActuador`, incorporando los atributos privados `__estado_activo` y `__potencia_pwm`, funciones de control (`encender()` / `apagar()`), y su respectiva adaptación de `enviar_telemetria()`.
- `src/main.py` — Configuración del script principal que instancia la lista heterogénea `red_iot` y ejecuta el comportamiento polimórfico en tiempo de ejecución.

---

## 📋 Evidencias Requeridas

- [ ] Capturas de pantalla de la terminal (muestra de la ejecución del bucle polimórfico).
- [ ] Enlace al video demostrativo subido a la plataforma (duración máxima de 3 minutos).
- [ ] Resguardo de archivos multimedia en la carpeta `evidencias/`.

---

## 📌 Tareas Pendientes

- [ ] Elaborar e integrar el **diagrama UML** correspondiente dentro del reporte técnico en PDF.
- [ ] Tomar las capturas de consola y realizar la grabación del video explicativo.
- [ ] Compilar y exportar el documento final `Reporte_Evidencias_P2.pdf` dentro del directorio `docs/`.

---

## ✅ Checklist de Entrega

- [x] Estructura de código organizada en `src/` aplicando herencia, encapsulamiento y polimorfismo.
- [ ] Reporte formal en `docs/` (`Reporte_Evidencias_P2.pdf`).
- [ ] Carpeta de `evidencias/` completa.
- [x] Archivo `README.md` actualizado con la información de la práctica.
