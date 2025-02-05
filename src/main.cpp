#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 6  // SDA pin
#define RST_PIN 4  // RST pin

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  Serial.begin(9600);  // Initialize serial communications with the PC
  SPI.begin();  // Init SPI bus
  mfrc522.PCD_Init();  // Init MFRC522
  Serial.println("Scan a card...");
}

void loop() {
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Show UID on serial monitor without spaces between bytes
  Serial.print("UID tag: ");
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) {
      Serial.print("0");
      content.concat("0");
    }
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  delay(1000);  // Add a delay to avoid reading the same card multiple times
}