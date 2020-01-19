#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>

SoftwareSerial paradoxSerial(D8,D7);

void setup() {
  Serial.begin(9600);
  Serial.flush();

  paradoxSerial.begin(9600);
  paradoxSerial.flush();  
  
  Serial.println("setup");
}

void loop()
{
  if (paradoxSerial.available() >= 4) {
    int header = paradoxSerial.read();
    int command = paradoxSerial.read();

    paradoxSerial.read();
    paradoxSerial.read();

    if (header != 0x08) {
      return;
    }
    switch (command) {
        case 0xA1:
          Serial.println("Activated");
          break;
        case 0x91:
          Serial.println("Deactivated");
          break;
    }
  }
/*
  if(paradoxSerial.available() > 4) {
    for (int i=0; i<4; i++) {
      int data = paradoxSerial.read();
      Serial.print(data, HEX);
      Serial.print(" ");
    }
    Serial.println("");
  }*/
}
