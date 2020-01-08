#include <ESP8266WiFi.h>

const char* ssid = "test";//"TTNET_ZyXEL_TNC9";               //"asd";
const char* password =   "mOd8542999"  ;//"03c184659A437"; // "123asd123";
const char* host = "192.168.1.4";
int x=0;
int y[4];
int z[6];
int t=0;
int c=0;
void setup()
{
  Serial.begin(9600);
  Serial.println();

  //Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    //Serial.print(".");
  }
  //Serial.println(" connected");
}


void loop()
{
  x=0;
  WiFiClient client;
  client.setNoDelay(true);
  //Serial.printf("[Connecting to %s ... ", host);
  if (client.connect(host, 80))
  {
    //Serial.println("connected");

    //Serial.println("[Sending get request]");
    client.print(String("GET /cdtp/get_watt2") + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n"
                );
    c=0;
    //Serial.println("[Response:]");
    while (c<4)
    {
      if (client.available())
      {
        String line = client.readStringUntil('*');
        //Serial.println(line);
        x=line.toInt();
       }
       if(x){
        //Serial.println(x);
        y[c]=x;
        c=c+1;
        }
     }
    client.stop();
    //Serial.println("[Disconnected]");
  }
  else
  {
    //Serial.println("connection failed!");
    client.stop();
  }
  
  c=1;
  while(c<4){
    y[c]=y[c]-1000;
    if(y[c]<=0){
      y[c]=1;
    }
    c=c+1;
  }

  x=0;
  client.setNoDelay(true);
  //Serial.printf("[Connecting to %s ... ", host);
  if (client.connect(host, 80))
  {
    //Serial.println("connected");

    //Serial.println("[Sending get request]");
    client.print(String("GET /cdtp/get_comps3") + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n"
                );
    c=0;
    //Serial.println("[Response:]");
    while (c<6)
    {
      if (client.available())
      {
        String line = client.readStringUntil('*');
        //Serial.println(line);
        x=line.toInt();
       }
       if(x){
        //Serial.println(x);
        z[c]=x;
        c=c+1;
        x=0;
        }
     }
    client.stop();
    //Serial.println("[Disconnected]");
  }
  else
  {
    //Serial.println("connection failed!");
    client.stop();
  }
  c=0;
  while(c<6){
    if(z[c]!=1){
      z[c]=0;
    }
    c=c+1;
  }
  int v=z[0]*180+z[1]*100+z[2]*190+z[3]*120+z[4]*40+z[5]*50;
  y[0]=y[0]-v;
  if(y[0]<1){
    y[0]=1;
  }
  int a1=y[0];
  int a2=y[1];
  int a3=y[2];
  int a4=y[3];
  String b1=String(a1);
  String b2=String(a2);
  String b3=String(a3);
  String b4=String(a4);
  client.setNoDelay(true);
  //Serial.printf("[Connecting to %s ... ", host);
  if (client.connect(host, 80))
  {
    //Serial.println("connected");

    //Serial.println("[Sending set request]");
    client.print(String("GET /cdtp/set_watt2?a1=" + b1 + "&a2=" + b2 + "&a3=" + b3 + "&a4=" + b4) + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n"
                );
   client.stop();
   //Serial.println("[Disconnected]");
  }else{
    //Serial.println("Fail Connection");
  }
  c=0;
  while(c<4){
    if(y[c]>50){
      Serial.write("1");
    }else{
      Serial.write("0");
    }
    c=c+1;
  }


client.setNoDelay(true);
  //Serial.printf("[Connecting to %s ... ", host);
  if (client.connect(host, 80))
  {
    //Serial.println("connected");

    //Serial.println("[Sending get request]");
    client.print(String("GET /cdtp/get_time") + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n"
                );
    c=0;
    //Serial.println("[Response:]");
    while (c<1)
    {
      if (client.available())
      {
        String line = client.readStringUntil('*');
        //Serial.println(line);
        x=line.toInt();
       }
       if(x){
        //Serial.println(x);
        t=x;
        c=c+1;
        x=0;
        }
     }
    client.stop();
    //Serial.println("[Disconnected]");
  }
  else
  {
    //Serial.println("connection failed!");
    client.stop();
  }


  if(t<18 and t>7){
    Serial.write("1");
  }else{
    Serial.write("0");
  }
  //Serial.println(t);
  t=(t+1)%25;
  if(t==0){
    t=1;
  }
  
  Serial.println(t);
  String t1=String(t);
  client.setNoDelay(true);
  //Serial.printf("[Connecting to %s ... ", host);
  if (client.connect(host, 80))
  {
    //Serial.println("connected");

    //Serial.println("[Sending set request]");
    client.print(String("GET /cdtp/set_time?t=" + t1) + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n"
                );
   client.stop();
   //Serial.println("[Disconnected]");
  }else{
    //Serial.println("Fail Connection");
  }
  
  
  delay(5000);
}
