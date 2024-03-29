//DHT11 and NodeMCU with Blynk
//----------------------------
//Libraries used
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <DHT.h>
#include <ThingSpeak.h>
#include <BlynkSimpleEsp8266.h>

//Blynk Setup
//------------
#define BLYNK_PRINT Serial
/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL6b-30xqrI"   // change to your own template ID
#define BLYNK_TEMPLATE_NAME "Temperature Monitoring"   // change to your own template name
#define BLYNK_AUTH_TOKEN "0gVYxFAcv-074X82yK9c8x8ZE8gkn_64"  // change to your own Blynk_auth_token
BlynkTimer timer;

int LED = D4;

//ThingSpeak Setup
long myChannelNumber = 2079878; // change to your own channel number
const char myWriteAPIKey[] = "9SGWYN7TZ78N0NZJ";  // change to your own API Write Key

//Temperature & Humidity Setup
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
//#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321

uint8_t DHTPin = D6;
DHT dht(DHTPin, DHTTYPE);
float Temperature;
float Humidity;
float Temp_Fahrenheit;

// Your WiFi credentials.
// Set password to "" for open networks. 
const char *ssid =  "myiot";  // change to your own SSID @ hotspot
const char *pass =  "myiot2022";  // change to your own Password
WiFiClient client;

BLYNK_WRITE(V2){    //// V2 correspond to the Virtual pin for LED datastream set on Blynk2.0
  int switchStatus = param.asInt();
  digitalWrite(LED, switchStatus);
}

void sendSensor(){
//Sensor Readings
  Humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  Temperature = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  Temp_Fahrenheit= dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(Humidity) || isnan(Temperature) || isnan(Temp_Fahrenheit)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

//display temperature and humidity to Serial Monitor
  Serial.print(F("Humidity: "));
  Serial.print(Humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(Temperature);
  Serial.print(F("°C "));
  Serial.print(Temp_Fahrenheit);
  Serial.println(F("°F "));
  delay(1000);

// Sending data to ThingSpeak
//----------------------------
  ThingSpeak.setField(1, Temperature); // set temperature values to Field 1
  ThingSpeak.setField(2, Humidity);    // set humidity values to Field 2

// write all data to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  delay(20000); // Wait 20 seconds to update the channel again

  // Sending data to Blynk IoT
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, Temperature);  // V0 correspond to the Virtual pin for Temperature datastream set on Blynk2.0
  Blynk.virtualWrite(V1, Humidity);   // V1 correspond to the Virtual pin for Humidity datastream set on Blynk2.0
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  // Initialize serial
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
    WiFi.mode(WIFI_STA); 
  pinMode(LED, OUTPUT);   
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); //Initialized Blynk
  dht.begin();  // Initialized DHT11 sensor
  ThingSpeak.begin(client);  // Initialize ThingSpeak

// Setup a function to be called every 1 seconds
  timer.setInterval(1000L, sendSensor);

}
 
void loop() {
  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }

  Blynk.run();
  timer.run();
}

