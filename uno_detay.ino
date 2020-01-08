#include <SoftwareSerial.h>
#define buzdolabi 5
#define firin 6   
#define camasir 7
#define bulasik 8

SoftwareSerial mySerial(2, 3); // RX, TX mor 2 ye mavi 3 e
 int kombiKontrol=0;
void setup()
{
 Serial.begin(9600);
 mySerial.begin(9600);
 pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
   pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,INPUT);
 delay(5000);
 }
 
void loop(){
 
 String IncomingString="";
 boolean StringReady = false;
 
 
 while (mySerial.available()){
  
  int sensor = analogRead(A0);
  Serial.println(sensor);
 if(sensor>150 or kombiKontrol==1){
    kombiKontrol=1;
    digitalWrite(11,HIGH);
  }else{
    digitalWrite(11,LOW);
  }
   IncomingString=mySerial.readString();
   StringReady= true;
  }
  delay(500);
  if (StringReady){

   
    Serial.println( IncomingString.charAt(0));
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
    if(kombiKontrol==1){
      digitalWrite(9,HIGH);
      if(IncomingString.charAt(4)=='0'){
        kombiKontrol=0;
      }
    }else{
      if(IncomingString.charAt(4)=='1'){
     digitalWrite(9,LOW);
    }else {
     digitalWrite(9,HIGH);
    }
    }
    
    if(IncomingString.charAt(5)=='1'){
     digitalWrite(10,LOW);
    }else {
      digitalWrite(10,HIGH);
    }
    
  }
 }
