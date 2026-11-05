// ============================================================================
//  INCLUDE GUARDS (Protección contra inclusiones múltiples)
//  Estas líneas aseguran que el archivo Datalogger_h solo se compile una vez,
//  incluso si es incluido en varios archivos del proyecto.
//  #ifndef   -> Verifica si la macro Datalogger_h NO ha sido definida.
//  #define   -> Define la macro Datalogger_h para marcar que ya fue incluida.
//  #endif    -> Cierra la condición.
// ============================================================================
#ifndef Datalogger_h
#define Datalogger_h

// ============================================================================
//  Inclusión de librerías y objetos necesarios para el sistema de datalogger
//  Cada módulo se integra en este archivo para centralizar la gestión:
//   - MicroSD: almacenamiento de datos
//   - RTC: reloj en tiempo real
//   - ArduinoJson: creación de estructuras JSON
//   - MQTT: comunicación en red
//   - Sensores: lectura de valores analógicos
//   - Actuadores: buzzer y LCD
//   - Tasks: gestión de tareas periódicas con millis()
// ============================================================================

#include "MicroSD.h"
  MicroSD MSD;              // Objeto para manejo de archivos en MicroSD

#include "RTC.h"
  DS1307_RTC MIRTC;         // Objeto para manejo del reloj en tiempo real

#include <ArduinoJson.h>    // Librería para crear y manipular objetos JSON

#include "MQTT.h"
  MQTT mqtt;                // Objeto para comunicación con Broker MQTT

#include "Sensors.h"
  sensores SEN;             // Objeto para lectura de sensores (potenciómetro)

#include "Actuators.h"
  actuadores ACT;           // Objeto para control de actuadores (buzzer, LCD)

#include "JSONS.h"
  JSON_Factory JSON_fac;    // Objeto para creación de mensajes JSON

#include "Tasks.h"
  millis_tasks TSK;         // Objeto para gestión de tareas periódicas

#endif
