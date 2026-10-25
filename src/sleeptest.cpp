/*
 * FilaHygro – Messfirmware für den Ruhestrom.
 *
 * Setzt die Pins in den Zustand, den auch die Betriebsfirmware im Schlaf
 * hinterlässt, und geht ohne Funk in den Deep Sleep, bis RESET gedrückt wird.
 * Kein Wecken nach Zeit: Der Strom der Wachphase würde am µA-Bereich des
 * Messgeräts so viel Spannung verlieren, dass der ESP8266 neu startet.
 *
 * Ablauf der Messung siehe docs/ruhestrom.md.
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>

// Schaltet über Q1 den Spannungsteiler der Akkumessung ein (aktiv HIGH)
constexpr uint8_t PIN_M_BAT = 15;

// I2C zur Sensorplatine; Pull-ups sitzen auf der Platine
constexpr uint8_t PIN_SDA = 4;
constexpr uint8_t PIN_SCL = 5;

// Auf der Platine nicht beschaltet
constexpr uint8_t PINS_FREE[] = {12, 13, 14};

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.printf("FilaHygro %s – sleeptest\n", FW_VERSION);

  // Funk bleibt aus; nichts ins Flash schreiben
  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);

  // Spannungsteiler aus, I2C hochohmig, freie Pins nicht schwebend
  pinMode(PIN_M_BAT, OUTPUT);
  digitalWrite(PIN_M_BAT, LOW);
  pinMode(PIN_SDA, INPUT);
  pinMode(PIN_SCL, INPUT);
  for (uint8_t pin : PINS_FREE) {
    pinMode(pin, INPUT_PULLUP);
  }

  Serial.println("Deep Sleep bis RESET");
  Serial.flush();

  ESP.deepSleep(0, WAKE_RF_DISABLED);
}

void loop() {
}
