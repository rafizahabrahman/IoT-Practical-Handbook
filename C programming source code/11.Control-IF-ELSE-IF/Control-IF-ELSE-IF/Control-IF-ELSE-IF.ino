
// These constants won't change:
const int ledPin1 = D2; // pin that the LED is attached to
const int ledPin2 = D5; // pin that the LED is attached to
const int ledPin3 = D8; // pin that the LED is attached to

void setup() {
 // initialize the LED pin as an output:
 pinMode(ledPin1, OUTPUT);
 pinMode(ledPin2, OUTPUT);
 pinMode(ledPin3, OUTPUT);
 // initialize serial communications:
 Serial.begin(9600);
}

char user_input = 0;

void loop(){
if (Serial.available() > 0) {    // is a character available?
    char user_input = Serial.read();
  
  if (user_input == 'a' || user_input == 'A') {
    // the character 'a' was received, blink the LED once per second
    digitalWrite(ledPin1, HIGH);  // switch the LED on
    delay(500);              // leave the LED on for 500ms
    digitalWrite(ledPin1, LOW);   // switch the LED off
    delay(500);              // leave the LED off for 500ms
  }
//  else if (user_input == 'b') {
//    // the character 'b' was received, blink the LED every 400ms
//    digitalWrite(ledPin2, HIGH);  // switch the LED on
//    delay(200);              // leave the LED on for 200ms
//    digitalWrite(ledPin2, LOW);   // switch the LED off
//    delay(200);              // leave the LED off for 200ms
//  }
  else {
    // any character except 'a' or 'b' was received
    digitalWrite(ledPin3, HIGH);  // switch the LED on
    delay(100);              // leave the LED on for 100ms
    digitalWrite(ledPin3, LOW);   // switch the LED off
    delay(100);              // leave the LED off for 100ms
    }
  }
}  
