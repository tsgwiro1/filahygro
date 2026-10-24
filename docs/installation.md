# Installation

Vom geklonten Repository bis zur Firmware auf dem Gerät. Die Einrichtung im
Portal (WLAN, MQTT, Kalibrierung) folgt, sobald die Firmware sie anbietet.

---

## Inhalt

1. [Voraussetzungen](#1-voraussetzungen)
2. [Bauen](#2-bauen)
3. [Adapter anschliessen](#3-adapter-anschliessen)
4. [Flashen](#4-flashen)
5. [Kontrolle](#5-kontrolle)

---

## 1. Voraussetzungen

- [PlatformIO](https://platformio.org/), als Kommandozeile oder in VS Code
- USB-Seriell-Adapter mit **3.3-V-Pegel** (FTDI, CP2102, CH340 o.ä.)
- Geladene Zelle im Gerät. Die Stiftleiste J1 führt keine Versorgung, das
  Gerät läuft beim Flashen aus seinem Akku.

## 2. Bauen

```bash
pio run
```

Kontrolle: Die Ausgabe endet mit `[SUCCESS]`, die Firmware liegt in
`.pio/build/filahygro/firmware.bin`.

## 3. Adapter anschliessen

Stiftleiste J1 auf der Platine (Rev 2):

| J1 Pin | Signal am ESP | an den Adapter |
|---|---|---|
| 2 | RX | TX |
| 3 | TX | RX |
| 6 | GND | GND |

Pin 1, 4 und 5 sind nicht belegt. Den 3.3-V- oder 5-V-Ausgang des Adapters
**nicht** anschliessen.

## 4. Flashen

Die Platine hat keine automatische Umschaltung in den Flash-Modus. Von Hand:

1. **BOOT** (KEY2) gedrückt halten.
2. **RESET** (KEY1) kurz drücken.
3. **BOOT** loslassen.
4. Flashen:

   ```bash
   pio run -t upload
   ```

5. Nach dem Upload **RESET** drücken, damit die neue Firmware startet.

Findet PlatformIO den Adapter nicht von selbst, den Port mit
`--upload-port /dev/cu.usbserial-…` angeben.

## 5. Kontrolle

```bash
pio device monitor
```

**RESET** drücken. Nach einer Zeile mit Zeichensalat (Bootmeldung des ESP8266
mit 74880 Baud) erscheint:

```
FilaHygro 0.1.0
```

Danach schläft das Gerät und meldet sich nach fünf Minuten wieder.
