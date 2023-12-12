# Control Board

This folder contains details of STRACHEY's control board, which you see below (component side).

<p width=100%, align="center">
<img width=40%, src="https://github.com/m0xpd/STRACHEY/blob/main/Hardware/Control/Graphics/STRACHEY%20Control%20Board%20Component%20Side%20Populated.jpg".  
</p>

The bottom side of the control board contains all the jacks, pots, tactile switches, and 24 LEDs, which mate with the Front Panel and form the user interface.

You can download the main board's schematic as a [.sch file]() into your PCB program (KiCad etc) or see a [PDF version]().

In addition to the front panel / UI components mentioned above, the control board hosts three 74HC595 serial in, parallel out shift registers. One of these communicates gate signals from inside the Aruino to the physical world - for display on the LEDs, for application to the DAC which drives the channel Y output, and for gate 1 output. The other 2 shift registers service all the other status indication lights.

STRACHEY is my first electronic project in KiCad and I am new to the BoM generator's .csv output format. I have decided to save this information [as an Excel file]() to retain some edits I made. 

There are a few points where the BoM should be emphasised, as the information is not made explicit in the schematic.
Firstly, whilst all potentiometers use the 9mm snap-in vertical footprint, only three are the usual 'Alpha' pots. These are VR2 (The TUNING Control), VR5 (The DENSITY control) & VR8 (The TURING Control). The remaining potentiometers are Song Huei 9mm Trimmers

Secondly, the momentary action 6mm 'tactile' switches, SW1:SW3 should be of 13mm size (or taller). The tip of the shaft of a 13mm switch protrudes through the front panel by a little over 1.5mm, which looks and feels right. If you want more, fit a 14mm or 15mm switch.

Finally, although the PCB shows a 3mm LED footprint, the front panel is drilled to accept 2mm "Lighthouse-type" LEDs. I have chosen to use green LEDs for the TUNING indication (LEDs 13:17, 19, 21 & 23) whilst the rest are red. Series resistors of 1K for the green and 10k for the red work well with the particular LEDs I'm using - hence the component values for the resistor networks RN1 & 2 etc.. However, you should check YOUR LEDs for appropriate brightness before fitting the resistors. 

The [.pcb file]() and [.pro file]() (togther with the [.sch file]() ) constitute a KiCad project, which define the Main board. 

[JLCPCB](https://jlcpcb.com) made the boards for my prototype and did their usual excellent job (usual disclaimer) - you can see the top and bottom sides of the Main Board below:

# Assembly

As with all such 'control boards' which mate with an accurately prepared front panel, it is advisable to fit the panel-mounting components into BOTH the PCB and panel before soldering, to ensure correct alignment. 

This is **particularly important** with all the tiny LEDs in STRACHEY, as alignment is critical!
