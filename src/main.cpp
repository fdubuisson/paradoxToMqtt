#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include "wifi.h"
#include "mqtt.h"
#include "config.h"

SoftwareSerial paradoxSerial(RX_PIN, TX_PIN);

void setup() {
  setupWifi(ssid, password);
  setupMqtt(mqtt_server, mqtt_port, mqtt_user, mqtt_password);  

  Serial.begin(9600);
  Serial.flush();

  paradoxSerial.begin(9600);
  paradoxSerial.flush();  
}

void loop() {
	keepAliveWifi(ssid, password);
  keepAliveMqtt(mqtt_user, mqtt_password);

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
          sendArmStatus(true);
          break;
        case 0x91:
          Serial.println("Deactivated");
          sendArmStatus(false);
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
