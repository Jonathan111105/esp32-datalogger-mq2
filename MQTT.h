/* ============================================================================
   Librerías necesarias para configurar WiFi y protocolo MQTT
   ============================================================================ */
#include <WiFi.h>                  // Librería para el uso del cliente WiFi
WiFiClient ESP32_WIFI;             // Objeto cliente WiFi para el ESP32

#include "PubSubClient.h"          // Librería para el uso del protocolo MQTT
PubSubClient client ( ESP32_WIFI );// Objeto cliente MQTT asociado al cliente WiFi

/* ============================================================================
   Directivas de configuración de red y parámetros MQTT
   ============================================================================ */
#define HOTSPOT_WIFI  "POCO F7"       // Nombre del punto de acceso WiFi
#define HOTSPOT_PWD   "123456789"                  // Contraseña de la red WiFi
#define MQTT_SERVER   "test.mosquitto.org"// Dirección del Broker MQTT
#define MQTT_PORT     1883                // Puerto del Broker MQTT
#define TXTOPIC       "/TX_6X"            // Topic de publicación
#define RXTOPIC       "/RX_6X"            // Topic de suscripción
//#define RXTOPIC1    "/E"                 // Ejemplo de otro topic de suscripción

/* ============================================================================
   Clase MQTT
   Contiene métodos para gestionar la conexión WiFi y el protocolo MQTT:
   - Conexión a WiFi
   - Configuración del servidor MQTT
   - Suscripción y publicación en topics
   - Reconexión automática
   - Callback para recibir mensajes
   ============================================================================ */
class MQTT {
  public:
    void subscribe_MQTT ( void );            // Suscribirse a un topic MQTT
    void publish_MQTT ( String );            // Publicar un mensaje en un topic MQTT
    void reconnect_MQTT ( void );            // Reconectarse al servidor MQTT
    void setup_WiFi ( void );                // Configurar y conectar a la red WiFi
    void set_MQTT_server ( void );           // Establecer dirección y puerto del Broker MQTT
    void set_MQTT_callback ( void );         // Configurar la función callback para recibir mensajes
    static void callback ( char* , byte* , unsigned int ); // Función callback para manejar mensajes recibidos
};

/* ============================================================================
   Método: set_MQTT_server()
   Configura el servidor MQTT y el puerto a utilizar.
   ============================================================================ */
void MQTT :: set_MQTT_server ( void ) {
  client.setServer ( MQTT_SERVER, MQTT_PORT );   // Configuración del Broker MQTT
}

/* ============================================================================
   Método: set_MQTT_callback()
   Configura la función callback que manejará los mensajes recibidos.
   ============================================================================ */
void MQTT :: set_MQTT_callback ( void ) {
  client.setCallback ( this -> callback );       // Asignar función callback
}

/* ============================================================================
   Método: subscribe_MQTT()
   Se suscribe a un topic MQTT para recibir mensajes.
   ============================================================================ */
void MQTT :: subscribe_MQTT ( void ) {
  client.subscribe ( RXTOPIC );                  // Suscripción al topic principal
  //client.subscribe ( RXTOPIC1 );               // Ejemplo de suscripción adicional
}

/* ============================================================================
   Método: publish_MQTT()
   Publica un mensaje en el topic definido.
   ============================================================================ */
void MQTT :: publish_MQTT ( String msg ) {
  Serial.println ( F ( "Publicando información" ) );
  client.publish ( TXTOPIC, msg.c_str() );       // Publicar mensaje en el topic
}

/* ============================================================================
   Método: reconnect_MQTT()
   Reconecta al servidor MQTT en caso de desconexión.
   Se suscribe nuevamente a los topics tras reconectarse.
   ============================================================================ */
void MQTT :: reconnect_MQTT ( void ) {
  if ( ! client.connected ( ) ) {                // Verificar si está desconectado
    while ( ! client.connected ( ) ) {           // Intentar reconectar
      Serial.print ( F ( "Conectando nuevamente al servidor" ) );
      if ( client.connect ( "Client_test" ) ) {  // Intento de conexión
        Serial.println ( F ( "Cliente conectado" ) );
        subscribe_MQTT ( );                      // Suscribirse nuevamente
      } else {                                   // Si falla la conexión
        Serial.print ( F ( "Falló al conectarse, tipo de error: " ) );
        Serial.print ( client.state ( ) );       // Mostrar estado del error
        Serial.println ( F ( "Intentando nuevamente en 5 segundos" ) );
        delay ( 5000 );                          // Esperar antes de reintentar
      }
    }
  }
  client.loop ( );                               // Mantener la conexión activa
}

/* ============================================================================
   Método: setup_WiFi()
   Configura y conecta el ESP32 a la red WiFi definida.
   ============================================================================ */
void MQTT :: setup_WiFi ( void ) {
  delay ( 10 );
  Serial.println ( F ( "Configurando WiFi: " ) );
  WiFi.begin ( HOTSPOT_WIFI, HOTSPOT_PWD );      // Iniciar conexión WiFi
  
  while ( WiFi.status ( ) != WL_CONNECTED ) {    // Mientras no se conecte
    delay ( 500 );
    Serial.print ( F ( "." ) );                  // Mostrar progreso
  }
  //Serial.println ( "WiFi configurado con la IP: " );
}

/* ============================================================================
   Método: callback()
   Función que maneja los mensajes recibidos en los topics suscritos.
   Parámetros:
     - topic: nombre del topic
     - message: contenido del mensaje en bytes
     - length: longitud del mensaje
   ============================================================================ */
void MQTT :: callback ( char* topic, byte* message, unsigned int length ) {
  Serial.print ( F ( "Ha llegado un mensaje de: " ) );
  Serial.println ( topic );                      // Mostrar el topic recibido
  
  String messageTemp;
  for ( int i = 0; i < length; i++ ) {
    messageTemp += (char)message[i];             // Convertir bytes a String
  }

  Serial.println ( messageTemp );                // Mostrar mensaje recibido
}
