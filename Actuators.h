#ifndef Actuators_h
#define Actuators_h

#include <Wire.h>               
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
// Declaración de la pantalla OLED conectada por I2C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Definición de pines según diagrama
#define buzz_pin 4
#define red_pin 25
#define green_pin 26
#define blue_pin 27

class actuadores {
  public:
    void config ( void );                        
    void play_buzzer ( void );                   
    void set_color ( bool r, bool g, bool b );   // Control del LED RGB
    void imprimirtxt ( String f1, String f2 );   
};

void actuadores :: config ( void ) {
  pinMode ( buzz_pin, OUTPUT );
  pinMode ( red_pin, OUTPUT );
  pinMode ( green_pin, OUTPUT );
  pinMode ( blue_pin, OUTPUT );
  set_color(LOW, LOW, LOW); // Apagar LED inicialmente

  // Inicializar pantalla OLED en dirección 0x3C
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Fallo asignacion de OLED"));
  } else {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Iniciando Datalogger...");
    display.display();
  }
}

void actuadores :: play_buzzer ( void ) {
  tone ( buzz_pin, 262, 500 );    
}

void actuadores :: set_color ( bool r, bool g, bool b ) {
  digitalWrite(red_pin, HIGH);
  digitalWrite(green_pin, HIGH);
  digitalWrite(blue_pin, HIGH);
}

void actuadores :: imprimirtxt ( String f1, String f2 ) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(f1);
  display.setCursor(0, 16); // Espaciado para la segunda línea
  display.println(f2);
  display.display();
}

#endif