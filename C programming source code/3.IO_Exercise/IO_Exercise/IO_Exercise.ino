
int ledPin = D2;    
int ButtonPin = D0;


void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(ButtonPin,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonValue = digitalRead(ButtonPin);
  digitalWrite(ledPin, buttonValue);

}
