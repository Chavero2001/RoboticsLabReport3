// DHT Temperature & Humidity Sensor
//Connecting sensors, including libraries, LCD
//Arduino will be conncected to a DHT11 sensor, it will give data for the temperature and the humidity. Those values will be displayed in the Serial Monitor and in a LCD.

//Include libraries for the sensor
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 10     // Digital pin connected to the DHT sensor 

// Type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11

//This part is for the LCD
#include <LiquidCrystal.h> //Include library for LCD

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //Define pins for LCD
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//

DHT_Unified dht(DHTPIN, DHTTYPE); 

uint32_t delayMS;

void setup() {
  Serial.begin(9600); //Initialize Serial monitor
  // Initialize DHT
  dht.begin();
  Serial.println(F("DHT11"));
  // Prints temperature sensor details
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Prints humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details
  delayMS = sensor.min_delay / 1000;

//For the LCD
  pinMode(6,OUTPUT); //Pin that controls LCD brightness
  lcd.begin(16,2); //Initialize LCD
  }

void loop() {
  // Delay between measurements.
  delay(delayMS);

  // Get temperature event and print its value.
  sensors_event_t event;
  
analogWrite(6,60); //Uses analog output to control the brightness of the LCD

  dht.temperature().getEvent(&event);
  
    Serial.print(F("Temperature: ")); //Prints value for temperature in the Serial monitor
    Serial.print(event.temperature);
    Serial.println(F("°C"));
    
    lcd.setCursor(0,0); //Determines the position in which temperature will be printed
    lcd.print("T: "); //Prints value for temperature in the LCD
    lcd.print(event.temperature);
    lcd.print(" C");
  
  dht.humidity().getEvent(&event);
  
    Serial.print(F("Humidity: ")); //Prints value for humidity in the Serial monitor
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
    
    lcd.setCursor(0,1); //Determine the position in which humidity will be printed
    lcd.print("H: "); //Prints value for humidity in the LCD
    lcd.print(event.relative_humidity);
    lcd.print("%");

}
