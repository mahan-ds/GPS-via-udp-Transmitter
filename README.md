# ESP32-GPS-UDP-Transmitter

A simple project to read GPS data using an ESP32 and transmit the coordinates to a phone (or any UDP server) via WiFi UDP packets.

## 📡 Project Overview

This project sets up the ESP32 as a Wi-Fi Access Point and continuously reads GPS coordinates from a GPS module (like NEO-M8N) using the TinyGPS++ library. The coordinates are sent over UDP to a predefined IP address and port (e.g. your phone or computer).

## 🔧 Hardware Used

- ESP32 Dev Board  
- GPS Module (e.g., NEO-6M, NEO-M8N)  
- Jumper wires  
- (Optional) Smartphone to receive data over UDP

## 🔌 Wiring

| ESP32 Pin | GPS Module |
|-----------|------------|
| GPIO16    | TX         |
| GPIO17    | RX         |
| GND       | GND        |
| 3.3V/5V   | VCC        |

> ⚠️ Make sure your GPS module works with 3.3V or use a level shifter if needed.

## 📲 How It Works

1. ESP32 starts in Access Point mode with SSID `ESP32-AP` and password `12345678`.
2. It reads NMEA data from the GPS module over Serial2.
3. When a new location is available, it sends a UDP message with latitude and longitude (comma-separated) to the given IP and port.

## 📦 Example Output

```text
Sent: 35.68919712,51.38901923
