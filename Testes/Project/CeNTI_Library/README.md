# CeNTI Library

## Folders organization
### - HAL
*Hardware Abstraction Layer* is used to organize code that controls hardware. Inside there are the following folders:
- COM: \
    This folder contains all the communication functions.
- Defines: \
    This folder is where all the defines are set for all the other folders.
- GPIO: \
    This folder contains all the GPIO functions.
- Timers: \
    This folder contains all the functions for timers, delays, pwms, etc.

### - lib
*Library* is used to simplify the switch between microcontrollers and/or compilers. It also has some generic code to easily access and use. Inside there are the following folders:
- ArrayLists: \
    This folder contains a library that allows to manage an array of lists.
- CRC: \
    This folder contains a library that allows to calculate a CRC (8bits or 16bits).
- Debug: \
    This folder contains a library to use a serial com to print some debug messages.
- Defines: \
    This folder contains all the CeNTI library defines. Here is where mainly the user 
    needs to edit.
- FIFO: \
    This folder contains a library that allows to manage a FIFO.
- SoftTimer: \
    This folder contains a library with a software timer.
- Time: \
    This folder contains a library that allows to make operations with time more easily.
- Utils: \
    This folder contains some usefull codes.
- CeNTI_lib_includes.h:
    This file includes all the files that are enabled to more easily include all of them.