# Hardware
This folder contains details of STRACHEY's hardware.

STRACHEY is implemented using through-hole components mounted on two PCBs, each measuring 88 * 108 mm.

The majority of the electronics, incuding the Arduino Nano, which controls operations, are mounted on the '[main board](https://github.com/m0xpd/STRACHEY/blob/main/Hardware/Main/ReadMe.md)', whilst user-interface components are mounted on the '[control board](https://github.com/m0xpd/STRACHEY/blob/main/Hardware/Control/README.md)'.


The boards are joined electrically by two 18-way 0.1 inch headers and an 8-way 0.1 inch header. I cut the 18-way headers down from 40-way headers (of which I keep a stock). There are holes for M3 bolts to secure the boards together mechanically for those taking the system "on tour" - people using the system in a static installation will find that the headers alone provide a secure mechanical interface. The component board is secured to the front panel by the 16 "Thonkiconn" jack sockets and the 3 9mm potentiometers.  

The system was developed in [KiCad](https://www.kicad.org/) (the first electronic project I have undertaken using this software). KiCad projects for the boards are presented in the Main and Control folders, along with schematics, BoMs and circuit descriptions. A Front Panel design is presented as a KiCad project in the Panel folder.

All the hardware is published under [License](https://github.com/m0xpd/STRACHEY/blob/main/LICENSE.txt).
