#include "DHT.h"

#define SOILPIN 20      

#define DHTPIN 21
#define DHTTYPE 11
DHT dht(DHTPIN,DHTTYPE);

#define rxPin 7 // Teensy pin 7 <--> HC-05 Tx
#define txPin 8 // Teensy pin 8 <--> HC-05 Rx

void setup() 
{
  Serial.begin(9600); // Setup serial for monitor
  pinMode(SOILPIN, INPUT);

  pinMode(DHTPIN, INPUT);
  dht.begin();
  Serial1.begin(9600); // Setup Serial1 for BlueTooth
}

void loop() 
{
  
  float s = analogRead(SOILPIN);
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  
  
  Serial1.print(F("Temperature "));
  Serial1.print(t);
  Serial.print(("Temperature "));
  Serial.print(t);
  Serial1.print((" SoilMoisture "));
  Serial1.print(s);
  Serial.print((" SoilMoisture "));
  Serial.print(s);
  Serial1.print(" Humidity ");
  Serial1.println(h);
  Serial.print(" Humidity ");
  Serial.println(h);

  delay(3000);
}
