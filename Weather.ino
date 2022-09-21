//DHT22 Setup
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
//SD Card Setup
#include <SPI.h>
#include <SD.h>
File sdcard_file;
int CS_pin = 10;
//DS18B20 Temperature sensor
#include <OneWire.h>
#include<DallasTemperature.h>
#define ONE_WIRE_BUS 3
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int scale = 3; // 3 (±3g) for ADXL337, 200 (±200g) for ADXL377
boolean micro_is_5V = true; // Set to true if using a 5V microcontroller such as the Arduino Uno, false if using a 3.3V microcontroller, this affects the interpretation of the sensor data
void setup() {
Serial.begin(9600);
sensors.begin();
 dht.begin();
 pinMode(CS_pin, OUTPUT);//declaring CS pin as output pin
 if (SD.begin()){
   Serial.print("SD Card found!");
 } else
 {
   Serial.print("Error finding SD Card");
   return;
 }
 sdcard_file = SD.open("data.csv", FILE_WRITE);
 if (sdcard_file) { //If the file is found
 }
 else {
   Serial.print("error initializing SD card");
 }
sdcard_file.print("DS18B20");
sdcard_file.print(",");
sdcard_file.print("DHT22 Temp");
sdcard_file.print(",");
sdcard_file.print("Hum");
sdcard_file.print(",");
sdcard_file.print("H.InX");
sdcard_file.print(",");
sdcard_file.print("rawX");
sdcard_file.print(",");
sdcard_file.print("rawY");
sdcard_file.print(",");
sdcard_file.print("rawZ");
sdcard_file.print(",");
sdcard_file.print("scaledX");
sdcard_file.print(",");
sdcard_file.print("scaledY");
sdcard_file.print(",");
sdcard_file.print("scaledZ");
sdcard_file.print(",");
sdcard_file.println(" ");
}
void loop() {
delay(222);

//DS18B20 Temp
sensors.requestTemperatures();
int etemp=sensors.getTempCByIndex(0);
//DS18B20 Humidity Sensor
 float h = dht.readHumidity();
 float t = dht.readTemperature();
 float f = dht.readTemperature(true);
 // Check if any reads failed and exit early for DHT
 if (isnan(h) || isnan(t) || isnan(f)) {
   return;
 }
 // Compute heat index in Fahrenheit (the default)
 float hif = dht.computeHeatIndex(f, h);
 // Compute heat index in Celsius (isFahreheit = false)
 float hic = dht.computeHeatIndex(t, h, false);
 sdcard_file.print(etemp);
 sdcard_file.print(",");
 sdcard_file.print(t);
  sdcard_file.print(",");
 sdcard_file.print(h);
  sdcard_file.print(",");
 sdcard_file.print(hic);
  sdcard_file.print(",");
 
 sdcard_file.print(" ");
 sdcard_file.println(" ");
sdcard_file.close();
delay(223);
}
float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
} 
