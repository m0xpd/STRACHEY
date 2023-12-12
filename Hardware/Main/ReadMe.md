# Main Board

This folder contains details of STRACHEY's Main Board which you seen below (component side) 

<p width=100%, align="center">
<img width=40%, src="https://github.com/m0xpd/STRACHEY/blob/main/Hardware/Main/Graphics/STRACHEY%20Main%20Board%20Component%20Side%20Populated.jpg".  
</p>

You can download the main board's schematic as a [.sch file](https://github.com/m0xpd/STRACHEY/blob/main/Hardware/Main/main%20board.kicad_sch) into your PCB program (KiCad etc) or see a [PDF version](https://github.com/m0xpd/STRACHEY/blob/main/Hardware/Main/main%20board%20schematic.pdf).

The Main Board hosts power supplies, the Arduino Nano, the DACs, output drivers, input protection and conditioning circuits, the Turing Machine Expansion port, and interface to the control Board.

I am new to KiCad and the BoM generator produces output in .csv format. I have decided to save this information [as an Excel file](https://github.com/m0xpd/STRACHEY/blob/main/Hardware/Main/Strachey%20main%20board%20BoM.xlsx) to retain some edits I made. 

There are a few minor points of potential confusion in the BoM (e.g. where I gave resistors value "10K" and others "10k"), but I'm sure you'll figure it out. Note particularly that the two multi-turn trimmers, TR1 and TR2  (the blue components seen in the photo above) are listed as having value 1k in the schematic and the BoM. I decided to use 10k components,as I had them to hand. Any value above 1k (and up to 100k) will work fine.

The [.pcb file](https://github.com/m0xpd/STRACHEY/blob/main/Hardware/Main/main%20board.kicad_pcb) and [.pro file](https://github.com/m0xpd/STRACHEY/blob/main/Hardware/Main/main%20board.kicad_pro) (togther with the [.sch file](https://github.com/m0xpd/STRACHEY/blob/main/Hardware/Main/main%20board.kicad_sch) ) constitute a KiCad project, which define the Main board. 

[JLCPCB](https://jlcpcb.com) made the boards for my prototype and did their usual excellent job (usual disclaimer) - you can see the top and bottom sides of the Main Board below:

<p width=100%, align="center">
<img width=80%, src="https://github.com/m0xpd/STRACHEY/blob/main/Hardware/Main/Graphics/STRACHEY%20Main%20Board%20Unpopulated.%20LoRes.jpg">  
</p>
  
  
