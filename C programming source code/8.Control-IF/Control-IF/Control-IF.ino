
// These constants won't change:
const int ledPin = D2; // pin that the LED is attached to
void setup() {
 // initialize the LED pin as an output:
 pinMode(ledPin, OUTPUT);
 // initialize serial communications:
 Serial.begin(9600);
}
void loop() {
 // declare local variable
   char user_input;
  
  if (Serial.available() > 0) {    // is a character available?
    user_input = Serial.read();       //
    if (user_input == 'a') {
      digitalWrite(ledPin, HIGH);
    }
    if (user_input == 'b') {
      digitalWrite(ledPin, LOW);
    }
  }
 
}
