#include <WiFi.h>
#include <WiFiUdp.h>
#include <TinyGPS++.h>

// WiFi settings
const char *ssid = "ESP32-AP";
const char *password = "12345678";
const char *destinationIp = "192.168.4.2";  // Phone's IP
const int destinationPort = 1234;

WiFiUDP udp;
TinyGPSPlus gps;

// GPS pin configuration
#define GPS_RX_PIN 16
#define GPS_TX_PIN 17

unsigned long previousMillis = 0;
const long interval = 100; // 1 Hz

void setup() {
  Serial.begin(115200);
  
  // Start Access Point
  WiFi.softAP(ssid, password);
  Serial.println("Access Point Started");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.softAPIP());
  
  // Initialize UDP
  udp.begin(1234);
  
  // Start serial communication with GPS module
  Serial2.begin(57600, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Read data from GPS module
  while (Serial2.available() > 0) {
    gps.encode(Serial2.read());
  }

  // Check if valid data has been received
  if (gps.location.isUpdated() && (currentMillis - previousMillis >= interval)) {
    previousMillis = currentMillis;
    
    double latitude = gps.location.lat();
    double longitude = gps.location.lng();
    
    // Convert coordinates to string
    char latBuffer[20];
    char lonBuffer[20];
    dtostrf(latitude, 1, 8, latBuffer);
    dtostrf(longitude, 1, 8, lonBuffer);
    
    // Build the message
    String message = String(latBuffer) + "," + String(lonBuffer);
    
    // Send message via UDP
    udp.beginPacket(destinationIp, destinationPort);
    udp.print(message);
    udp.endPacket();
    
    // Print data to Serial Monitor
    Serial.print("Sent: ");
    Serial.println(message);
  }
}
