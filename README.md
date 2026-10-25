# FilaHygro 🧵💧

![Version](https://img.shields.io/badge/version-v0.2.0-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Platform](https://img.shields.io/badge/platform-ESP8266-lightgrey.svg)

> Misst Feuchte und Temperatur in Filamentboxen und Räumen, läuft monatelang
> auf einer Li-Ion-Zelle und meldet sich per MQTT selbst in Home Assistant an.

> 🚧 **Im Neuaufbau.** Version 0.2.0 bringt die Messfirmware für den Ruhestrom
> und deren Ergebnis. Messen und Senden folgen in den nächsten Versionen.

---

## 📖 Inhalt

- [Das Problem](#-das-problem)
- [Die Lösung](#-die-lösung)
- [Was es leisten soll – und was nicht](#-was-es-leisten-soll--und-was-nicht)
- [Aufbau](#-aufbau)
- [Schnellstart](#-schnellstart)
- [Hardware](#-hardware)
- [Dokumentation](#-dokumentation)
- [Herkunft](#-herkunft)
- [Haftung](#-haftung)
- [Lizenz](#-lizenz)

---

## 🚨 Das Problem

Filament zieht Feuchtigkeit. Ob eine Box noch trocken ist, sieht man ihr nicht
an – man merkt es erst am Druckbild. Ein Sensor in der Box hilft nur, wenn er
ohne Kabel auskommt und nicht alle paar Wochen geladen werden will.

## ✅ Die Lösung

Eine kleine Platine mit ESP-12F, Sensor und 18650-Zelle. Sie wacht in festen
Abständen auf, misst, sendet nur bei einer Änderung und schläft sofort wieder.
Alles ausserhalb von Messen und Senden läuft einmalig oder nur auf Anstoss.

| | |
|---|---|
| 🌡️ **Sensor** | SHT31-D, SHT40, HDC1080 oder BME280, wird einmal erkannt |
| 📡 **Anbindung** | MQTT mit Home-Assistant-Discovery, ohne Eintrag von Hand |
| ⚙️ **Einrichtung** | WLAN, MQTT, Name und Kalibrierung im Einrichtungsportal am Gerät, keine Konfigurationsdateien |
| 🔋 **Akku** | Spannung und Ladestand, Tiefentladeschutz in der Hardware |

## ⚖️ Was es leisten soll – und was nicht

**Soll leisten:** Feuchte, Temperatur, Akkuspannung und Ladestand in Home
Assistant, mit einer Laufzeit von deutlich über einem Jahr pro Ladung.

**Leistet nicht:** Einstellungen aus Home Assistant heraus ändern. Jede
Verbindung, die das Gerät länger wach hält, geht auf Kosten des Akkus. Was
selten ändert, steht in der Firmware oder im Portal.

## 🧱 Aufbau

```
   FilaHygro-Platine
   ┌────────────────────────────────────┐
   │  18650 ── TP4056 ── NCP718 3.3 V   │
   │    │                    │          │
   │    └─ Teiler ── ADC   ESP-12F      │
   │                         │ I2C      │
   │                       Sensor       │
   └─────────────────────────│──────────┘
                             │ WLAN, MQTT
                             ▼
                  Broker ──▶ Home Assistant
```

## 🚀 Schnellstart

Voraussetzung: [PlatformIO](https://platformio.org/) und ein USB-Seriell-Adapter
mit 3.3-V-Pegel.

```bash
git clone https://github.com/tsgwiro1/filahygro.git
cd filahygro
pio run                  # bauen
pio run -t upload        # flashen, Gerät vorher in den Flash-Modus bringen
pio device monitor       # Ausgabe lesen
```

Wie das Gerät in den Flash-Modus kommt und wie der Adapter angeschlossen wird,
steht in **[docs/installation.md](docs/installation.md)**.

## 🔌 Hardware

Schema und Beschreibung der Platine liegen in **[hardware/](hardware/)**.

## 📚 Dokumentation

| Datei | Inhalt |
|---|---|
| [docs/installation.md](docs/installation.md) | Bauen, Adapter anschliessen, flashen |
| [docs/entscheidungen.md](docs/entscheidungen.md) | Warum es so gebaut ist – Energie, Einrichtung, Sensoren, Ausgangslage |
| [docs/ruhestrom.md](docs/ruhestrom.md) | Ruhestrom mit der Messfirmware messen |
| [hardware/README.md](hardware/README.md) | Schema und Baugruppen |
| [CHANGELOG.md](CHANGELOG.md) | Was sich je Version geändert hat, und warum |

Betrieb und Home Assistant bekommen eigene Dokumente, sobald es dort etwas zu
beschreiben gibt.

## 🧬 Herkunft

FilaHygro entstand 2021 als gemeinsames Projekt von Roger Widmer und Michael
Tanner, damals mit einer Firmware für die Arduino IDE und einer Platine, die bis
heute in Betrieb ist. Die Firmware in diesem Repository ist neu geschrieben,
die Platine ist unverändert übernommen.

## ⚠️ Haftung

Das Gerät arbeitet mit einer Li-Ion-Zelle. Laden und Tiefentladeschutz
übernimmt das TP4056-Modul, nicht die Firmware.

Keine geprüfte Software, keine Gewähr, Nutzung auf eigene Gefahr.

## 📄 Lizenz

MIT – siehe [LICENSE](LICENSE).
