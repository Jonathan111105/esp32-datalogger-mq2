#ifndef JSONS_H
#define JSONS_H

class JSON_Factory {
  public:
    String make_json ( String hora, String fecha, int mq2_val, bool warning );
};

String JSON_Factory :: make_json ( String hora, String fecha, int mq2_val, bool warning ) {
  DynamicJsonDocument doc ( 1024 );   
  String temp = "";                   

  doc["fecha"] = fecha;
  doc["hora"] = hora;
  doc["mq2_gas"] = mq2_val;

  if ( warning ) {
    JsonObject advertencia = doc.createNestedObject ( "advertencia" );
    advertencia["fecha"] = SEN.fecha_mq2;   
    advertencia["hora"]  = SEN.hora_mq2;    
  }

  serializeJson ( doc, temp );
  Serial.println ( temp );   
  return temp;   
};

#endif