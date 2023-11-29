# STRACHEY
A Random Looping Sequencer for Eurorack


STRACHEY is a new kind of sequencer for electronic music applications. STRACHEY implements my [Tuning Strategy for Klee-type Sequencers](https://github.com/m0xpd/TuningStrategyForVoltages) and - as such - 
it is directly inspired by Music Thing Modular's [Turing Machine](https://www.musicthing.co.uk/Turing-Machine/) and its [Voltages expander]([https://www.musicthing.co.uk/Turing-Voltages-Expander/](https://www.musicthing.co.uk/Turing-Volts-Expander/)). 

STRACHEY contains an implementation of the Turing Machine, offering most of the features of the original hardware, including the ability to interface to expanders, such as [Pulses](https://www.musicthing.co.uk/Turing-Pulse-Expander/), [Volts](https://www.musicthing.co.uk/Turing-Volts-Expander/) and even [Voltages](https://www.musicthing.co.uk/Turing-Volts-Expander/). 
Most importantly, STRACHEY directly implements the fixed tunings presented in my [Tuning Strategy](https://github.com/m0xpd/TuningStrategyForVoltages), without the need to set these up on a Voltages expander (which is a laborious and delicate task). This offers opportunity to quickly expand and develop the tunings (e.g. using octave expansions) and - most importantly - to instantly move between the tunings (allowing modulation and "chord progressions"). However, STRACHEY does more...

STRACHEY has three channels of outputs: A, B and Y, all of which derive their timing from a master clock. The clock signal either is applied from an external source applied to the Clock input or 
(in the absence of such an input) is supplied by a simple oscillator integral to STRACHEY. Outputs A and Y both apprear with every beat of this clock.

Channel Y is the conventional 'Turing Machine' Output signal, formed of a weighted sum of the Turing Machine's gates 1:8  (the weights being an exponential series proprtional to 1, 0.5, 0.25, 0.125, ...). 
The Y signal is scaled to range between 0 and 5V and is provided for use as a general modulations source.

Channel A is the main STRACHEY output. It produces output (to be interpreted as a pitch 1V/8ve pitch CV signal) at the rate of the main signal clock. It is set to span over a maximum of around 
six and a half octaves at a resolution of 51 quantisation steps per semitone (meaning there will be less than a 2 cent error in tuning over the range).

Channel B is the secondary STRACHEY output. It operates at the same resolution as channel B (but - for reasons which will become apparent, the whole of this resolution is not exercised). The outputs on channel B occur on onsets produced by a Euclidean pattern generator, which has length determined by the Turing Machine's LENGTH parameter and density determined by the DENSITY control. LENGTH and DENSITY are both controllable by front panel potentiometers and can further be controlled by CV inputs. This makes the onsets of the pattern on channel B a subset of the beats of the main system clock, a pattern which has rhythmic interest and a pattern which can be made to evolve. The same gate sequence (produced by the Turing Machine) and the same weight vector (determined by the tuning selected by the TUNING controls) produces the channel A and B outputs, so the notes are the same. BUT channel A and B occur at different rates (as described) and the weight vector can be permuted before channel A's output is formed, giving STRACHEY an entirely new dimension of variability relative to other Klee sequencers, including the Turing Machine.

