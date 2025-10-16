# Temperature & Humidity Detector IoT

This project is an IoT-based temperature and humidity detector using a DHT sensor. It measures environmental temperature and humidity, shows real-time readings on a display, and calculates average/normalized values over time.

## Features

- Measures temperature & humidity using DHT sensor (DHT11/DHT22)
- Shows data on an LCD/OLED display
- Calculates and displays average/normalized readings
- Easy setup for Arduino, ESP8266, or ESP32
- Code structure allows further IoT/cloud integration

## Hardware Requirements

- Microcontroller (Arduino UNO, ESP8266, ESP32, etc.)
- DHT sensor (DHT11 or DHT22)
- Display (16x2 LCD, SSD1306 OLED, etc.)
- Jumper wires, Breadboard (optional)

## Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/Dhruvinkatakiya/Temparature_detector_IOT.git
```

### 2. Wiring

- Connect DHT sensor (signal, VCC, GND) to microcontroller
- Wire display according to your module’s documentation

### 3. Install Libraries

- DHT sensor library (`DHT.h`)
- Display library (`LiquidCrystal.h`, `Adafruit_SSD1306.h`, etc.)

### 4. Upload Code

- Open main code file in Arduino IDE
- Set board type and port
- Upload the code

### 5. Usage

- On startup, display shows live temperature and humidity.
- The average or normalized values are calculated and displayed (e.g., after every minute or after N readings).

#### Example Output

```
Temp: 24.5°C
Humidity: 56%

Avg Temp: 24.2°C
Avg Humidity: 55%
```

## Customization

- Change sensor type (DHT11/DHT22) in the code.
- Modify display type or pin connections as needed.
- Adjust averaging interval or normalization logic.
- Extend for Wi-Fi/cloud logging or data alerts.

## License

MIT License

## Author

Dhruvinkatakiya
