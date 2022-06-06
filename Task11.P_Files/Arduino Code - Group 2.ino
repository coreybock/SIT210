#include <Wire.h>

int inPin = A0;
boolean running = 1;//when running=1, the liquid is detected, print out 1, otherwise, print out 0; running=0, the liquid is detected, print out 0, otherwise, print out 1.
boolean cmdReceived = 0;
int systemStatus = 0;
int waterAvail = 0;
int modePin = 5;
int pumpPin = 7;

void setup()
{
  Serial.begin(9600);

  Wire.begin(9);              
  Wire.onReceive(eventHandler);
  Wire.onRequest(eventRequest);
  
  pinMode(inPin, INPUT);
  pinMode(modePin, OUTPUT);
  pinMode(pumpPin, OUTPUT);
  digitalWrite(modePin, running);
}

boolean checkWaterLvl(){
  waterAvail = analogRead(inPin);

  if (waterAvail > 900){
    return true;
  }
  else {
    systemStatus = 2;
    return false;
  }
}


void startPump(){
  boolean pump = checkWaterLvl();
  int check = 0;

  Serial.print("Water Available: ");
  Serial.println(pump);
  
  while(pump == true){
    Serial.println("Starting pump");
    Serial.print("Count at ");
    Serial.println(check);
    digitalWrite(pumpPin, HIGH);

    if(!checkWaterLvl())
    {
      Serial.println("Ran out of water");
      systemStatus = 3;
      break;
    }
    else if(check >= 80){
      Serial.println("Should be stopped");
      systemStatus = 1;
      break;
    }
    else {
      check++;
    }

  }

  Serial.println("Stopping pump");
  digitalWrite(pumpPin, LOW);
  
  cmdReceived = 0;
  
}

void eventRequest(){
  Wire.write(systemStatus);
}

void eventHandler() {
  while (Wire.available()) { 
    byte c = Wire.read();
    Serial.print("Recieved: ");
    Serial.println(c);
    if(c == 1){
      cmdReceived = 1;
      systemStatus = 0;
    }
  }
}

void loop()
{
  if(cmdReceived == 1){
    startPump();
  }
  delay(100);
}
