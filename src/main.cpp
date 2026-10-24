/*
 * FilaHygro – Firmware für batteriebetriebene Feuchte- und Temperatursensoren
 * auf ESP-12F.
 *
 * Gerüst: meldet die Version auf der seriellen Schnittstelle und schläft.
 * Messen und Senden folgen.
 */

#include <Arduino.h>

// Schlafdauer zwischen zwei Wachphasen
constexpr uint64_t SLEEP_TIME_US = 300e6;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.printf("FilaHygro %s\n", FW_VERSION);

  ESP.deepSleep(SLEEP_TIME_US);
}

void loop() {
}
