/*
Switch Case Statement
Demonstrates the use of a switch case statement. The switch case
statement allows you to choose from among a set of discrete values
of a variable. It’s like a series of if statements.
created 1 Jul 2009
modified 9 Apr 2012
by Tom Igoe
modified 9 Sept 2012
by Michael James
This example code is in the public domain.
http://www.arduino.cc/en/Tutorial/SwitchCase
*/
const int min_ = 0;       // Lowest reading at analog pin
const int max_ = 1023;    // Highest reading at analog pin
void setup() {
 // initialize serial communication:
 Serial.begin(9600);
}
void loop() {

   // read the sensor:
   int sensorReading = analogRead(A0);
  
   // map the sensor range to a range of four options:
   int range = map(sensorReading, min_, max_, 0, 3);
  
   // do something different depending on the
   // range value:
   switch (range) {
   case 0: //Potentiometer turned between 0-25%
   Serial.println("low");
   break;
   case 1: //Potentiometer turned upto 26-50%
   Serial.println("medium");
   break;
   case 2:   //Potentiometer turned upto 51-75%
   Serial.println("high");
   break;
   case 3:   //Potentiometer turned upto 76-100%
   Serial.println("ridiculous high");
   break;
   }
   delay(1);         // delay in between reads for stability
}
