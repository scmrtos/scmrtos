scmRTOS
=======

Breif Description
-----------------
scmRTOS is tiny Real-Time Preemptive Operating System intended for use with Single-Chip Microcontrollers. scmRTOS is capable to run on tiny uCs with as small amount of RAM as 512 bytes. The RTOS is written on C++ and supports various platforms.

List of supported platforms for now:
------------------------------------
* MSP430
* AVR
* Blackfin
* ARM7
* Cortex-M0
* Cortex-M3
* Cortex-M4
* STM8

Key Features
------------

###Small
####Very small footprint:
* from 512 bytes of RAM
* from ~1K code

###Fast
####Minimal process switching latency:
* 900 ns on Cortex-M4 @ 168 MHz
* 1.8 us on Blackfin @ 200 MHz
* 2.7 us on Cortex-M3 @ 72 MHz
* 5 us on ARM7 @ 50 MHz
* 38-42 us on AVR @ 8 MHz
* 45-50 us on MSP430 @ 5 MHz
* 18-20 us on STM8 @ 16 MHz

###Modern
####Written entirely on C++:
* High reliability
* Simplicity and ease-of-use

###Extensible
####Extensions mechanism at kernel level:
* User defined extensions
* Debug features



