
int LED = D2;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);

}

void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  Serial.println("Sensor value: ");
  Serial.println(sensorValue);
  delay(1000);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 3.3V):
  float voltage = sensorValue * (5.0 / 1024.0);
  // print out the value you read:
  Serial.println("voltage: ");
  Serial.println(voltage);
  delay(1000);
}
