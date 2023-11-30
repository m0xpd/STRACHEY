# Hardware
This folder contains details of STRACHEY's hardware.

STRACHEY is implemented using through-hole components mounted on two PCBs, each measuring 88 * 108 mm.

The majority of the electronics, incuding the Arduino Nano, which controls operations, are mounted on the 'main board', whilst user-interface components are mounted on the 'control board'.
The control board also hosts two shift registers, implemented on three 74HC595 devices. The first shift register displays the gate vector (and outputs it to the expansion port) and the 
second shift register is used to support all the other LEDs, which display configuration / status information.

The system was developed in [KiCad](https://www.kicad.org/) (the first electronic project I have undertaken using this software). KiCad projects for the boards are presented in the Main and Control folders, along 
with schematics, BoMs and circuit descriptions.
