#include <ESP8266WiFi.h>

const char* ssid = "test";//"TTNET_ZyXEL_TNC9";               //"asd";
const char* password =   "mOd8542999"  ;//"03c184659A437"; // "123asd123";
const char* host = "192.168.1.4";
int x=0;
int y[6];
int c=0;

void setup()

{
  Serial.begin(9600);
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
  }
  if(y[0]>150){
    

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
    x=0;
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
        y[c]=x;
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
    }else{
  y[0]=0;
  y[1]=0;
  y[2]=0;
  y[3]=0;
  y[4]=0;
  y[5]=0;}
  c=0;
  while(c<6){
    if(y[c]==1){
      Serial.write("1");
    }else{
      Serial.write("0");
    }
    c=c+1;
  }
  delay(1000);
 
}
