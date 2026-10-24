# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [0.1.0] - 2026-10-24

Gerüst des Neuaufbaus. Die Firmware baut, meldet ihre Version und schläft;
sie misst und sendet noch nicht.

### Added

- PlatformIO-Projekt für ESP-12F (`espressif8266@4.2.1`, Board `esp12e`).
- Firmware-Gerüst: Version auf der seriellen Schnittstelle, danach Deep Sleep.
- Schema der Platine Rev 2 unter `hardware/`.
- README, Installationsanleitung und Begründung des Aufbaus unter `docs/`.

[Unreleased]: https://github.com/tsgwiro1/filahygro/compare/v0.1.0...HEAD
[0.1.0]: https://github.com/tsgwiro1/filahygro/releases/tag/v0.1.0
