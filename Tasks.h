#ifndef Task_h
#define Task_h

#define TIEMPO_MQ2      4000    
#define TIEMPO_BUZZ     2000    
#define TIEMPO_WARNING  1000    
#define TIEMPO_OLED     5000    
#define TIEMPO_RTC      1000    
#define TIEMPO_MSD      2000    
#define TIEMPO_MQTT     5000    

class millis_tasks {
  public:
      uint64_t  tiempo_anterior_mq2        = 0,   
                tiempo_anterior_buzz       = 0,   
                tiempo_anterior_buzzwarning= 0,   
                tiempo_anterior_oled       = 0,   
                tiempo_anterior_rtc        = 0,   
                tiempo_anterior_msd        = 0,   
                tiempo_anterior_mqtt       = 0,   
                tiempo_actual              = 0;   

  public:
    void tarea_mq2 ( void );          
    void tarea_buzz ( void );         
    void tarea_buzzwarning ( void );  
    void tarea_oled ( void );          
    void tarea_rtc ( void );          
    void tarea_msd ( void );          
    void tarea_mqtt ( void );         
    void actualizar_tareas ( void );  
};

void millis_tasks :: tarea_mq2 ( void ) {
  if ( ( tiempo_actual - tiempo_anterior_mq2 ) >= TIEMPO_MQ2 ) {
     Serial.print ( "1.- Ejecutando tarea MQ2: " );
     Serial.println ( SEN.get_mq2V() );   
     tiempo_anterior_mq2 = tiempo_actual;
  }
}

void millis_tasks :: tarea_buzz ( void ) {
  if ( ( tiempo_actual - tiempo_anterior_buzz ) >= TIEMPO_BUZZ ) {
     ACT.play_buzzer();   
     tiempo_anterior_buzz = tiempo_actual;
  }
}

void millis_tasks :: tarea_buzzwarning ( void ) {
  if ( ( tiempo_actual - tiempo_anterior_buzzwarning ) >= TIEMPO_WARNING ) {
     uint16_t valor_gas = SEN.get_mq2V();
     
     if ( valor_gas >= MAXVALUE ) {
       ACT.play_buzzer(); 
       ACT.set_color(HIGH, LOW, LOW); // Enciende Rojo por Alarma
       MIRTC.get_time();
       SEN.fecha_mq2 = MIRTC.format_date();
       SEN.hora_mq2  = MIRTC.format_time();    
       SEN.warning_mq2 = true;
     } else {
       ACT.set_color(LOW, HIGH, LOW); // Enciende Verde, ambiente normal
     }
     tiempo_anterior_buzzwarning = tiempo_actual;
  }
}

void millis_tasks :: tarea_oled ( void ) {
  if ( ( tiempo_actual - tiempo_anterior_oled ) >= TIEMPO_OLED ) {
     ACT.imprimirtxt("MQ2: " + String(SEN.get_mq2V()), "Hora: " + MIRTC.format_time());
     tiempo_anterior_oled = tiempo_actual;
  }
}

void millis_tasks :: tarea_rtc ( void ) {
  if ( ( tiempo_actual - tiempo_anterior_rtc ) >= TIEMPO_RTC ) {
     MIRTC.get_time();      
     tiempo_anterior_rtc = tiempo_actual;
  }
}

void millis_tasks :: actualizar_tareas ( void ) {
  tiempo_actual = millis();   
}

void millis_tasks :: tarea_msd ( void ) {
  if ( ( tiempo_actual - tiempo_anterior_msd ) >= TIEMPO_MSD ) {
     MSD.SaveFile ( JSON_fac.make_json ( MIRTC.format_time(), MIRTC.format_date(), SEN.get_mq2V(), false ) );  
     tiempo_anterior_msd = tiempo_actual;
  }
}

void millis_tasks :: tarea_mqtt ( void ) {
  if ( ( tiempo_actual - tiempo_anterior_mqtt ) >= TIEMPO_MQTT ) {
    MIRTC.get_time();
     
    if ( SEN.warning_mq2 ) {
      mqtt.publish_MQTT ( JSON_fac.make_json ( SEN.hora_mq2, SEN.fecha_mq2, SEN.get_mq2V(), true ) );
      MSD.SaveFile ( JSON_fac.make_json ( MIRTC.format_time(), MIRTC.format_date(), SEN.get_mq2V(), true ) );
      SEN.warning_mq2 = false;
      SEN.fecha_mq2   = "";
      SEN.hora_mq2    = "";
    }
    else {
      mqtt.publish_MQTT ( JSON_fac.make_json ( MIRTC.format_time(), MIRTC.format_date(), SEN.get_mq2V(), false ) );
      MSD.SaveFile ( JSON_fac.make_json ( MIRTC.format_time(), MIRTC.format_date(), SEN.get_mq2V(), false ) );
    }
    tiempo_anterior_mqtt = tiempo_actual;
  }
}

#endif