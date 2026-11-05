# ESP32 Modular IoT Datalogger & Gas Monitor

Sistema embebido IoT de monitoreo ambiental y datalogger modular desarrollado sobre el microcontrolador **ESP32**. El proyecto realiza la lectura en tiempo real de concentración de gas y humo mediante un sensor **MQ-2**, gestiona alertas locales físicas, registra bitácoras en almacenamiento local y transmite telemetría remota hacia la nube.

## 🚀 Características Principales

* **Arquitectura Modular Multitarea:** Diseñado bajo Programación Orientada a Objetos (POO) con gestión de tiempo basada en `millis()` (evitando el uso de `delay()`) para garantizar una ejecución paralela no bloqueante.
* **Monitoreo Ambiental (MQ-2):** Lectura analógica continua en pin ADC con detección de umbrales críticos programables.
* **Alertas Físicas (Actuadores):** Estado visual en tiempo real mediante **LED RGB** (Verde = Normal, Rojo = Alerta) y aviso auditivo con **Buzzer piezoeléctrico**.
* **Interfaz Local (OLED I2C):** Despliegue dinámico de lecturas de gas y estampado de tiempo en pantalla OLED SSD1306 (128x64).
* **Estampado de Tiempo (RTC DS1307):** Sincronización de hora y fecha exactas por I2C con mecanismo de fallback automático al tiempo de compilación.
* **Almacenamiento Local (MicroSD SPI):** Generación y guardado continuo de bitácoras de eventos y métricas en formato **JSON**.
* **Telemetría Remota (MQTT & WiFi):** Publicación periódica de payloads JSON y alertas prioritarias hacia un broker MQTT para monitoreo remoto.
* **Resiliencia y Tolerancia a Fallos:** Inicialización no bloqueante en `setup()` que permite al sistema operar de manera offline o sin periféricos secundarios si alguno no responde.

## 🛠️ Distribución de Pines (Pinout ESP32)

| Componente | Interfaz / Pines ESP32 |
| :--- | :--- |
| **MQ-2 Gas** | `D35` (Entrada Analógica AO) |
| **Buzzer** | `D4` (Salida Digital) |
| **LED RGB** | Rojo: `D32`, Verde: `D33`, Azul: `D25` |
| **I2C (OLED + RTC DS1307)** | SDA: `D21`, SCL: `D22` |
| **MicroSD (SPI)** | CS: `D5`, MOSI: `D23`, MISO: `D19`, SCK: `D18` |

## 📦 Requisitos de Librerías

* `ArduinoJson`
* `PubSubClient` (MQTT)
* `Adafruit_SSD1306` & `Adafruit_GFX`
* `RTClib` & `Wire`
* `SD` & `SPI`
