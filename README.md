# **Smart Aquatic Control & Monitoring System** 🌊🐠  

This project consists of two ESP32-based programs that utilize **WiFi and MQTT** for **controlling relays and servos** and **monitoring soil moisture and water levels**.

---

## **🚀 Features**
✅ **Remote Relay Control:** Turn devices ON/OFF via MQTT  
✅ **Servo Motor Control:** Adjust servo angles through MQTT messages  
✅ **Soil Moisture Monitoring:** Read and publish soil moisture levels  
✅ **Ultrasonic Water Level Measurement:** Measure and transmit water level data  
✅ **WiFi & MQTT Connectivity:** Seamless integration with an MQTT broker  

---

## **📁 Project Structure**
```
📂 smart-aquatic
│── 📄 README.md
│── 📄 smart_aquatic_control.ino      # Relay & Servo Control Program
│── 📄 smart_aquatic_monitoring.ino   # Soil Moisture & Distance Monitoring Program
```

---

## **🛠️ Requirements**
- **ESP32 Development Board**
- **Relay Module** (2 channels)
- **Servo Motor**
- **Soil Moisture Sensor**
- **Ultrasonic Sensor (HC-SR04)**
- **WiFi Router**
- **MQTT Broker (e.g., Mosquitto, Cloud MQTT)**

---

## **⚙️ Installation & Setup**
### **1️⃣ Flashing the Code**
1. Install **Arduino IDE** and add the **ESP32 Board Manager**  
2. Install required libraries:  
   - `PubSubClient` (for MQTT)  
   - `ESP32Servo` (for servo motor control)  
3. Open `smart_aquatic_control.ino` or `smart_aquatic_monitoring.ino`  
4. Replace **WiFi and MQTT credentials** (`YOUR_WIFI_SSID`, `YOUR_MQTT_SERVER`, etc.)  
5. Upload the code to **ESP32**  

### **2️⃣ MQTT Setup**
- Install **Mosquitto MQTT Broker** (or use an online MQTT broker)  
- Use an MQTT client (e.g., **MQTT Explorer, Node-RED**) to send/receive messages  

---

## **📡 MQTT Topics**
| Topic                 | Description                 | Expected Payload |
|-----------------------|---------------------------|------------------|
| `smartaquatic/relay1`  | Control **Relay 1**         | `"ON"` / `"OFF"` |
| `smartaquatic/relay2`  | Control **Relay 2**         | `"ON"` / `"OFF"` |
| `smartaquatic/servo`   | Set **Servo Angle**         | `"0-180"`        |
| `smartaquatic/moisture` | **Soil Moisture Level** (Published) | Numeric Value   |
| `smartaquatic/distance` | **Water Level Distance** (Published) | Numeric Value (cm) |

---

## **💡 Usage**
### **🔘 Controlling Relays & Servo**
1. Publish `"ON"` or `"OFF"` to `smartaquatic/relay1` or `smartaquatic/relay2`  
2. Publish an **angle (0-180)** to `smartaquatic/servo` to control the servo  

### **📊 Monitoring Moisture & Water Level**
- The ESP32 **automatically sends data** to `smartaquatic/moisture` and `smartaquatic/distance` every **1 second**  

---

## **👨‍💻 Author & Credits**
📌 **Developed by:** Yodha Ardiansyah  
📌 **GitHub:** [https://github.com/Yodhaardiansyah](https://github.com/Yodhaardiansyah)  
📌 **ESP32 Libraries:** WiFi, PubSubClient, ESP32Servo  

---

## **📜 License**
This project is **open-source** and licensed under the **MIT License**. Feel free to modify and contribute! 🚀✨  

---
