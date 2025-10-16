#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

// ----- LCD and DHT setup -----
#define DHTPIN 4          // DHT11 connected to GPIO 4
#define DHTTYPE DHT11     // Sensor type
#define MAX_READINGS 10   // Number of readings to store

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

float temperatureData[MAX_READINGS];
int indexCount = 0;
bool bufferFull = false;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);   // SDA, SCL pins for ESP32

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("DHT11 Sensor");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);

  dht.begin();
  Serial.println("System Ready for Data Analysis");
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Celsius

  if (isnan(humidity) || isnan(temperature)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!");
    Serial.println("Failed to read from DHT sensor!");
    delay(2000);
    return;
  }

  // ----- Store the temperature reading -----
  temperatureData[indexCount] = temperature;
  indexCount++;
  if (indexCount >= MAX_READINGS) {
    indexCount = 0;
    bufferFull = true;
  }

  // ----- Compute average -----
  float sum = 0;
  int validCount = bufferFull ? MAX_READINGS : indexCount;
  for (int i = 0; i < validCount; i++) {
    sum += temperatureData[i];
  }
  float avgTemp = sum / validCount;

  // ----- Analyze changes -----
  String status;
  if (temperature > 40) {
    status = "DANGER!"; // Very high temperature
  } else if (abs(temperature - avgTemp) > 5) {
    status = "WARNING!"; // Sudden spike
  } else {
    status = "NORMAL";
  }

  // ----- Display on LCD -----
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature, 1);
  lcd.print("C H:");
  lcd.print(humidity, 0);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print(status);
  lcd.print(" Avg:");
  lcd.print(avgTemp, 1);

  // ----- Print to Serial -----
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print("C  Humidity: ");
  Serial.print(humidity);
  Serial.print("%  AvgTemp: ");
  Serial.print(avgTemp);
  Serial.print("  Status: ");
  Serial.println(status);

  delay(3000); // 3-second delay between readings
}