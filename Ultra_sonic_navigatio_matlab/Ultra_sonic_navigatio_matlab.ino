/*
 HC-SR04 Ping distance sensor:
 VCC to arduino 5v 
 GND to arduino GND
 Echo to Arduino pin 12
 Trig to Arduino pin 13
 
 Thanks for sort function to https://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm
 */
 

#include <Servo.h>
#define echoPin 12 // Echo Pin
#define trigPin 13 // Trigger Pin


Servo myservo;
int pos;
int inPin = 8;         // the number of the input pin
int outPin = 7;       // the number of the output pin
int reading =0;

int muestras=4;
int mediana =1+ (muestras/2);
int values[] = { 0, 0, 0, 0, 0 };
long duration, distance, realDistance; // Duration used to calculate distance
//long pos = 50;
int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}
void setup() {
 myservo.attach(9); 
 Serial.begin (9600);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(inPin, INPUT);
 pinMode(outPin, OUTPUT);
}
//////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
void loop() {
  int m;
  reading = reading+1;
if (reading == 1){
  for(int j = 0; j <= 180; j+= 1)  // goes from 0 degrees to 180 degrees 
  {      // in steps of 1 degree 
     pos = j;
     myservo.write(pos);               // tell servo to go to position in variable 'pos' 
     for(int n = 0; n <= muestras; n+= 1)
     {
     //ultrasonic
     digitalWrite(trigPin, LOW); 
     delayMicroseconds(2); 

     digitalWrite(trigPin, HIGH);
     delayMicroseconds(10); 
 
     digitalWrite(trigPin, LOW);
     duration = pulseIn(echoPin, HIGH);
     //
 
     //Calculate the distance (in cm) based on the speed of sound.
     distance = duration/58.2;
     values[n]=distance;

     delay(50);
     }
     qsort(values, 5, sizeof(int), cmpfunc);
     realDistance=values[mediana];
     Serial.println(realDistance);

     //Serial.println(values[3]);
     //delay(50);
  }
}
}

