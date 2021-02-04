#include <Servo.h>

#define rain_D 4
#define rain_A A0
int d = 1;
int val_s, val_w;

Servo myservo; 


void setup() {
  myservo.attach(6); 
  pinMode(rain_D, INPUT);
  pinMode(rain_A, INPUT);
  Serial.begin(9600);
}


void loop() {
  val_w = analogRead(rain_A);
  val_s = myservo.read();
  if (val_w<500 && d == 0)
  {

      d = 1;
      myservo.attach(6);
      myservo.write(0);
      delay(6000);
      myservo.detach();
  }
  if (val_w>=500 && d == 1)
  {
   
    --d;
    myservo.attach(6);
    myservo.write(180);
    delay(6000);
    myservo.detach();
  
  }
  Serial.print("Analog value : ");
  Serial.println(val_w);
  delay(500);
}
