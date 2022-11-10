// Ultrasonic, DHT & LCD
//Using multiple sensors, including libraries. 
//Arduino will use an ultrasonic sensor to print the distance from the sensor to an object.
/*
  The presicion will be improved with the help of a temperature and humidity sensor, the DHT11,
  since the temperature and the humidity affect the sound speed.
  After the arduino makes the calculation, the value will be printed in the Serial monitos and a LCD.
*/

//This part is for the LCD
#include <LiquidCrystal.h> //Includes library to use LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //Define de pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //Link the pins to the LCD

//This part for the DHT and ultrasonic
#include "DHT.h"; //Include library for the DH11 sensor
 
// Include NewPing Library
#include "NewPing.h" //Include library to improve Ultrasonic sensor presicion
 
// Define Constants
 
#define DHTPIN 7       // DHT11 Output Pin connection
#define DHTTYPE DHT11   // Define the type of the DHT sensor


#define TRIGGER_PIN  10 //Pin that is connected to the Trigger pin
#define ECHO_PIN     13 //Pin that is connected to the Echo pin
#define MAX_DISTANCE 400
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); //Initialize Ultrasonic sensor
 
// Define Variables
 
float hum;    // Stores humidity value in percent
float temp;   // Stores temperature value in Celcius
float duration; // Stores HC-SR04 pulse duration value
float distance; // Stores calculated distance in cm
float soundsp;  // Stores calculated speed of sound in M/S
float soundcm;  // Stores calculated speed of sound in cm/ms
int iterations = 5;
 
// Initialize DHT sensor for normal 16mhz Arduino
 
DHT dht(DHTPIN, DHTTYPE); //Define DHT11 

uint32_t delayMS;

void setup() {
 
  Serial.begin (9600); //Initialize Serial monitor
  dht.begin(); //Initialize DHT11 
  
//For the LCD
  pinMode(6,OUTPUT); //Pin that controls LCD brightness
  lcd.begin(16,2); //Initialize LCD
  }

void loop() {
  
analogWrite(6,60); //It controls LCD britghtness

 
 delay(2000);  // Delay so DHT11 sensor can stabalize
   
    hum = dht.readHumidity();  // Get Humidity value
    temp= dht.readTemperature();  // Get Temperature value
    
    // Calculate the speed of sound in M/S
    soundsp = 331.4 + (0.606 * temp) + (0.0124 * hum);
    

    // Convert to cm/ms
    soundcm = soundsp / 10000;
    
  duration = sonar.ping_median(iterations);
  
  // Calculate the distance
  distance = (duration / 2) * soundcm;
  
  // Send results to Serial Monitor
  
    Serial.print("Sound: ");
    Serial.print(soundsp); //Print the speed 
    Serial.print(" m/s, ");
    Serial.print("Humid: ");
    Serial.print(hum); //Print the humidity
    Serial.print(" %, Temp: ");
    Serial.print(temp); //Print the temperature
    Serial.print(" C, ");
    Serial.print("Distance: ");
    lcd.setCursor(0,0); //Position to print in the LCD display
    lcd.print("Distance: ");
 
    if (distance >= 400 || distance <= 2) { 
    /*If the distance is to far or to close, Arduino prints "Out of range" 
    in both serial monitor and LCD display*/
    Serial.print("Out of range");
    lcd.setCursor(0,1);
    lcd.print("Out of range");

    }
    else {
/*
     If the distance is between the range, then it will be printed in both
     serial monitor and LCD display 
*/    
    Serial.print(distance);
    lcd.setCursor(0,1);
    lcd.print(distance);
    lcd.print("cm            "); //The spaces are to clear if there are numbers on the LCD display
    Serial.print(" cm");
    delay(500);
    }
  
  Serial.println(" ");
}

