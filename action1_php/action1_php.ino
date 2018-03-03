#include <SoftwareSerial.h>
SoftwareSerial esp(10,11);

String string="POST 192.168.43.34:8080/action1.php?soil_moisture=";
  String string1="&humidity=";
  String string2="&light=";
  String string3="&temp=";
  String string4=" HTTP/1.1\r\nHost:192.168.43.34\r\n\r\n";
  uint8_t moi;
  uint8_t hum;
  uint8_t light;
  uint8_t temp;

void setup(){
  Serial.begin(9600);
  esp.begin(115200);

  while(!Serial);
  esp.println("AT+RST");
  delay(1000);
  OK();
  esp.println("AT+CIPMUX=1");
  delay(1000);
  OK();
  esp.println("AT+CWJAP=\"Jimmy KZm\",\"\"");
  delay(1000);
  OK();
  
  
}
void loop(){
  esp.println("AT+CIPSTART=0,\"TCP\",\"192.168.43.34\",8080");
  delay(1000);
  OK();
  esp.print("AT+CIPSEND=0,124\r\n");
  if(!esp.available());
  delay(10);
//    esp.print("POST 192.168.43.34:8080/action1.php?soil_moisture=20&humidity=50&light=99&temp=50 HTTP/1.1\r\nHost:192.168.43.34\r\n\r\n");
    
  

  string+=moi;
  string+=string1;
  string+=hum;
  string+=string2;
  string+=light;
  string+=string3;
  string+=temp;
  string+=string4;
  esp.print(string);
  
  
//        char a = esp.read();
//        Serial.write(a);
  
  esp.println("AT+CIPCLOSE=0");
  delay(2000);
  /*
  if(Serial.available()){
    esp.write(Serial.read());
  }
  if(esp.available()){
    Serial.write(esp.read());
  }
  */
}

void OK(){
  if(esp.find("OK")){
    Serial.println("ok");
  }
  else{
    Serial.println("...");
  }
}

