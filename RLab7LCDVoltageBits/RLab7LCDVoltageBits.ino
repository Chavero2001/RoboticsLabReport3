//Voltmeter with LCD
//Using LCD, including libraries, analog intput
/*
Arduino will use analogRead to read a voltage in Bits, then it will convert the bits into actual Voltage.
The voltage and the bits values will be displayed in a LCD
*/

#include <LiquidCrystal.h> //Include Liquid Crystal library to use LCD


const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //Define the LCD pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //Declare the LCD pins in use

float sensor; //Define sensor, where the value of AnalogRead will be stored
float v; //v as the variable of voltage
int v2; //Since sensor is declared as a float, this part displays the sensor value without decimals

void setup() {
  // put your setup code here, to run once:
//pinMode(A0,INPUT_PULLUP); //define pin for analog input (Not necessary)
pinMode(9,OUTPUT); //define pin to control LCD brightness instead of using a resistor 
  lcd.begin(16, 2); 
  Serial.begin(9600); //initialize serial monitor
  // Print a message to the LCD.

}

void loop() {
  // put your main code here, to run repeatedly:
analogWrite(9,60); //gives brightness to the LCD
sensor=analogRead(A0); //Reads the bitvalue
v=sensor/(1023/5); //Converts from bits to voltage
v2=sensor; //Converts float to int

lcd.setCursor(0, 0); //THIS INDICATES THE DIRECTION ON THE LCD
Serial.print(v); //THIS PRINTS THE VOLTAGE
Serial.println(); //Separate to another line
lcd.print("Voltage "); //Prints "Voltage" in the LCD
lcd.print(v); //Prints the value of the voltage

lcd.setCursor(0, 1); //THIS INDICATES THE DIRECTION ON THE LCD
Serial.print(sensor); //THIS PRINTS THE BIT VALUE
Serial.println(); 
lcd.print("Bitvalue "); //Prints "Bitvalue" in the LCD
lcd.print(v2); //Prints the value of bits



}
