#include <SoftwareSerial.h>
#include "DHT.h"

#define SOILPIN 19      
int val = 0;
int soilPower = 7;
String component_componentStatus;



#define DHTPIN 21
#define DHTTYPE 11
DHT dht(DHTPIN,DHTTYPE);

#define LEDPIN 11
#define LEDPINGREEN 0
#define LEDPINYELLOW 1
#define LEDPINRED 2
#define BUZZERPIN 3
#define PHOTOPIN 18

#define rxPin 7 // Teensy pin 7 <--> HC-05 Tx
#define txPin 8 // Teensy pin 8 <--> HC-05 Rx

SoftwareSerial BTSerial =  SoftwareSerial(rxPin, txPin);

void setup() {
  // Setup serial for monitor
  Serial.begin(9600); 

  pinMode(soilPower, OUTPUT);//Set as an OUTPUT
  digitalWrite(soilPower, LOW);//Set to LOW so no power is flowing through the sensor\

  pinMode(PHOTOPIN, INPUT);

  pinMode(DHTPIN, INPUT);
  dht.begin();

  pinMode(LEDPINRED, OUTPUT);
  pinMode(LEDPINYELLOW, OUTPUT);
  pinMode(LEDPINGREEN, OUTPUT); 
  pinMode(BUZZERPIN,OUTPUT);

  // Setup Serial1 for BlueTooth
  Serial1.begin(9600); // Default communication rate of the Bluetooth module
}

void loop() {

  digitalWrite(LEDPIN, HIGH);
  
  displaySoil();
  displayPhotores();
  displayDHT();
  
  if(Serial1.available() > 0)
  { // Checks whether data is comming from the serial port
    
    component_componentStatus = Serial1.readString();
    component_componentStatus.trim();
    
    Serial1.println(component_componentStatus);
    
    if(component_componentStatus == "RedLed_ON")
    {
        digitalWrite(LEDPINRED, HIGH);
    }
    else if(component_componentStatus == "RedLed_OFF")
    {
        digitalWrite(LEDPINRED, LOW);
    }
     else if(component_componentStatus == "YellowLed_ON")
    {
      digitalWrite(LEDPINYELLOW, HIGH);
    }
    else if(component_componentStatus == "YellowLed_OFF")
    {
      digitalWrite(LEDPINYELLOW, LOW);
    }
     else if(component_componentStatus == "GreenLed_ON")
    {
      digitalWrite(LEDPINGREEN, HIGH);
    }
     else if(component_componentStatus == "GreenLed_OFF")
    {
      digitalWrite(LEDPINGREEN, LOW);
    }
    else if(component_componentStatus == "Buzzer_ON")
    {
      digitalWrite(BUZZERPIN, HIGH);
    }
    else if(component_componentStatus == "Buzzer_OFF")
    {
      digitalWrite(BUZZERPIN, LOW);
    }

   
  }
   delay(1000);
   digitalWrite(LEDPIN, LOW); 
   delay(1000);
}

int displaySoil()
{
  digitalWrite(soilPower, HIGH);//turn D7 "On"
  delay(10);//wait 10 milliseconds 
  val = analogRead(SOILPIN);//Read the SIG value form sensor 
  digitalWrite(soilPower, LOW);//turn D7 "Off"
  
  Serial1.print(("Soil Moisture = "));
  Serial1.print(val);

  return val;
}

int displayPhotores()
{
  val = analogRead(PHOTOPIN);
  Serial1.print("Photoresistor value = ");
  Serial1.print(val);
}

void displayDHT()
{
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);

    float hif = dht.computeHeatIndex(f, h);
    float hic = dht.computeHeatIndex(t, h, false);  

    Serial1.print(F(" Humidity: "));
    Serial1.print(h);
    Serial1.print(F("%  Temperature: "));
    Serial1.print(t);
    Serial1.print(F("C "));
    Serial1.print(f);
    Serial1.print(F("F  Heat index: "));
    Serial1.print(hic);
    Serial1.print(F("C "));
    Serial1.print(hif);
    Serial1.println(F("F"));
}
