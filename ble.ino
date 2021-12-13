//libraries
#include <Servo.h>

///////Vars//////////
char incomingByte;  // incoming data
#define carSpeed 150
Servo myservo;

///////////Pins L298N to IO/////////////////
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

void setup() 
{
  Serial.begin(9600); 
  myservo.attach(3);     
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  myservo.write(86);    //86 is straight(physical offeset)
}

void forward()
{
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void brake()
{
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}

void loop()
{
  if(Serial.available() > 0)// Checks whether data is comming from the serial port
  {
    incomingByte = Serial.read();

    if(incomingByte == '0') {
       myservo.write(60);
    }
    if(incomingByte == '1') {
       myservo.write(120);
    }
    Serial.print(incomingByte);
  }
}
