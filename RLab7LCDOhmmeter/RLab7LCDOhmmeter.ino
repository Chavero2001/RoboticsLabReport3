//Ohmmeter & LCD
//LCD, analog input, Ohm's Law and libraries
//Using the voltage and Ohm's law, arduino will give the value of an unknown resistor.


#include <LiquidCrystal.h> //Library to use LCD

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //define pins for LCD
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); 

float sensor; //Variable in which analogRead will be stored 
float v; //Variable for the voltage
float Rx; //Variable for unnkown resistor 
float I; //Value of the current
int Rx2; //Convert the value of the resistor from float to int

byte ohm[8] = { //This part is to create Ohm's symbol for the LCD
  B00000,
  B01110,
  B10001,
  B10001,
  B10001,
  B01010,
  B11011,
  B00000
};

void setup() {
  // put your setup code here, to run once:
//pinMode(A0,INPUT_PULLUP); //define pin for analog input (Not necessary)
pinMode(9,OUTPUT); //Pin that controls LCD brightness
  lcd.createChar(0,ohm);
  lcd.begin(16, 2); //Initialize lcd
  Serial.begin(9600); //Initialize Serial monitor
  // Print a message to the LCD.
  

}

void loop() {

analogWrite(9,60);
sensor=analogRead(A0); //HERE IT READS IN BITS
v=sensor/(1023/5);  //The value sensor is a number between 0 and 255, so the first thing is to make a convertion to know the voltage
//1023/5 comes from the general ecuation for the system y=1023x/5 or x=y/(1023/%), where x is v and y is sensor

I=(5-v)/220; //Once with the voltage, it is possible to know the Current with the resistor that is known
//220 is the value of the resistor known

Rx=v/I; //Since the Voltage and the Current are obtained, using Ohm's Law allows us to know the value of the unknown resistor
Rx2=Rx; //Convert from float to int to have a clearer number



lcd.setCursor(0, 0); //THIS INDICATES THE DIRECTION ON THE LCD
Serial.print(Rx); //THIS PRINTS THE RESISTANCE IN THE SERIAL MONITOR
Serial.println();
lcd.print("Resistance ");
lcd.setCursor(0, 1); //THIS INDICATES THE DIRECTION ON THE LCD
lcd.print(Rx2); //PRINTS THE VALUE OF THE RESISTANCE ON THE LCD
lcd.write(byte(0)); //PRINTS OHM'S SYMBOL ON LCD
delay(1000); //Gives time to print the value on the lcd before writing the next one
lcd.clear(); //eraeses previous value before starting again



}




