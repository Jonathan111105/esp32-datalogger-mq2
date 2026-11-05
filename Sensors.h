#ifndef Sensor_h
#define Sensor_h 

#define MQ2_pin   35    // Pin analógico del MQ2
#define MAXVALUE  1500  // Umbral de gas crítico

class sensores {
  public:
    uint16_t mq2;                 
    String hora_mq2   = "";       
    String fecha_mq2  = "";       
    bool warning_mq2  = false;    

  public:
    uint16_t get_mq2V ( void );   
    void config ( void );         
};

uint16_t sensores :: get_mq2V ( void ) {
  return analogRead ( MQ2_pin );   
}

void sensores :: config ( void ) {
  pinMode ( MQ2_pin, INPUT );      
}

#endif