// Test for minimum program size.

#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

#include "DHT.h"
#define DHTPIN 2     // PIN D2

#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C
// SDA - A4
// SCL - A5
// dht DATA PIN - D2

// Define proper RST_PIN if required.
#define RST_PIN -1

SSD1306AsciiWire oled;

//------------------------------------------------------------------------------
void setup() {
  dht.begin();
  
  Wire.begin();
  Wire.setClock(400000L);

#if RST_PIN >= 0
  oled.begin(&Adafruit128x32, I2C_ADDRESS, RST_PIN);
#else // RST_PIN >= 0
  oled.begin(&Adafruit128x32, I2C_ADDRESS);
#endif // RST_PIN >= 0
  oled.setFont(font5x7);
  oled.setCursor(10, 1);
  oled.println("Temperature - 'C");
  oled.setCursor(10, 3);
  oled.println("Humidity - %");
  delay(4000);
  oled.set2X();
  oled.clear();
}

//------------------------------------------------------------------------------

void loop() {

  float h = dht.readHumidity();

  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    oled.setCursor(2, 1);   
    oled.clearToEOL();
    oled.println("Read fail!");
    delay(2000);
    return;
  }
  oled.setCursor(2, 1);   
  oled.println(String(int(t)) + "'C");

  oled.setCursor(80, 1);  
  oled.println(String(int(h)) + "%");
  delay(2000);
}
