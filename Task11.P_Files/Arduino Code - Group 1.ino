#include <Wire.h>

int pt1 = A2;

void setup() {
 
  Serial.begin(9600);
  Serial.println("Started");
  Wire.begin(8);
  Wire.onRequest(requestEvent);
}

void loop() {
  delay(100);
}

void requestEvent(){
  int pm1 = analogRead(pt1);
  byte pm = pm1 / 4;
  Serial.println("Reading Sensor");
  Serial.println(pm1);
  Wire.write(pm);
}
