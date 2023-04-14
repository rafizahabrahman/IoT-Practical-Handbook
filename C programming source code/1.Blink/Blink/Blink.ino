/*
 ESP8266 Blink by Simon Peter
 Blink the blue LED on the ESP-01 module
 This example code is in the public domain
 The blue LED on the ESP-01 module is connected to GPIO1 
 (which is also the TXD pin; so we cannot use Serial.print() at the same time)
*/

int LED = D2;                       //Connect an LED to pin D2 or GPIO4

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(LED, OUTPUT);             // led
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, LOW);   // Turn the built-in LED ON (Note that LOW is the voltage level
                                    // but actually the LED is on; this is because 
                                    // it is active low on the ESP-01)
  delay(1000);                      // Wait for a second (1000=1second)
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(2000);                      // Wait for two seconds (to demonstrate the active low built in LED)

  digitalWrite(LED, HIGH);          // Turn the LED connected to D2 ON 
  delay(1000);                      // Wait for a second (1000=1second)
  digitalWrite(LED, LOW);           // Turn the LED OFF by making the voltage LOW
  delay(2000);                      // Wait for two seconds (to demonstrate the active high LED)
}
