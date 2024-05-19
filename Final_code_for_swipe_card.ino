// Intelligent Home Automation system
// Created by Rabbi islam

#include <LiquidCrystal_I2C.h>
#include <virtuabotixRTC.h> 
#include <SPI.h>  
#include <MFRC522.h> 
#include <Wire.h> 
#include <Servo.h>
#define SS_PIN 10
#define RST_PIN 9
#define ledRed 5
#define Relay 4
MFRC522 mfrc522(SS_PIN, RST_PIN); 
virtuabotixRTC myRTC(6, 7, 8);
LiquidCrystal_I2C lcd(0x27,16,2);  
  
void setup()   
 {  
  Serial.begin(9600);  
  SPI.begin();    
  lcd.init();             
  lcd.backlight(); 
  lcd.begin(16,2); 
  mfrc522.PCD_Init();
  myRTC.setDS1302Time(10, 23, 11, 5, 4, 6, 2023);    
  pinMode(ledRed, OUTPUT);
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, LOW);  

   
 }


void loop()   
 {  
 myRTC.updateTime();
 lcd.setCursor(0,0);
 
 lcd.print("Date:");
 lcd.print(myRTC.dayofmonth);
 lcd.print("/");
 lcd.print(myRTC.month);
 lcd.print("/");
 lcd.print(myRTC.year);
 lcd.setCursor(0,1);
 
 lcd.print("Time:");
 lcd.print(myRTC.hours);
 lcd.print(":");
 lcd.print(myRTC.minutes);
 lcd.print(":");
 lcd.print(myRTC.seconds);
 delay(100);
  if ( ! mfrc522.PICC_IsNewCardPresent())  // new cards   
  {  
   return;  
  }      
  if ( ! mfrc522.PICC_ReadCardSerial()) // Select the cards  
  {  
   return;  
  }  
  
  
  String content= "";  
  byte letter;  
  for (byte i = 0; i < mfrc522.uid.size; i++)   
  {  
      
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));  
    content.concat(String(mfrc522.uid.uidByte[i], HEX));  
  }  
   
  content.toUpperCase();  
  if (content.substring(1) == "CA CB E9 81") 
    
  {
      
       
     lcd.setCursor(0,0);  
     lcd.print(" CARD IS VALID      ");  
     lcd.setCursor(0,1);  
     lcd.print("Opening the Door   ");
     digitalWrite(Relay, HIGH);
     delay(2000);    
     lcd.setCursor(0,1);  
     lcd.print("closing the Door   ");  
     lcd.clear(); 
     digitalWrite(Relay, LOW);
     delay(2000);
     lcd.setCursor(0,0);  
     lcd.print("Please put your");
     lcd.setCursor(0,1);
     lcd.print("card here...");  
  }  
  
  else   
  { 
    lcd.clear(); 
      
    lcd.print("   Warning!");
    lcd.setCursor(0,1); 
    lcd.print("Card is invalid..");  
    digitalWrite(ledRed, HIGH);   
    delay(1000);  
    digitalWrite(ledRed, LOW);  
    lcd.setCursor(0,1); 
    lcd.clear();
    lcd.print("Please put your");
    lcd.setCursor(0,1);
    lcd.print("card here..."); 
     
  }  
 }  
