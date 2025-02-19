// Tested with ESP32 Boards Package Version 2.0.17 

#include "src/ESPSerialFlasher/src/ESPSerialFlasher.h" 
#include <SPI.h>
#include "SD.h"
const int SD_CS_pin = 5;
const int startProgramming_pin = 21;
const int En3VPin = 4;
unsigned long greenLEDstartTime;

//the 4 files we're looking for must contain these keywords in the title
const char bootKey[] = "boot_app";
const char bootloaderKey[] = "bootloader";
const char partitionsKey[] = "partitions";
const char firmwareKey[] = ".ino.bin";//when you flash over USB, it looks like this
const char firmwareSecondKey[] = "esp32.bin";//when you export compiled binary, this is the file it generates
const char SPIFFSKey[] = "spiffs.bin";///Users/kevindarrah/Library/Arduino15/packages/esp32/tools/esptool_py/3.0.0/esptool --chip esp32 --port /dev/cu.usbserial-DA00XJ7V  --baud 230400 read_flash 0x3D0000 0x30000 spiffs.bin
boolean flashSPIFFS = false;//that way we only flash if present on card

const char hiddenFileKey[] = "/._";//on mac, we may find duplicates that start with this, so we filter out

//these title names will be stored here
char bootName[100] = {NULL};
char bootloaderName[100] = {NULL};
char partitionsName[100] = {NULL};
char firmwareName[100] = {NULL};
char spiffsName[100] = {NULL};


SPIClass spiSD(VSPI);

void initSDcard();
bool startFlashing();
void getFileNames();

void setup() {
  Serial.begin(115200);
  delay(2000);
  redLED(true);
  initSDcard();
  pinMode(startProgramming_pin, INPUT_PULLUP);
  pinMode(En3VPin, OUTPUT);
  digitalWrite(En3VPin, HIGH);
  redLED(false);
}

void loop() {
  if (millis() - greenLEDstartTime > 500) {
    greenLEDstartTime = millis();
    greenLEDflash();
  }

  if (!digitalRead(startProgramming_pin)) {
    if (!startFlashing()) {
      digitalWrite(En3VPin, LOW);
      while (1) {
        greenLED(false);
        yelLED(false);
        redLED(true);
      }
    }
    digitalWrite(En3VPin, LOW);
    delay(1000);
    digitalWrite(En3VPin, HIGH);
  }
}
