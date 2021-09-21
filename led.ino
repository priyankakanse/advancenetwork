#define REDLED 0
#define YELLOWLED 1
#define GREENLED 2

#define rxPin 7 // Teensy pin 7 <--> HC-05 Tx
#define txPin 8 // Teensy pin 8 <--> HC-05 Rx

String component_componentStatus;

void setup() 
{
  Serial.begin(9600);  // Setup serial for monitor
  pinMode(REDLED, OUTPUT);
  pinMode(YELLOWLED, OUTPUT);
  pinMode(GREENLED, OUTPUT);
  Serial1.begin(9600);   // Setup Serial1 for BlueTooth
}

void loop() 
{  
  if(Serial1.available() > 0)
  { // Checks whether data is comming from the serial port
    
    component_componentStatus = Serial1.readStringUntil('\n');
    component_componentStatus.trim();
    Serial.println(component_componentStatus);
    
    if(component_componentStatus == "RL_ON")
    {
    digitalWrite(REDLED, HIGH);
    }
    else if(component_componentStatus == "RL_OFF")
    {
    digitalWrite(REDLED, LOW);
    }
    
    if(component_componentStatus == "GL_ON")
    {
    digitalWrite(GREENLED, HIGH);
    }
    else if(component_componentStatus == "GL_OFF")
    {
    digitalWrite(GREENLED, LOW);
    }
    
    if(component_componentStatus == "YL_ON")
    {
    digitalWrite(YELLOWLED, HIGH);
    }
    else if(component_componentStatus == "YL_OFF")
    {
    digitalWrite(YELLOWLED, LOW);
    }
  }
}
