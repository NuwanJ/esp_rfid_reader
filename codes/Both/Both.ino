#include <brzo_i2c.h>
#include "SSD1306Brzo.h"

//#include <Wire.h>
//#include "SSD1306.h"

//#include <ESP8266WiFi.h>
#include <SPI.h>
#include "MFRC522.h"

/*
  MOSI    = D7 GPIO13
  MISO    = D6 GPIO12
  SCK     = D5 GPIO14
*/

#define RST_PIN	D0  // GPI16
#define SS_PIN	D2  // GPIO4 

#define SDA_PIN D3 	// GPIO 00
#define SCL_PIN D1 	// GPIO 05

SSD1306Brzo  display(0x3c, SDA_PIN, SCL_PIN);
MFRC522 mfrc522(SS_PIN, RST_PIN);	// Create MFRC522 instance

void setup() {

  Serial.begin(115200);    // Initialize serial communications
  delay(250);

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

