#include <Wire.h>               // Librería para el uso del protocolo I2C

/* RTClib.h requiere la instalación de dos librerías:
   - RTClib: Permite el uso de varios relojes del fabricante Adafruit.
   - Adafruit BusIO: Necesaria para configurar ciertos elementos de los componentes electrónicos de Adafruit.
*/
#include "RTClib.h"

// Objeto global del tipo RTC_DS1307 para manejar el reloj
RTC_DS1307 rtc;

// ============================================================================
//  Clase DS1307_RTC
//  Contiene variables y métodos para inicializar, obtener y mostrar la hora
//  y fecha desde el módulo RTC DS1307.
// ============================================================================
class DS1307_RTC {
  
  public:
      // Variables que almacenan la fecha y hora obtenida del RTC
      uint8_t hora = 0, minuto = 0, segundo = 0, dia = 0, mes = 0;
      uint16_t ano = 0;
      String fecha = " ";   // Cadena con la fecha formateada
      String tiempo = " ";  // Cadena con la hora formateada
      
  public:
    void RTC_init ( void );       // Inicializa el RTC
    void get_time ( void );       // Obtiene la fecha y hora actuales
    String format_date ( void );  // Devuelve la fecha en formato legible
    String format_time ( void );  // Devuelve la hora en formato legible
    void show_time ( void );      // Muestra fecha y hora en consola serial
};

// ============================================================================
//  Método: RTC_init()
//  Inicializa el módulo RTC DS1307.
//  Si no se reconoce el dispositivo, muestra un error y reintenta.
//  Si el reloj no está corriendo, ajusta la fecha y hora con la de la computadora.
// ============================================================================
void DS1307_RTC::RTC_init ( void ) {

   while ( ! rtc.begin ( ) ) {                  
    Serial.println ( F ( "Hay un error de reconocimiento del RTC, revisa conexiones y alimentación" ) );
    Serial.flush ( );                           // Espera a que se transmita la información serial
    delay ( 3000 );
  }

  if ( ! rtc.isrunning ( ) ) {      // Si el reloj no está ejecutándose
    Serial.println ( F ( "El reloj se está configurando con la fecha y hora de la computadora" ) );
    // __DATE__ y __TIME__ son macros que retornan la fecha y hora de la computadora
    rtc.adjust ( DateTime ( F ( __DATE__ ), F ( __TIME__ ) ) );   // Ajuste automático
  }

  // Ejemplo de ajuste manual:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));  // año, mes, día, hora, minuto, segundo
}

// ============================================================================
//  Método: get_time()
//  Obtiene la fecha y hora actuales desde el RTC y las guarda en variables.
// ============================================================================
void DS1307_RTC::get_time ( void ) {
      DateTime now = rtc.now();
      segundo = now.second ( );
      minuto  = now.minute ( );
      hora    = now.hour ( );
      dia     = now.day ( );
      mes     = now.month ( );
      ano     = now.year ( );
}

// ============================================================================
//  Método: format_date()
//  Devuelve la fecha en formato legible: DD/MM/AAAA.
//  Se agregan ceros a la izquierda si el día o mes son menores a 10.
// ============================================================================
String DS1307_RTC::format_date ( void ) {
  String fecha = "";
  if ( dia < 10 ) fecha += '0';
  fecha += dia;
  fecha += '/';
  if ( mes < 10 ) fecha += '0';
  fecha += mes;
  fecha += '/';
  fecha += ano;
  return fecha;
}

// ============================================================================
//  Método: format_time()
//  Devuelve la hora en formato legible: HH:MM:SS.
//  Se agregan ceros a la izquierda si hora, minuto o segundo son menores a 10.
// ============================================================================
String DS1307_RTC::format_time ( void ) {
  String tiempo = "";
  if ( hora < 10 ) tiempo += '0';
  tiempo += hora;
  tiempo += ':';
  
  if ( minuto < 10 ) tiempo += '0';
  tiempo += minuto;
  tiempo += ':';

  if ( segundo < 10 ) tiempo += '0';
  tiempo += segundo;
  return tiempo;
}

// ============================================================================
//  Método: show_time()
//  Muestra en la consola serial la hora y fecha obtenidas del RTC.
// ============================================================================
void DS1307_RTC :: show_time ( void ) {
  Serial.print ( F ( "Hora: " ) );
  Serial.println ( format_time() );   // Mostrar hora formateada
  Serial.print ( F ( "Fecha: " ) );
  delay ( 200 );
  Serial.println ( format_date() );   // Mostrar fecha formateada
}
