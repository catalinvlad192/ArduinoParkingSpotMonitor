#include <SoftwareSerial.h>
#include <Servo.h>
#include "SensorHC.h"

//Servo motor and pin
Servo myBarrier;
#define servoPin 10

//LEDs for showing spot availability
#define redLed 13
#define greenLed 12

//distance sensor1 pins
#define echoPin1 A0
#define trigPin1 A1

//distance sensor2 pins
#define echoPin2 A2
#define trigPin2 A3

//7 segment display
#define a 2  //For displaying segment "a"
#define b 3  //For displaying segment "b"
#define c 4  //For displaying segment "c"
#define d 5  //For displaying segment "d"
#define e 6  //For displaying segment "e"
#define f 8  //For displaying segment "f"
#define g 9  //For displaying segment "g"

//First sensor, distance detected and previous distance detected
SensorHC sensor1(echoPin1, trigPin1);
long distance1;
long prevDistance1 = 999;

//Second sensor, distance detected and previous distance detected
SensorHC sensor2(echoPin2, trigPin2);
long distance2;
long prevDistance2 = 999;

//Integer to 7 segments display format
void segmentDisplay(int number);

//Number of parking spots
int number = 9;

void setup() {
  // put your setup code here, to run once:

  //////////////////////////////////////////////////////////////////////////
  myBarrier.attach(servoPin);
  myBarrier.write(150);

  //For displaying in arduino console
  Serial.begin(9600);
  
  //setup pins for first sensor 
  pinMode(trigPin1, OUTPUT); 
  pinMode(echoPin1, INPUT);

  //setup pins for second sensor
  pinMode(trigPin2, OUTPUT); 
  pinMode(echoPin2, INPUT);
  
  //setup LED pins
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  //setup 7-segment display
  pinMode(a, OUTPUT);  //A
  pinMode(b, OUTPUT);  //B
  pinMode(c, OUTPUT);  //C
  pinMode(d, OUTPUT);  //D
  pinMode(e, OUTPUT);  //E
  pinMode(f, OUTPUT);  //F
  pinMode(g, OUTPUT);  //G
}

void loop() {
  // put your main code here, to run repeatedly:

 //Ping first sensor and get distance
  sensor1.ping();
  distance1 = sensor1.getDistance();

  //Print distance received
  Serial.print("FirstSensor ");
  Serial.print(distance1);
  Serial.println("cm");

  //Check if something passed over the sensor or it's the same object
  if (distance1 <=40 && prevDistance1 >40)
  {
    if (!number)
    {
      //If it's 0 then it shouldn't decrement, so a small signal is shown
      digitalWrite(redLed, LOW);
      delay(250);
      digitalWrite(redLed, HIGH);
      delay(250);
      digitalWrite(redLed, LOW);
      delay(250);
      digitalWrite(redLed, HIGH);
    }
    else{
      number--;
      myBarrier.write(0);
      delay(1000);
      myBarrier.write(150);
    }
  }
  prevDistance1 = distance1;

  //Choose and set the right (green or red) LED
  if (number)
  {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
  } 
  else
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
  }
  segmentDisplay(number);

 //Ping second sensor and get distance
  sensor2.ping();
  distance2 = sensor2.getDistance();

  //Print distance received
  Serial.print("SecondSensor ");
  Serial.print(distance2);
  Serial.println("cm");

  //Check if something passed over the sensor or it's the same object
  if(distance2 <=40 && prevDistance2 >40)
  {
    if (number == 9)
    {
      //If it's the max number of parking spots free, then it shouldn't increment, so a small signal is shown
      digitalWrite(greenLed, LOW);
      delay(250);
      digitalWrite(greenLed, HIGH);
      delay(250);
      digitalWrite(greenLed, LOW);
      delay(250);
      digitalWrite(greenLed, HIGH);
    }
    else
      number++;
  }
  prevDistance2 = distance2;

  //Choose and set the right (green or red) LED
  if (number)
  {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    segmentDisplay(number);
  } 
  else
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    segmentDisplay(number);
  }
}

//integer to 7display format
void segmentDisplay(int number)
{
  switch (number)
  {
    case 0:
    {
      digitalWrite(a,HIGH);
      digitalWrite(b,HIGH);
      digitalWrite(c,HIGH);
      digitalWrite(d,HIGH);
      digitalWrite(e,HIGH);
      digitalWrite(f,HIGH);
      digitalWrite(g,LOW);
      break;
    }
    case 1:
    {
      digitalWrite(a,LOW);
      digitalWrite(b,HIGH);
      digitalWrite(c,HIGH);
      digitalWrite(d,LOW);
      digitalWrite(e,LOW);
      digitalWrite(f,LOW);
      digitalWrite(g,LOW);
      break;
    }
    case 2:
    {
      digitalWrite(a,HIGH);
      digitalWrite(b,HIGH);
      digitalWrite(c,LOW);
      digitalWrite(d,HIGH);
      digitalWrite(e,HIGH);
      digitalWrite(f,LOW);
      digitalWrite(g,HIGH);
      break;
    }
    case 3:
    {
      digitalWrite(a,HIGH);
      digitalWrite(b,HIGH);
      digitalWrite(c,HIGH);
      digitalWrite(d,HIGH);
      digitalWrite(e,LOW);
      digitalWrite(f,LOW);
      digitalWrite(g,HIGH);
      break;
    }
    case 4:
    {
      digitalWrite(a,LOW);
      digitalWrite(b,HIGH);
      digitalWrite(c,HIGH);
      digitalWrite(d,LOW);
      digitalWrite(e,LOW);
      digitalWrite(f,HIGH);
      digitalWrite(g,HIGH);
      break;
    }
    case 5:
    {
      digitalWrite(a,HIGH);
      digitalWrite(b,LOW);
      digitalWrite(c,HIGH);
      digitalWrite(d,HIGH);
      digitalWrite(e,LOW);
      digitalWrite(f,HIGH);
      digitalWrite(g,HIGH);
      break;
    }
    case 6:
    {
      digitalWrite(a,HIGH);
      digitalWrite(b,LOW);
      digitalWrite(c,HIGH);
      digitalWrite(d,HIGH);
      digitalWrite(e,HIGH);
      digitalWrite(f,HIGH);
      digitalWrite(g,HIGH);
      break;
    }
        case 7:
    {
      digitalWrite(a,HIGH);
      digitalWrite(b,HIGH);
      digitalWrite(c,HIGH);
      digitalWrite(d,LOW);
      digitalWrite(e,LOW);
      digitalWrite(f,LOW);
      digitalWrite(g,LOW);
      break;
    }
    case 8:
    {
      digitalWrite(a,HIGH);
      digitalWrite(b,HIGH);
      digitalWrite(c,HIGH);
      digitalWrite(d,HIGH);
      digitalWrite(e,HIGH);
      digitalWrite(f,HIGH);
      digitalWrite(g,HIGH);
      break;
    }
    case 9:
    {
      digitalWrite(a,HIGH);
      digitalWrite(b,HIGH);
      digitalWrite(c,HIGH);
      digitalWrite(d,HIGH);
      digitalWrite(e,LOW);
      digitalWrite(f,HIGH);
      digitalWrite(g,HIGH);
      break;
    }
    default :
    {
      digitalWrite(a,LOW);
      digitalWrite(b,LOW);
      digitalWrite(c,LOW);
      digitalWrite(d,LOW);
      digitalWrite(e,LOW);
      digitalWrite(f,LOW);
      digitalWrite(g,HIGH);
    }
  }
}
