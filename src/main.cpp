#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "wifi.h"
#include "mqtt.h"
#include "config.h"

SoftwareSerial paradoxSerial(RX_PIN, TX_PIN);
ESP8266WebServer server(httpPort);
bool alarmArmed = false;

void handleRoot() {
	server.send(200, "text/plain", String(alarmArmed));
}

void handleNotFound() {
	String message = "File Not Found\n\n";
	server.send(404, "text/plain", message);
}

void setup() {
  setupWifi(ssid, password);
  setupMqtt(mqtt_server, mqtt_port, mqtt_user, mqtt_password);  

  Serial.begin(9600);
  Serial.flush();

  paradoxSerial.begin(9600);
  paradoxSerial.flush();  

  server.on("/", handleRoot);
	server.onNotFound(handleNotFound);
	server.begin();
	Serial.println("HTTP server started");
}

void loop() {
	keepAliveWifi(ssid, password);
  keepAliveMqtt(mqtt_user, mqtt_password);
	server.handleClient();

  if (paradoxSerial.available() > 0) {
    int header = paradoxSerial.read();
    if (header == 0x08) {
      int command = paradoxSerial.read();

      paradoxSerial.read();
      paradoxSerial.read();

      switch (command) {
          case 0xA1:
            Serial.println("Activated");
            alarmArmed = true;
            sendArmStatus(true);
            break;
          case 0x91:
            Serial.println("Deactivated");
            alarmArmed = false;
            sendArmStatus(false);
            break;
      }
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

	delay(100);
}
