# Ruhestrom messen

Wie viel das Gerät im Deep Sleep zieht und woher dieser Strom kommt. Warum
das zuerst geklärt wird, steht in
[entscheidungen.md](entscheidungen.md#ausgangslage-stromverbrauch).

---

## Inhalt

1. [Voraussetzungen](#1-voraussetzungen)
2. [Messfirmware flashen](#2-messfirmware-flashen)
3. [Messen](#3-messen)
4. [Messreihe](#4-messreihe)

---

## 1. Voraussetzungen

- Strommessgerät mit µA-Auflösung, zum Beispiel ein uCurrent (EEVblog) vor
  einem Multimeter
- Geladene Zelle im Gerät
- Flash-Werkzeug wie in [installation.md](installation.md)

Gemessen wird an der Steckbrücke **J2 (Isens)**. Sie liegt direkt in Reihe
mit der Zelle. Der Messwert enthält also alles, was die Zelle hergibt,
einschliesslich des Lade- und Schutzmoduls.

## 2. Messfirmware flashen

```bash
pio run -e sleeptest -t upload
```

Die Messfirmware setzt die Pins wie im Betrieb, lässt den Funk aus und geht in
den Deep Sleep, bis **RESET** gedrückt wird. Sie wacht nicht nach Zeit auf.

Im seriellen Monitor erscheint nach RESET:

```
FilaHygro 0.2.0 – sleeptest
Deep Sleep bis RESET
```

Danach fällt der Strom von rund 70 mA auf wenige µA; ein Netzteil zeigt
≈ 0 mA. Liegt dabei ein Strommessgerät im µA-Bereich unüberbrückt in Reihe,
startet der ESP8266 nicht und gibt nichts aus, siehe unten.

## 3. Messen

Das Gerät zieht beim Start kurz rund 70 mA. Im µA-Bereich des Messgeräts
fällt dabei so viel Spannung ab, dass der ESP8266 nicht startet. Er bleibt
halb gestartet hängen und zieht dauernd über 100 mA. Deshalb in dieser
Reihenfolge:

1. Messgerät im µA-Bereich an J2 anschliessen (Jumper gezogen).
2. Die **Eingangsklemmen des Messgeräts** mit einem kurzen Kabel überbrücken.
3. **RESET** drücken und 1–2 Sekunden warten, bis das Gerät schläft.
4. Die Brücke am Messgerät entfernen.
5. Einige Sekunden warten, bis der Wert steht, und ablesen.

Mit dem uCurrent im µA-Bereich gilt 1 mV am Multimeter = 1 µA.

Ist der serielle Adapter noch an J1 angeschlossen, kann er über RX und TX
Strom ins Gerät speisen. Für die Messung abziehen.

Nach jedem Umbau an der Platine wieder bei Schritt 1 beginnen.

## 4. Messreihe

Je ein Gerät pro Sensortyp (SHT31-D, SHT40, HDC1080). Jede Stufe baut auf der
vorigen auf:

| Stufe | Zustand | Zeigt |
|---|---|---|
| 1 | Gerät komplett | Ruhestrom heute |
| 2 | Sensorplatine abgetrennt (VIN gelöst) | Anteil der Sensorplatine |
| 3 | zusätzlich R12 offen | Anteil des Spannungsteilers |

Was nach Stufe 3 übrig bleibt, ziehen ESP-12F, Spannungsregler und das Lade-
und Schutzmodul. Erwartet werden dafür 25 bis 40 µA. Liegt der Rest deutlich
darüber, zieht etwas anderes auf der Platine Strom, oder ein Pin steht
ungünstig.

Danach die Betriebsfirmware wieder flashen:

```bash
pio run -t upload
```
