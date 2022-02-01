#include <Keypad.h>
#include <Wire.h>
#include <dht.h>
#define DATA_PIN 2
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include<stdio.h>

LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7);
dht DHT;

int sensorPin = A0; 
int sensorValue;  
const int kipas = 3;
const int pompa = 4;
const int lampu = 5;
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {13,12, 11, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


int counter = 0; 
int attempts = 0; 
int max_attempts = 2;
String myhum;
int kelembaban = 0;
String myhum2;
int kelembaban2 = 0;

String myt1;
int i_suhu1 = 0;
String myt2;
int i_suhu2 = 0;
int secflag = 0; 

int relayON = LOW;
int relayOFF = HIGH;

void setup() {
  pinMode (kipas, OUTPUT);
  pinMode(pompa, OUTPUT);
  pinMode(lampu, OUTPUT);
  
  digitalWrite(kipas, relayOFF);
  digitalWrite(pompa, relayOFF);
  digitalWrite(lampu, relayOFF);
 
  lcd.begin (16,2); // LCD 16x2
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.setCursor(3,0);
  lcd.print("Penyiraman");
  lcd.setCursor(4,1);
  lcd.print("Otomatis");

    delay(3000); 
    lcd.clear();
    lcd.print("Min Kelembaban :");
}

void loop() {   
 keypadfunction();
}

void keypadfunction()
{ 
 char key = keypad.getKey();
  
  if (key){
    Serial.println(key);
    counter = counter + 1; 
    lcd.setCursor(counter, 1);
    lcd.print(key);
  }
  if (key == '1')
  {

    myhum = myhum + 1;   
  }
  
    if (key == '2')
  {

    myhum = myhum + 2;  
  }
  
  if (key == '3')
  {
 
    myhum = myhum + 3; 
  }
  
   if (key == '4')
  {
  
    myhum = myhum + 4;  
  }
  
  if (key == '5')
  {
  
    myhum = myhum + 5;
  }
  
   if (key == '6')
  {
   
    myhum = myhum + 6; 
  }
  
   if (key == '7')
  {

    myhum = myhum + 7; 
  }

   if (key == '8')
  {

    myhum = myhum + 8; 
  }
  
  if (key == '9')
  {

    myhum = myhum + 9;
  }
             
    if (key == '0')
  {

    myhum = myhum + 0; 
  }

    if (key == '#')
  {
    counter = 0;
    myhum = ""; 
    kelembaban = 0;
    myhum2 = "";
    kelembaban2 = 0;  
    myt1 = ""; 
    i_suhu1 = 0; 
    myt2 = ""; 
    i_suhu2 = 0;  

    lcd.clear(); 
    lcd.setCursor(0,0); 
    lcd.print("Max Kelembaban :"); 
}
if (key == '*')
  {
lcd.clear();     
kelembaban = myhum.toInt();
//Serial.println(minutes);
lcd.clear(); 
lcd.print("Min Kelembaban : "); 
lcd.setCursor(1,1); 
lcd.print(kelembaban); 
myhum = ""; // empty the string
delay(3000); 
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Max Kelembaban :");
counter = 0; 
secflag = 1; 

while(secflag == 1)
{
batasKelembaban(); 
}    
  }
} 

void batasKelembaban()
{ 
 char key = keypad.getKey();
  
  if (key){
    Serial.println(key);
    counter = counter + 1; 
    lcd.setCursor(counter, 1);
    lcd.print(key);
  }
  if (key == '1')
  {

    myhum2 = myhum2 + 1;   
  }
  
    if (key == '2')
  {

    myhum2 = myhum2 + 2;  
  }
  
  if (key == '3')
  {
 
    myhum2 = myhum2 + 3; 
  }
  
   if (key == '4')
  {
  
    myhum2 = myhum2 + 4;  
  }
  
  if (key == '5')
  {
  
    myhum2 = myhum2 + 5;
  }
  
   if (key == '6')
  {
   
    myhum2 = myhum2 + 6; 
  }
  
   if (key == '7')
  {

    myhum2 = myhum2 + 7; 
  }

   if (key == '8')
  {

    myhum2 = myhum2 + 8; 
  }
  
  if (key == '9')
  {

    myhum2 = myhum2 + 9;
  }
             
    if (key == '0')
  {

    myhum2 = myhum2 + 0; 
  }

    if (key == '#')
  {

    counter = 0;
    myhum = "";
    kelembaban = 0;
    myhum2 = ""; 
    kelembaban2 = 0;  
    myt1 = ""; 
    i_suhu1 = 0; 
    myt2 = ""; 
    i_suhu2 = 0;  

    lcd.clear(); 
    lcd.setCursor(0,0); 
    lcd.print("Min Suhu :"); 
}
if (key == '*')
  {
lcd.clear();     
kelembaban2 = myhum2.toInt();
//Serial.println(minutes);
lcd.clear(); 
lcd.print("Max Kelembaban : "); 
lcd.setCursor(1,1); 
lcd.print(kelembaban2); 
myhum = ""; // empty the string
delay(3000); 
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Min Suhu :");
counter = 0; 
secflag = 1; 

while(secflag == 1)
{
minSuhu(); 
}    
  }
}

void minSuhu()
{ 
 char key = keypad.getKey();
  
  if (key){
    Serial.println(key);
    counter = counter + 1; 
    lcd.setCursor(counter, 1);
    lcd.print(key);
  }
  if (key == '1')
  {

    myt1 = myt1 + 1;   
  }
  
    if (key == '2')
  {

    myt1 = myt1 + 2;  
  }
  
  if (key == '3')
  {
 
    myt1 = myt1 + 3; 
  }
  
   if (key == '4')
  {
  
    myt1 = myt1 + 4;  
  }
  
  if (key == '5')
  {
  
    myt1 = myt1 + 5;
  }
  
   if (key == '6')
  {
   
    myt1 = myt1 + 6; 
  }
  
   if (key == '7')
  {

    myt1 = myt1 + 7; 
  }

   if (key == '8')
  {

    myt1 = myt1 + 8; 
  }
  
  if (key == '9')
  {

    myt1 = myt1 + 9;
  }
             
    if (key == '0')
  {

    myt1 = myt1 + 0; 
  }

    if (key == '#')
  {

    counter = 0;
    myhum = "";
    kelembaban = 0;
    myhum2 = ""; 
    kelembaban2 = 0;  
    myt1 = ""; 
    i_suhu1 = 0; 
    myt2 = ""; 
    i_suhu2 = 0;  

    lcd.clear(); 
    lcd.setCursor(0,0); 
    lcd.print("Max Suhu :"); 
}
if (key == '*')
  {
lcd.clear();     
i_suhu1 = myt1.toInt();
//Serial.println(minutes);
lcd.clear(); 
lcd.print("Min Suhu : "); 
lcd.setCursor(1,1); 
lcd.print(i_suhu1); 
myhum = ""; // empty the string
delay(3000); 
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Max Suhu :");
counter = 0; 
secflag = 1; 

while(secflag == 1)
{
maxSuhu(); 
}    
  }
}

void maxSuhu()
{ 
 char key = keypad.getKey();
  
  if (key){
    Serial.println(key);
    counter = counter + 1; 
    lcd.setCursor(counter, 1);
    lcd.print(key);
  }
  if (key == '1')
  {

    myt2 = myt2 + 1;   
  }
  
    if (key == '2')
  {

    myt2 = myt2 + 2;  
  }
  
  if (key == '3')
  {
 
    myt2 = myt2 + 3; 
  }
  
   if (key == '4')
  {
  
    myt2 = myt2 + 4;  
  }
  
  if (key == '5')
  {
  
    myt2 = myt2 + 5;
  }
  
   if (key == '6')
  {
   
    myt2 = myt2 + 6; 
  }
  
   if (key == '7')
  {

    myt2 = myt2 + 7; 
  }

   if (key == '8')
  {

    myt2 = myt2 + 8; 
  }
  
  if (key == '9')
  {

    myt2 = myt2 + 9;
  }
             
    if (key == '0')
  {

    myt2 = myt2 + 0; 
  }

    if (key == '#')
  {

    counter = 0;
    myhum = ""; 
    kelembaban = 0;  
    myt1 = ""; 
    i_suhu1 = 0; 
    myt2 = ""; 
    i_suhu2 = 0;  
}
if (key == '*')
  {
lcd.clear();     
i_suhu2 = myt2.toInt();
Serial.println(i_suhu2);
lcd.clear();
lcd.setCursor(0,0); 
lcd.print("Max Suhu : "); 
lcd.setCursor(1,1); 
lcd.print(i_suhu2); 
myt1 = ""; // empty the string
delay(3000); 
lcd.clear();
lcd.setCursor(0,0);
 
while( kelembaban != 0 && kelembaban2 != 0 && i_suhu1 != 0 && i_suhu2 != 0)
{
   char key = keypad.getKey();
  int readData = DHT.read22(DATA_PIN); // baca Data dari sensor
  float t = DHT.temperature; // Ambil nilai Suhu
  //float h = DHT.humidity;
 sensorValue = analogRead(sensorPin);
  if (sensorValue >= kelembaban && sensorValue <= kelembaban2) {
      //digitalWrite(pompa, relayOFF);
      digitalWrite(lampu, relayOFF);
      } else if (sensorValue < kelembaban){
        digitalWrite(pompa, relayON);
        //digitalWrite(lampu, relayOFF);
      }
      else if (sensorValue > kelembaban2){
        digitalWrite(pompa, relayOFF);
        //digitalWrite(lampu, relayON);
      }
        if (t >= i_suhu1 && t <= i_suhu2) {
         digitalWrite(kipas, relayOFF);
         digitalWrite(lampu, relayOFF);
        } else if (t < i_suhu1) {
        digitalWrite(lampu, relayON);
        digitalWrite(kipas, relayOFF);
        }else if (t > i_suhu2) {
        digitalWrite(kipas, relayON);
        digitalWrite(lampu, relayOFF);
        }
      
        lcd.print("Kelembaban Suhu"); 
        lcd.setCursor(4,1); 
        lcd.print(sensorValue/10); 
        lcd.setCursor(11,1); 
        lcd.print(t);
        delay(5000);
    }
}
}
