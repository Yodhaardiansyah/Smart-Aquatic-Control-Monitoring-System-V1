/*
 * Project: Smart Aquatic Control System
 * Description: This ESP32 program connects to an MQTT server and listens for commands 
 *              to control two relays and a servo motor.
 * Author: Yodha Ardiansyah
 * GitHub: https://github.com/Yodhaardiansyah
 */

#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>

// WiFi Configuration (Replace with your credentials)
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// MQTT Configuration (Replace with your server details)
const char* mqtt_server = "YOUR_MQTT_SERVER";
const int mqtt_port = 1883;
const char* mqtt_user = "YOUR_MQTT_USERNAME";
const char* mqtt_password = "YOUR_MQTT_PASSWORD";

// MQTT Topics
const char* topic_relay1 = "smartaquatic/relay1";
const char* topic_relay2 = "smartaquatic/relay2";
const char* topic_servo = "smartaquatic/servo";

// Pin Configuration
#define RELAY1_PIN 14
#define RELAY2_PIN 27
#define SERVO_PIN 25

// MQTT and Servo Objects
WiFiClient espClient;
PubSubClient client(espClient);
Servo myServo;

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

// MQTT Callback Function
void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.print("Received message: ");
  Serial.println(message);

  if (String(topic) == topic_relay1) {
    digitalWrite(RELAY1_PIN, message == "ON" ? HIGH : LOW);
  } else if (String(topic) == topic_relay2) {
    digitalWrite(RELAY2_PIN, message == "ON" ? HIGH : LOW);
  } else if (String(topic) == topic_servo) {
    int angle = message.toInt();
    myServo.write(angle);
  }
}

// Function to Reconnect MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32Subscriber", mqtt_user, mqtt_password)) {
      Serial.println("Connected to MQTT");
      client.subscribe(topic_relay1);
      client.subscribe(topic_relay2);
      client.subscribe(topic_servo);
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

// Setup Function
void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  myServo.attach(SERVO_PIN);
}

// Main Loop
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
