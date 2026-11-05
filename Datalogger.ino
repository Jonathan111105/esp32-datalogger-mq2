#include "Datalogger.h"   

void setup ( void ) {
  Serial.begin ( 115200 );   

  Serial.println ( F ( "Configurando: MicroSD" ) );        MSD.MicroSD_init();
  Serial.println ( F ( "Configurando: Reloj DS1307" ) );   MIRTC.RTC_init();   
  Serial.println ( F ( "Configurando: Sensores" ) );       SEN.config();
  Serial.println ( F ( "Configurando: Actuadores" ) );     ACT.config();
  Serial.println ( F ( "Configurando: WiFi" ) );           mqtt.setup_WiFi();
  Serial.println ( F ( "Configurando: Servidor MQTT" ) );  mqtt.set_MQTT_server();
  Serial.println ( F ( "Configurando: Receptor MQTT" ) );  mqtt.set_MQTT_callback();
}

void loop ( void ) {
  TSK.actualizar_tareas();     
  TSK.tarea_oled();            // Cambio de LCD a OLED
  //TSK.tarea_mq2();           // Lectura en serial del MQ2 (Opcional)
  TSK.tarea_buzzwarning();     
  TSK.tarea_mqtt();            
  mqtt.reconnect_MQTT();       
}