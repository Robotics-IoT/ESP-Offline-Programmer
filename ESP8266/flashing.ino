
/*
  boot_app0.bin
  bootloader_qio_80m.bin
  trigBoardV8_BaseFirmware.ino.bin
  trigBoardV8_BaseFirmware.ino.partitions.bin
*/
bool startFlashing() {
  delay(1000);
  digitalWrite(En3VPin, HIGH);  // Ensure target device is powered

  // Initialize the flasher to set up Serial communication to ESP8266
  ESPFlasherInit(true, &Serial);

  // Connect to the ESP8266 module
  if (ESPFlasherConnect()) {
    Serial.println("Flashing firmware...");

    // Flash the firmware file at the correct address (0x00000 for ESP8266)
    if (ESPFlashBin(firmwareName, 0x0)) {
      Serial.println("Firmware flashed successfully!");
      return true;
    } else {
      Serial.println("Firmware flashing failed!");
      return false;
    }
  } else {
    Serial.println("Failed to connect to ESP8266!");
    return false;
  }
}

// bool startFlashing() {
//   delay(1000);
//   digitalWrite(En3VPin, HIGH);
//   ESPFlasherInit(true, &Serial);//sets up Serial communication to wifi module, with debug messages, to Print Class of your choice
//   if (ESPFlasherConnect()) {       //connects to wifi module
//         Serial.println("fleser start boot app");
//     if (ESPFlashBin(bootName, 0xe000)) { //bootapp
//       ESPFlasherInit(true, &Serial);
//       if (ESPFlasherConnect()) {
//         Serial.println("fleser start bootloader app");
//         if (ESPFlashBin(bootloaderName, 0x1000)) { //bootloader
//           ESPFlasherInit(true, &Serial);
//           if (ESPFlasherConnect()) {
//             Serial.println("fleser start firmware app");
//             if (ESPFlashBin(firmwareName, 0x10000)) { //firmware
//               ESPFlasherInit(true, &Serial);
//               if (ESPFlasherConnect()) {
//                 Serial.println("fleser start partition app");
//                 if (ESPFlashBin(partitionsName, 0x8000)) { //partitions
//                   if (flashSPIFFS) {//only if SPIFFS bin is present!
//                     ESPFlasherInit(true, &Serial);
//                     if (ESPFlasherConnect()) {
//                       if (ESPFlashBin(spiffsName, 0x3D0000)) { //SPIFFS - minimal SPIFFS settings, you need to change this for your settings!
//                         Serial.println("!!!EVERYTHING IS FLASHED AND COMPLETE!!!");
//                         return true;
//                       } else
//                         return false;
//                     } else
//                       return false;
//                   } else {
//                     Serial.println("!!!EVERYTHING IS FLASHED AND COMPLETE!!!");
//                     return true;
//                   }
//                 }
//               }
//             }
//           }
//         }
//       }
//     }
//   }
//   return false;
// }
