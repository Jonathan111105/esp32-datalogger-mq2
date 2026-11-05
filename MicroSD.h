#ifndef MicroSD_h
#define MicroSD_h

// ============================================================================
//  Librería para manejo de archivos en una tarjeta MicroSD
//  Utiliza las librerías oficiales de Arduino: SD y SPI.
//  Permite inicializar la tarjeta, guardar datos en un archivo y leerlos.
// ============================================================================

#include <SD.h>
#include <SPI.h>

// Pin de control de la MicroSD (CS - Chip Select)
#define MICROSD_PIN 5    

// Objeto global de tipo File para manejar lectura/escritura en la MicroSD
File MicroSD_File;       

// ============================================================================
//  Clase MicroSD
//  Contiene métodos y variables para inicializar y manipular archivos en la tarjeta.
// ============================================================================
class MicroSD  {
  // VARIABLES
  public:
    uint8_t contador = 0;      
    /* Contador auxiliar (puede usarse para llevar registro de operaciones). */

    String filename = "/TestMicroSD.txt";   
    /* Nombre del archivo en la raíz de la tarjeta. 
       El prefijo "/" indica que está en el directorio principal. */

  // MÉTODOS
  public:
    void MicroSD_init ( void );   // Inicializa la tarjeta MicroSD
    void SaveFile ( String );     // Guarda datos en el archivo
    void ReadFile ( void );       // Lee datos del archivo
};

// ============================================================================
//  Método: MicroSD_init()
//  Inicializa la tarjeta MicroSD en el pin definido.
//  Si falla la inicialización, muestra un mensaje de error y reintenta.
// ============================================================================
void MicroSD::MicroSD_init ( void ) {
   while ( !SD.begin ( MICROSD_PIN ) ) {
        Serial.println ( F ( "Falló la inicialización del módulo MicroSD" ));
        delay ( 1000 );   // Espera 1 segundo antes de reintentar
    }
    Serial.println ( F ( "La librería MicroSD ha inicializado con éxito" ) );
}

// ============================================================================
//  Método: SaveFile()
//  Recibe un mensaje (String) y lo guarda en el archivo definido.
//  Si el archivo no existe, lo crea. Si existe, lo abre en modo append.
//  Después de escribir, verifica si el archivo existe en la tarjeta.
// ============================================================================
void MicroSD :: SaveFile ( String msg ) {
    
    // Abrir o crear archivo en modo append (agregar al final)
    MicroSD_File = SD.open ( filename, FILE_APPEND );
    if ( MicroSD_File ) {
        // Escribir el mensaje en el archivo
        MicroSD_File.print ( msg );
        MicroSD_File.close ( );   // Cerrar archivo
    } else {
        // Si no se pudo abrir el archivo, mostrar error
        Serial.print ( F ( "Error abriendo " ) );
        Serial.println ( filename );
    }

    // Verificar si el archivo existe en la tarjeta
    Serial.println ( "Verificando si existe el archivo: " );
    if ( SD.exists ( filename ) ) {
        Serial.println ( filename );
        Serial.println ( " existe" );
    } else {
        Serial.println ( filename );
        Serial.println ( " no existe" );
    }

    // Esperar un segundo entre operaciones
    delay ( 1000 );
}

// ============================================================================
//  Método: ReadFile()
//  Abre el archivo en modo lectura y muestra su contenido en el monitor serie.
//  Si no se puede abrir, muestra un mensaje de error.
// ============================================================================
void MicroSD :: ReadFile ( void ) {
  MicroSD_File = SD.open ( filename );   // Abrir archivo en modo lectura
  if ( MicroSD_File ) {
    Serial.println ( "Contenido del archivo:" );

    // Leer carácter por carácter hasta que no haya más datos
    while ( MicroSD_File.available ( ) ) {
      Serial.write ( MicroSD_File.read ( ) );
    }

    MicroSD_File.close ( );   // Cerrar archivo
  } else {
    // Si no se pudo abrir el archivo, mostrar error
    Serial.println ( "Error abriendo el archivo" );
  }
}

#endif
