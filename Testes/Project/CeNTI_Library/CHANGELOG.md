# Change Log
All notable changes to this library will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).

## [Unrealeased] - dd-mm-yyyy
Here we write upgrading notes. This notes must be as straightforward as possible.

### Added
...

### Changed
...

### Fixed
...

## [1.0.1] - 12-01-2024
Fix some issues with MCC includes.

### Changed
- Change file name of CeNTI_lib_defines.h to CeNTI_Lib_defines.h.

### Fixed
- Fixed path for MCC generated code files.

## [1.0.0] - 10-01-2024
Initial version based on an old CeNTI library version.

### Added
- Library files base;
- Major support to ATSAM (ATMEL Start and Harmony), ATTiny (Melody), PIC18 (MCC Classic and Melody), STM32L4  (CUBEMX), STM32F4 (CUBEMX), EFR32 (Silicon Labs Configurator Project), and NRF52 (NRFX);
- Communication examples for I2C master, SPI master, UART RingBuffer, UART ASync for some devices;
- Delay function for some devices;
- ArrayList;
- CRC;
- Debug;
- FIFO;
- SoftTimer;
- Time;
- Utilities.
