/*
 * Project: Smart Aquatic Monitoring System
 * Description: This ESP32 program reads soil moisture and ultrasonic distance sensor data 
 *              and publishes the values to an MQTT broker.
 * Author: Yodha Ardiansyah
 * GitHub: https://github.com/Yodhaardiansyah
 */

#include <WiFi.h>
#include <PubSubClient.h>

// WiFi Configuration (Replace with your credentials)
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// MQTT Configuration (Replace with your server details)
const char* mqtt_server = "YOUR_MQTT_SERVER";
const int mqtt_port = 1883;
const char* mqtt_user = "YOUR_MQTT_USERNAME";
const char* mqtt_password = "YOUR_MQTT_PASSWORD";

// MQTT Topics
const char* topic_soil_moisture = "smartaquatic/moisture";
const char* topic_distance = "smartaquatic/distance";

// Pin Configuration
#define MOISTURE_PIN 33
#define TRIG_PIN 12
#define ECHO_PIN 13

// MQTT Client Object
WiFiClient espClient;
PubSubClient client(espClient);

// Function to Connect WiFi
void setup_wifi() {
  delay(10);
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");
}

// Function to Reconnect MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32Publisher", mqtt_user, mqtt_password)) {
      Serial.println("Connected to MQTT");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

// Function to Read Distance using Ultrasonic Sensor
long readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2; // Convert to cm
}

// Setup Function
void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);

  pinMode(MOISTURE_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

// Main Loop
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Read soil moisture
  int moistureValue = analogRead(MOISTURE_PIN);
  client.publish(topic_soil_moisture, String(moistureValue).c_str());

  // Read distance using HC-SR04
  long distance = readDistance();
  client.publish(topic_distance, String(distance).c_str());

  delay(1000); // Data transmission interval
}
