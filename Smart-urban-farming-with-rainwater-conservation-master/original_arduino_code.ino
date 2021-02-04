

#include "DHT.h"
#include <Wire.h> 
#include <BH1750.h>

const int Pump=4;
const int Fan=5;
const int Light=6;
const int TempHum=7;
const int Moisture=8; 
const int TestLED=9; 
const int Brightness=12; 
const int analogMoistue=0;  

#define DHTTYPE DHT11
DHT dht(TempHum, DHTTYPE);  
BH1750 lightMeter;
char Data='x';
String cmd=""; 
float temperature=0; 
float humidity=0;
uint16_t lux=0; 


void setup() 
{
  
  Wire.begin(); 
  dht.begin(); 
  lightMeter.begin(); 
  Serial.begin(9600);
  Serial.setTimeout(100);
  pinMode(Pump,OUTPUT);
  pinMode(Fan,OUTPUT);
  pinMode(Light,OUTPUT);
  pinMode(Moisture,INPUT);
  pinMode(TestLED,INPUT);
  delay(1000);
  digitalWrite(Pump,LOW);
  digitalWrite(Fan,LOW);
  digitalWrite(Light,LOW);
}

void loop() 
{
  while(Serial.available())                                  
  {
    delay(10);
    Data=Serial.read();
    cmd+=Data;
  }
  
  
  
  if(cmd=="aa")   {                                           
    
    Serial.print(humidity);
  Serial.print("||");
  Serial.print(analogRead(analogMoistue));
  Serial.print("||");
  Serial.print(temperature);
  Serial.print("||");
  
  delay(1000);}
  
    if(cmd=="f")                                             // Turn ON the FAN
    {
      analogWrite(Fan,255);
    }
    if(cmd=="x")                                             // Turn OFF the FAN
    {
      analogWrite(Fan,0);
    }
    if( lux<=2)
     analogWrite(Light,255);

    if( lux>3)
     analogWrite(Light,0);
    if(cmd=="w")                                             // Turn ON the Pump
    {
      analogWrite(Pump,255);
    }
    if(cmd=="y")                                             // Turn OFF the Pump
    {
      analogWrite(Pump,0);
    }

  cmd="";                                                    
  lux = lightMeter.readLightLevel();                         
  temperature=dht.readTemperature();                         
  humidity=dht.readHumidity();
  delay(1000);
}
