#include <FS.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266SSDP.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <DNSServer.h>
#include <PubSubClient.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>

#include <SoftwareSerial.h>

SoftwareSerial paradoxSerial(D8,D7);

void setup() {
  /*
  Serial1.begin(9600);
  Serial1.flush();
  Serial1.setDebugOutput(true);
  */

  Serial.begin(9600);
  Serial.flush();

  paradoxSerial.begin(9600);
  paradoxSerial.flush();  
  
  Serial.println("setup");
}
 
void loop()
{
  if(paradoxSerial.available() >= 4) {
    for (int i=0; i<4; i++) {
      int data = paradoxSerial.read();
      Serial.print(data, HEX);
      Serial.print(" ");
    }
    Serial.println("");
  }
}
