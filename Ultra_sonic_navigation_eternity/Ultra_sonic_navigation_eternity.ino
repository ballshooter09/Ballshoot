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
int posFinal;
int Pos1 =180;
int Pos2 =0;
int distPos1;
int distPos2;
int minDist=400;
int muestras=4;
int errors=0;
int aux =0;
int mediana =1+ (muestras/2);
int values[] = { 0, 0, 0, 0, 0 };
long duration, distance, realDistance, oldDistance; // Duration used to calculate distance
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
 pinMode(8, OUTPUT);
}
//////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
void loop() {
  int m;
/* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */ 
for(int j = 0; j <= 300; j+= 5)  // goes from 0 degrees to 180 degrees 
  {      // in steps of 1 degree 
     if (j<150) {
       pos = j + 25;
     }
     else pos = 325 - j;
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
     if (( realDistance < minDist )&&(pos>35)&&(pos<165)){
      minDist=realDistance;
      Pos1=pos;
     }
     distPos1=minDist+2;
     distPos2=minDist-2;
     if ( (realDistance <= distPos1) && (realDistance >= distPos2) ){
      if (pos<Pos1){
        Pos1=pos;
      }
      if (pos>Pos2){
        Pos2=pos;
      } 
     }
     //Serial.println(values[3]);
     //delay(50);
  }
  posFinal=(Pos1+Pos2)/2;
  myservo.write(posFinal);
  oldDistance=minDist;
Pos1 =180;
Pos2 =0;
minDist=400;
delay(500);
while ( true ){
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
     if (aux<3){
        oldDistance=realDistance;
        aux=aux+1;
      }
     Serial.println(realDistance);
     Serial.println(oldDistance);
     if((realDistance >= oldDistance+4) || (realDistance <= oldDistance-3)){
      Serial.println("Falle");
      errors=errors+1;
      if (errors==5){
        errors=0;
        aux=0;
        break;
      }
     }
}
}

