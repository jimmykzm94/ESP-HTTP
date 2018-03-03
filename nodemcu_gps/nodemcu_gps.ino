#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
SoftwareSerial gps(12,14);

const char *ssid = "Jimmy KZm";
const char *pswd = "";
char server[] = "www.dweet.io";

String send1 = "POST /dweet/for/jsonstring123?latitude=";
String send2 = "&longitude=";
int i=0;
String latitudeStr;
String longitudeStr;
float latitude;
float longitude;
char message[10]="";
boolean chk=false;
boolean transmit=false;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pswd);
  Serial.println("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(20);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wifi is connected.");

}

void loop() {
  WiFiClient client;
  
  if(gps.available()){
      if(gps.find("$GPGGA")){
        if(gps.find(',')){
          if(gps.read()==','){
            chk=false;
            return;
          }
          else{
            chk=true;
          }
        }
      }
      else{
        return;
      }
      while(chk){
        
          //if(gps.find(',')){
            if(gps.find(',')){
              //Serial.print("Latitude: ");
              i=0;
              while(true){
                if(gps.available()){
                  message[i]=gps.read();
                  if(message[i]==','){
                    i=0;
                    break;
                  }
                  i++;
                }
              }
              latitudeStr=message;
              Serial.println(latitudeStr);
            }
          //}
            if(gps.find(',')){
              while(true){
                if(gps.available()){
                  message[i]=gps.read();
                  if(message[i]==','){
                    i=0;
                    chk=false;
                    transmit=true;
                    break;
                  }
                  i++;
                }
              }
              longitudeStr=message;
              Serial.println(longitudeStr);
            }
      }
    }

    latitude=latitudeStr.toFloat();
    latitude=conversion(latitude);
    longitude=longitudeStr.toFloat();
    longitude=conversion(longitude);
      String sending="";
      sending+=send1;
      sending+=latitude;
      sending+=send2;
      sending+=longitude;
  //Serial.println(sending);
  if (!client.connect(server, 80)) {
    Serial.println("Connection failed.");
    return;
  }
  client.println(sending);
  client.println("Host:www.dweet.io");
    client.println("Connection:close");
    client.println("");
}
float conversion(float i){
  float dp;
  int no;
  float temp;

  i/=100;
  no=(int)i;
  dp=i-(float)no;
  dp*=1.67;
  temp=(float)no+dp;

  return temp;
}
