# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [0.2.0] - 2026-10-25

Ruhestromanalyse. Eine Messfirmware zeigt, wie viel ein Gerät im Deep Sleep
zieht; die Messung an den gebauten Geräten ergab rund 30 µA für die Schaltung
und einzelne defekte Bauteile als Ursache der hohen Werte.

### Added

- Messfirmware `sleeptest` (`pio run -e sleeptest`): setzt die Pins, lässt den
  Funk aus und schläft bis RESET, damit der Ruhestrom ohne Wachphasen messbar
  ist.
- Anleitung zur Messung des Ruhestroms in `docs/ruhestrom.md`, mit
  Überbrückung des Messgeräts beim Start.
- Ergebnis der Messreihe in `docs/entscheidungen.md`; Hinweis in
  `hardware/README.md`, jedes Gerät vor dem Einsatz zu messen.

### Changed

- BME280 als vierter Sensor vorgesehen (Erkennung über die Chip-ID, um
  BMP280-Module ohne Feuchtemessung auszuschliessen).
- Laufzeitrechnung auf eine 3000-mAh-Zelle (LG HG2) korrigiert.

### Fixed

- Belegung von J1 in `docs/installation.md`: Pin 2 ist TX, Pin 3 RX des ESP
  (Rev 2). Hinweis für ältere Platinen mit vertauschten Leitungen.

## [0.1.0] - 2026-10-24

Gerüst des Neuaufbaus. Die Firmware baut, meldet ihre Version und schläft;
sie misst und sendet noch nicht.

### Added

- PlatformIO-Projekt für ESP-12F (`espressif8266@4.2.1`, Board `esp12e`).
- Firmware-Gerüst: Version auf der seriellen Schnittstelle, danach Deep Sleep.
- Schema der Platine Rev 2 unter `hardware/`.
- README, Installationsanleitung und Begründung des Aufbaus unter `docs/`.

[Unreleased]: https://github.com/tsgwiro1/filahygro/compare/v0.2.0...HEAD
[0.2.0]: https://github.com/tsgwiro1/filahygro/compare/v0.1.0...v0.2.0
[0.1.0]: https://github.com/tsgwiro1/filahygro/releases/tag/v0.1.0
