#include <brzo_i2c.h>
#include "SSD1306Brzo.h"

//#include <Wire.h>
//#include "SSD1306.h"

//#include <ESP8266WiFi.h>
#include <SPI.h>
#include "MFRC522.h"

/* wiring the MFRC522 to ESP8266 (ESP-12)
  RST     = GPIO5
  SDA(SS) = GPIO4
  MOSI    = GPIO13
  MISO    = GPIO12
  SCK     = GPIO14
  GND     = GND
  3.3V    = 3.3V
*/

#define RST_PIN	D0  // RST-PIN für RC522 - RFID - SPI - Modul GPIO5 
#define SS_PIN	D2  // SDA-PIN für RC522 - RFID - SPI - Modul GPIO4 

#define SDA_PIN D3
#define SCL_PIN D1 

// brzo_i2c_setup(uint8_t sda, uint8_t scl, uint32_t clock_stretch_time_out_usec).
//SSD1306  display(0x3c, D3, D5);

SSD1306Brzo  display(0x3c, SDA_PIN, SCL_PIN);
MFRC522 mfrc522(SS_PIN, RST_PIN);	// Create MFRC522 instance

void setup() {

  Serial.begin(115200);    // Initialize serial communications
  delay(250);
  Serial.println(F("Booting...."));

  SPI.begin();	         // Init SPI bus
  mfrc522.PCD_Init();    // Init MFRC522

  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  display.clear();
  drawTextFlowDemo();
  display.display();

  Serial.println(F("Ready!"));
  Serial.println(F("======================================================"));
  Serial.println(F("Scan for Card and print UID:"));
}

void loop() {

  rfid();
  
}

void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

void drawTextFlowDemo() {
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawStringMaxWidth(0, 0, 128,
                             "Lorem ipsum\n dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore." );
}

