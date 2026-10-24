# Entscheidungen

Dieses Dokument erklärt, **warum** die Firmware so gebaut wird. Die Schritte
zum Bauen und Flashen stehen in [installation.md](installation.md).

---

## Inhalt

- [Energie nur fürs Messen](#energie-nur-fürs-messen)
- [Einstellungen im Portal statt in Home Assistant](#einstellungen-im-portal-statt-in-home-assistant)
- [Keine Konfigurationsdateien](#keine-konfigurationsdateien)
- [Sensor einmal erkennen](#sensor-einmal-erkennen)
- [Kalibrierung der Akkuspannung](#kalibrierung-der-akkuspannung)
- [Ladestand aus der Li-Ion-Kurve](#ladestand-aus-der-li-ion-kurve)
- [Warum nicht ESPHome](#warum-nicht-esphome)
- [Ausgangslage Stromverbrauch](#ausgangslage-stromverbrauch)

---

## Energie nur fürs Messen

Das Gerät läuft aus einer Zelle. Im normalen Wachzyklus gibt es nur drei
Schritte: Sensor lesen, bei Bedarf senden, schlafen. Alles andere – Sensor
suchen, Home Assistant über das Gerät informieren, Einstellungen ändern – läuft
einmalig oder nur, wenn jemand es auslöst.

Jede Entscheidung unten folgt daraus.

## Einstellungen im Portal statt in Home Assistant

Einstellungen über MQTT aus Home Assistant zu holen, hiesse: in jeder
Wachphase einen Topic abonnieren und auf die Antwort des Brokers warten. Das
verlängert jede Wachphase um eine Zeit, in der das Funkmodul läuft, für Werte,
die sich fast nie ändern.

Deshalb gibt es ein Einrichtungsportal (WiFiManager). Das Gerät öffnet dafür
einen eigenen Access Point:

- wenn noch nichts eingerichtet ist,
- nach einem Doppel-Reset über die Taste RESET,
- nach mehreren fehlgeschlagenen Verbindungen.

Das Portal schliesst nach einer festen Zeit. Danach schläft das Gerät wieder.

Intervall und Sendeschwellen stehen fest in der Firmware. Sie ändern sich so
selten, dass dafür eine neue Firmware zumutbar ist.

## Keine Konfigurationsdateien

Alle Geräte bekommen dasselbe Binary. Was gerätespezifisch ist, wird am Gerät
eingegeben oder vom Gerät selbst ermittelt:

| Wert | Woher |
|---|---|
| WLAN, MQTT-Broker und Zugangsdaten | Portal |
| Gerätename | Vorgabe aus der Chip-ID, im Portal änderbar |
| Kalibrierung der Akkuspannung | Portal |
| Sensortyp | vom Gerät erkannt |
| Intervall, Sendeschwellen | fest in der Firmware |

Damit liegen keine Zugangsdaten im Code oder in Dateien neben dem Repository.
Ein neues Passwort heisst: Doppel-Reset, im Portal eingeben.

Die Konfiguration liegt im Flash. Nach dem Kaltstart hält das Gerät eine Kopie
im RTC-Speicher, der den Deep Sleep übersteht. Eine normale Wachphase liest nur
diese Kopie und braucht kein Dateisystem.

## Sensor einmal erkennen

Die gebauten Geräte tragen verschiedene Sensoren: SHT31-D, SHT40, HDC1080. Die
Firmware sucht den Sensor beim ersten Start und nach dem Portal und merkt sich
das Ergebnis. Danach liest sie direkt den bekannten Sensor. Neu gesucht wird
nur, wenn das Lesen fehlschlägt, etwa nach einem Sensortausch.

## Kalibrierung der Akkuspannung

Die Akkuspannung geht über einen Spannungsteiler (330 kΩ / 100 kΩ) auf den ADC
des ESP8266. Dessen Verstärkung streut von Exemplar zu Exemplar; bei den
bestehenden Geräten liegen die Umrechnungsfaktoren rund 6 % auseinander. Das
genügt, um den Ladestand deutlich zu verschieben.

Im Portal zeigt das Gerät die Spannung, die es mit dem Standardfaktor misst.
Man misst die Zelle mit einem Multimeter und gibt den Wert ein; das Gerät
berechnet daraus seinen Faktor. Das geschieht einmal pro Gerät.

## Ladestand aus der Li-Ion-Kurve

Der Ladestand wird aus der Spannung über eine Entladekurve für Li-Ion-Zellen
geschätzt. Sie gilt für 18650-Zellen wie für LiPo-Akkus, beide laden auf 4.2 V.
Eine lineare Umrechnung zwischen 4.2 V und 3.0 V zeigt im langen flachen
Mittelstück um 3.7 V deutlich zu wenig an.

## Warum nicht ESPHome

ESPHome würde die Anmeldung in Home Assistant mitbringen. Im Deep-Sleep-Betrieb
bleibt ein ESPHome-Gerät aber typischerweise mehrere Sekunden wach, bis es
verbunden ist und gesendet hat, statt einer knappen halben Sekunde. Das kostet
ein Mehrfaches an Akku. Die Anmeldung in Home Assistant lässt sich mit MQTT
Discovery einmalig und ohne Kosten im laufenden Betrieb lösen.

## Ausgangslage Stromverbrauch

Messung an der Firmware von 2021, ein Sendezyklus alle fünf Minuten:

| Phase | Dauer | Strom | Ladung je Zyklus |
|---|---|---|---|
| wach | 0.9 s | 72 mA | 0.018 mAh |
| Deep Sleep | 300 s | 0.4 mA | 0.033 mAh |

Im Mittel rund 0.61 mA, mit einer 4000-mAh-Zelle etwa 270 Tage. Zwei Drittel
davon verbraucht der Schlaf. 0.4 mA ist rund das Zwanzigfache dessen, was ein
ESP8266 im Deep Sleep allein braucht; der Rest kommt von der übrigen
Schaltung. Woher genau, klärt eine Messreihe an der Steckbrücke J2 (Isens),
bevor an der Firmware gespart wird.
