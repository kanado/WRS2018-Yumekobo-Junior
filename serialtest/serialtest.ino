/*char val;*/

void setup(){
  // Serial Setting
  Serial.begin(9600);

  // Port Setting
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
  if(Serial.available() > 0){
    String val = Serial.readStringUntil(';');
    
    if(val == "ON"){
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.print("ON DESU");
      Serial.println();
    }
    else if (val == "OFF"){
      digitalWrite(LED_BUILTIN, LOW);
      Serial.print("OFF DESU");
      Serial.println();
    }
    
    else {
      Serial.print("ERROR Input:[");
      Serial.print(val);
      Serial.print("]");
      Serial.println();
    }
  }
}
