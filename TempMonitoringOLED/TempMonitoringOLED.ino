//Libraries used
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//OLED Display Setup
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire, -1);
unsigned long delayTime;

//Temperature & Humidity Setup
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
//#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321

uint8_t DHTPin = D6;
DHT dht(DHTPin, DHTTYPE);

float Temperature;
float Humidity;
float Temp_Fahrenheit;

//WiFi Credentials 
const char *ssid =  "yourownssid";  // change to your own SSID @ hotspot
const char *pass =  "yourssidpassword";  // change to your own Password
WiFiClient client;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  // Initialize serial
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  WiFi.mode(WIFI_STA); 
  dht.begin();  // Initialized DHT11 sensor
  
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize OLED Display with the I2C addr 0x3C (for the 128x64)
   // init done
  display.display();
  delay(100);
  display.clearDisplay();
  display.display();
  display.setTextSize(1.75);
  display.setTextColor(WHITE);
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
// display temperature to OLED Display
  display.setCursor(0,0);
  display.clearDisplay();
  display.setTextSize(1.75);
  display.setCursor(0,0);
  display.print("Temp Monitoring");
  display.setTextSize(1);
  display.setCursor(0,16);
  display.print("Temperature: ");
  display.setTextSize(2);
  display.setCursor(0,26);
  display.print(Temperature);
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("C");
  // display humidity
  display.setTextSize(1);
  display.setCursor(0, 41);
  display.print("Humidity: ");
  display.setTextSize(2);
  display.setCursor(0, 51);
  display.print(Humidity);
  display.print(" %"); 
  display.display();
  delay(1000);
}

