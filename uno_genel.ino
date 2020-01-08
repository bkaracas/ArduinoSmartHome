#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX sarı 2 ye yeşil 3 e
 
void setup()
{
 Serial.begin(9600);
 mySerial.begin(9600);
 pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
   pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
   pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,INPUT);
 delay(5000);
 }
 
void loop(){
 
 String IncomingString="";
 boolean StringReady = false;
 
 
 while (mySerial.available()){
  
   IncomingString=mySerial.readString();
   StringReady= true;
  }
  delay(500);
  if (StringReady){
    int sensor = analogRead(A0);
    Serial.println(sensor);
    //Serial.println( IncomingString.charAt(0));
    if(IncomingString.charAt(0)=='1'){
     digitalWrite(5,LOW);
    }else {
      digitalWrite(5,HIGH);
    }
    
    if(IncomingString.charAt(1)=='1'){
     digitalWrite(6,LOW);
    }else {
      digitalWrite(6,HIGH);
    }
    if(IncomingString.charAt(2)=='1'){
     digitalWrite(7,LOW);
    }else {
      digitalWrite(7,HIGH);
    }
    if(IncomingString.charAt(3)=='1'){
     digitalWrite(8,LOW);
    }else {
      digitalWrite(8,HIGH);
    }

    
    if(IncomingString.charAt(4)=='1' or sensor<100){
      digitalWrite(11,HIGH);
      digitalWrite(10,LOW);
    }else{
      digitalWrite(10,HIGH);
      digitalWrite(11,LOW);
    }
    
    
  }
 }
