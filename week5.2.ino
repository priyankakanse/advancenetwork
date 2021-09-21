 #include <SoftwareSerial.h>

#define SOILPIN 19      
int val = 0;
int soilPower = 7;

#define LEDPIN 11
#define LEDPINGREEN 0
#define LEDPINYELLOW 1
#define LEDPINRED 2

// Teensy 5V <--> HC-05 Vcc
// Teensy Ground <--> HC-05 GND

#define rxPin 7 // Teensy pin 7 <--> HC-05 Tx
#define txPin 8 // Teensy pin 8 <--> HC-05 Rx

SoftwareSerial BTSerial =  SoftwareSerial(rxPin, txPin);

void setup() {
  // Setup serial for monitor
  Serial.begin(9600); 

  pinMode(soilPower, OUTPUT);//Set D7 as an OUTPUT
  digitalWrite(soilPower, LOW);//Set to LOW so no power is flowing through the sensor

  pinMode(LEDPINRED, OUTPUT);
  pinMode(LEDPINYELLOW, OUTPUT);
  pinMode(LEDPINGREEN, OUTPUT);

  // Setup Serial1 for BlueTooth
  Serial1.begin(9600); // Default communication rate of the Bluetooth module
}

void loop() {
  if(Serial1.available() > 0)
  { // Checks whether data is comming from the serial port
    digitalWrite(LEDPIN, HIGH);
    
    Serial.print("Soil Moisture = ");
    Serial1.println("Soil Moisture = ");    
    //get soil moisture value from the function below and print it
    Serial.println(readSoil());
    Serial1.println(readSoil());
    
  

    if(readSoil() < 50)
    {
      digitalWrite(LEDPINRED, HIGH);
      digitalWrite(LEDPINYELLOW, LOW);
      digitalWrite(LEDPINGREEN, LOW);
    }
    else if(readSoil() >= 50 && readSoil() <= 100)
    {
      digitalWrite(LEDPINRED, LOW);
      digitalWrite(LEDPINYELLOW, HIGH);
      digitalWrite(LEDPINGREEN, LOW);
    }
    else if(readSoil()>100)
    {
      digitalWrite(LEDPINRED, LOW);
      digitalWrite(LEDPINYELLOW, LOW);
      digitalWrite(LEDPINGREEN, HIGH);
    }
    
   
    digitalWrite(LEDPIN, LOW); 
    delay(1000);
 }
}


 int readSoil()
{
    digitalWrite(soilPower, HIGH);//turn D7 "On"
  delay(10);//wait 10 milliseconds 
  val = analogRead(SOILPIN);//Read the SIG value form sensor 
  digitalWrite(soilPower, LOW);//turn D7 "Off"
  return val;//send current moisture value

}
