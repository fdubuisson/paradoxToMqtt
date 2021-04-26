#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "mqtt.h"

WiFiClient espClient;
PubSubClient client(espClient);

const char* connectionStatus = "paradox/connected";
const char* armStatusTopic = "paradox/armed";

void setupMqtt(const char* server, int port, const char* user, const char* password) {
    client.setServer(server, port);
    keepAliveMqtt(user, password);
}

void keepAliveMqtt(const char* user, const char* password) {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    if (client.connect("paradox", user, password)) {
      Serial.println("connected");
      client.publish(connectionStatus, "connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
  client.loop();
}

void sendArmStatus(bool activated) {
  char data = (activated ? '1' : '0');
  if (! client.publish(armStatusTopic, &data, 1)) {
    Serial.print("Failed sending status");
  }
}

void sendDebug(const char* message) {

}