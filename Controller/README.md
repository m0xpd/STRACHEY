# Controller

This folder contains details of the code which implements the STRACHEY sequencer.

I originally intended to build the code on an STM32, expecting that both the I/O requirements and the complexity of the application would take me beyond the scope of simpler microcontrollers. 
However, I found that I could fit the features I had targetted into code for a simple little [ARDUINO NANO](https://docs.arduino.cc/hardware/nano) - so that is what has been used.

There is an [Arduino script](https://github.com/m0xpd/STRACHEY/blob/main/Controller/Code/STRACHEY_Sequencer_1v0.ino) in the Code folder.

The code includes a Euclidean pattern generator written by Tom Whitwell, which I originally discovered on [Craig Lee's site](https://clsound.com/euclideansequenc.html)
