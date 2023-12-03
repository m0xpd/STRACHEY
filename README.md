# STRACHEY
A Random Looping Sequencer for Eurorack

-image-

STRACHEY is a new kind of sequencer for electronic music applications. 

STRACHEY's novelty is two-fold: 
* it directly implements my [tuning strategy](https://github.com/m0xpd/TuningStrategyForVoltages) for Klee-type sequencers and
* it introduces a Permutation Matrix between the gates and the weights, adding a new dimension of variability

STRACHEY is published under a Creative Commons By-SA 4.0 [License](https://github.com/m0xpd/STRACHEY/blob/main/LICENSE.txt). 

I you wish to build one, or if you're just curious, you can find [description of the hardware here](https://github.com/m0xpd/STRACHEY/tree/main/Hardware) and [details of the software running in the controller here](https://github.com/m0xpd/STRACHEY/tree/main/Controller).

There are some [specifications here](https://github.com/m0xpd/STRACHEY/blob/main/README.md#specifications) and descriptions of application and patching here.

# Background

The STRACHEY sequencer is named for [Christopher Strachey](https://en.wikipedia.org/wiki/Christopher_Strachey), who (amongst many other accomplishments) was the first person in England to [program a computer to make music](https://link.springer.com/chapter/10.1007/978-3-319-53280-6_8), leading to the world's [first recording of computer-generated music](http://curation.cs.manchester.ac.uk/digital60/www.digital60.org/media/mark_one_digital_music/mark_one_digital_music.mp3), developed one of the world's first computer games, and developed the programming language CPL, a precursor of C (which is used in the code which runs this 
STRACHEY sequencer).

STRACHEY implements my [Tuning Strategy for Klee-type Sequencers](https://github.com/m0xpd/TuningStrategyForVoltages) and, as such, 
it is directly inspired by Music Thing Modular's [Turing Machine](https://www.musicthing.co.uk/Turing-Machine/) and its [Voltages expander](https://www.musicthing.co.uk/Turing-Volts-Expander/). 

STRACHEY contains an implementation of the Turing Machine ('TM'), offering most of the features of the original hardware, including the ability to interface to expanders, such as [Pulses](https://www.musicthing.co.uk/Turing-Pulse-Expander/), [Volts](https://www.musicthing.co.uk/Turing-Volts-Expander/) and even [Voltages](https://www.musicthing.co.uk/Turing-Volts-Expander/). 
Most importantly, STRACHEY directly implements many of the fixed tunings presented in my [Tuning Strategy](https://github.com/m0xpd/TuningStrategyForVoltages), without the need to set these up on the sliders of a Voltages expander (which is a laborious and delicate task). This offers opportunity to quickly expand and develop the tunings (e.g. using octave expansions) and - most importantly - to instantly move between the tunings (allowing modulation and "chord progressions"). However, STRACHEY does more...

STRACHEY has three channels of outputs: A, B and Y, all of which derive their timing from a master clock. This architecture reflects another source of inspiration for STRACHEY: Mutable Instruments' [Marbles](https://pichenettes.github.io/mutable-instruments-documentation/modules/marbles/). 

STRACHEY's clock signal can be applied from an external source to the Clock input (as in the TM) or (in the absence of an external clock) is generated by a simple 
oscillator integral to STRACHEY. Outputs A and Y both appear on every beat of this clock.

Channel Y is the conventional TM Output signal, formed of a weighted sum of the TM's gates 1:8  (the weights being an exponential series, proportional to 1, 0.5, 0.25, 0.125, ...). 

The Y signal is scaled to range between 0 and 5V and is provided for use as a general modulation source.

Channel A is the main STRACHEY output. It produces output (to be interpreted as a pitch 1V/8ve pitch CV signal) at the rate of the main signal clock. 
It is set to span a maximum of around six and a half octaves at a resolution of 51 quantisation steps per semitone 
(meaning there will be less than a 2 cent error in tuning over the system's range).

Channel B is the secondary STRACHEY output. It operates at the same resolution as channel B but (for reasons which will become apparent), the pitch range 
of channel B is lower than that of channel A. 

The outputs on channel B occur on onsets produced by a Euclidean pattern generator, which has length determined by the Turing Machine's LENGTH parameter and density determined by the DENSITY control. LENGTH and DENSITY are both controllable by front panel potentiometers and can further be controlled by CV inputs. This makes the onsets of the pattern on channel B: 
* a subset of the beats of the main system clock,
* a pattern which has rhythmic interest and
* a pattern which can be made to evolve.

The same gate sequence (generated by the Turing Machine) and the same initial weight vector (determined by the tuning selected by the TUNING controls) produces the channel A and B outputs, so the set of allowed pitches are the same. However, there are two changes which can be applied to the weight vector used in forming the output from channel A.

Firstly, the initial weight vector can be permuted before channel A's output is formed, giving STRACHEY an entirely new dimension of variability relative to other Klee sequencers, including the Turing Machine. 

Secondly, the initial weight vector can be subject to octave span extensions (under control of the SPAN controls - both potentiometer and CV input), which extend the pitch range of the channel A output. 

Neither the permutations or the octave extensions of channel A's weight vector are applied to channel B.

So - channel B has a generally reduced pitch span compared to channel A (as there is no octave extension added via SPAN) and there is no variation introduced by permutation it also has less dense onsets; it samples notes from the set of pitches within the fundamental range of channel A's pitch distribution on a rhythmic sub-pattern of variable DENSITY. It is paricularly useful for forming bass or melody against a fuller arpeggiated 'continuo' from channel A.


The idea of introducing permutation between the gates and weights of a Random Looping Sequencer is (as far as I'm aware) a new idea. 

The idea of stopping and single-stepping a sequencer is familiar and I have [demonstrated some other effects](https://www.youtube.com/watch?v=kFBzPTS7XLM) obtained with other multi-rate or asynchronous approaches. But the synchronous permutation of the mapping between gates and weights is less familiar. One notable exception is the idea of reversing the scan direction of a sequencer, (which can be expreesed as a simple permutation) and is seen e.g. on sequencers from [MFOS](https://musicfromouterspace.com/analogsynth_new/SEQ16_2006/SEQ16_2006.php) and [Doepfer](https://doepfer.de/a154.htm). 

There are other synchronous permutations worth exploring.

Back in 2017 I made a gate sequencer which was inspired by the patterns used in [Change Ringing](https://en.wikipedia.org/wiki/Change_ringing), a perversely English way of sounding the bells of a Church. These patterns are called "Methods". The key ingredient of Change Ringing is an exploration of the permutations by which a number of bells may be sounded in sequence. In the case of my module, I implemented four of the traditional "Methods"  (Rounds, Plain Hunt, Grandsire and Plain Bob) to trigger any number of gates (any "Stage") between 4 and 8 and - for the purposes of demonstration - added CV pitch outputs typical of the diatonic tuning of bells. 

STRACHEY uses a fixed number of weights ("Stage") to form the pitch output from the gate vector - the eight inherited from MTM's Voltages expander. If these 8 weights are seen in analogy with 8 bells (which is the standard stage in a larger bell tower for change ringing), some of STRACHEY's methods for permuting the weights can be related to bell ringing.

STRACHEY can implement two standard bell ringing methods; "rounds" (which is the bell-ringing term when the permuatation martix is fixed at the identity matrix) and "Plain Hunt Major" (Plain Hunt is a standard algorithm for changing the permutation matrix and 'Major' refers to the fact that it is applied to 8 weights). However, STRACHEY can also intoduce variation through the permutation matrix by other means.

STRACHEY can generate a permutation matrix which sorts the weights in pitch order, either descending or ascending. It can do this in two ways - either in an immediate sort or as one step of a [bubble sort](https://en.wikipedia.org/wiki/Bubble_sort) (such that a number of successive number of calls to this process are required to achieve the final sort). Each call is instatiated at the start of the cycle (of length determined by the Turing Machine's LENGTH parameter), if requested by an 'Evolve' input during the previous cycle. STRACHEY can also reset the permutation matrix (to the identity matrix - playing 'rounds' in bell-ringing parlance), can fully randomise the permutation matrix or can introduce one random swap in the permutation matrix associated with swapping position of a random (non-zero) weight with one of its neighbours. (This last variation is rather like the underlying mechanism in [Call-changing](https://en.wikipedia.org/wiki/Call_changes) but is - in this case - randomised rather than designed.)




# Specifications

STRACHEY is 18HP wide.

It extends xx mm behind the front panel when a conventional Eurorack power header (with strain relief) is fitted.

STRACHEY draws:
xx mA from the +12V power line
xx mA from the -12V power line
and nothing from the 5V power line. 

All inputs are protected against over/under voltage.

Most of the CV inputs are intended to operate over a 0:5V control range. However, the Density and Method inputs are applied to attenuverters; these inputs will respond to signals spanning 
the entire bipolar Eurorack voltage range (+/- 12V).

The external Clock input is triggered by signals exceeding an (upward) threshold of 1.25V.

The Evolve input similarly responds to signals exceeding an (upward) threshold of 1.25V.

The Write input is held at mid-voltage (2.5V) by an internal resistor network. Pulling this voltage below xx V will write a '0' and above xx V will write a '1'.



