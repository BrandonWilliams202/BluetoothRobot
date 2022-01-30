//libraries
#include <Servo.h>
#include <SoftwareSerial.h>

///////Vars//////////
char incomingByte;  // incoming data
int forwardDistance = 0;
Servo myservo;
#define carSpeed 150
#define turnSpeed 180
#define BT_SERIAL_RX 0
#define BT_SERIAL_TX 1
SoftwareSerial BluetoothSerial(BT_SERIAL_RX, BT_SERIAL_TX);

///////////Pins L298N to IO/////////////////
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

//Ultrasonic to IO
#define Echo A4
#define Trig A5

void setup() 
{
  Serial.begin(9600); 
  BluetoothSerial.begin(9600);
  myservo.attach(3);     
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT); 
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

void left()
{
  analogWrite(ENA, turnSpeed);
  analogWrite(ENB, turnSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void right()
{
  analogWrite(ENA, turnSpeed);
  analogWrite(ENB, turnSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

int sonarDistance()
{
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);   
  float timeLen = pulseIn(Echo, HIGH);  
  float distance = timeLen * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)       
  return (int)distance;
}

void loop()
{
  //send sonar data
  forwardDistance = sonarDistance();
  Serial.println(forwardDistance);
//  BluetoothSerial.write("test");
  
  if(Serial.available() > 0)// Checks whether data is comming from the serial port
  {
    incomingByte = Serial.read();

    //sonar
    if(incomingByte == 'p') {
       int angle = myservo.read();
       if(angle >= 20){
          myservo.write(angle-10);
       }
    }
    if(incomingByte == 'o') {
       int angle = myservo.read();
       if(angle <= 160){
          myservo.write(angle+10);
       }
    }
    
    //movement
    if(incomingByte == 'w') {
       forward();
    }
    if(incomingByte == 'a') {
       left();
    }
    if(incomingByte == 'd') {
       right();
    }
    if(incomingByte == 's') {
       brake();
    }
    
    Serial.print(incomingByte);
  }
}
