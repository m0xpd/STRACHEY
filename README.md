# STRACHEY
A Random Looping Sequencer for Eurorack

<p width=100%, align="center">
<img width=40%, src="https://github.com/m0xpd/STRACHEY/blob/main/Hardware/Graphics/STRACHEY%20front%20perspective%20LoRes.jpg">
</p>

STRACHEY is a new kind of sequencer for electronic music applications. 

STRACHEY's novelty is two-fold: 
* it directly implements my [tuning strategy](https://github.com/m0xpd/TuningStrategyForVoltages) for Klee-type sequencers and
* it introduces a [Permutation Matrix](https://en.wikipedia.org/wiki/Permutation_matrix) between the gates and the weights, adding a new dimension of variability

STRACHEY is published under a Creative Commons BY-SA 4.0 [License](https://github.com/m0xpd/STRACHEY/blob/main/LICENSE.txt). 

I you wish to build one, or if you're just curious, you can find [description of the hardware here](https://github.com/m0xpd/STRACHEY/tree/main/Hardware) and [details of the software running in the controller here](https://github.com/m0xpd/STRACHEY/tree/main/Controller).

There are some [specifications here](https://github.com/m0xpd/STRACHEY/blob/main/README.md#specifications) and descriptions of application and patching here.

# Background

The STRACHEY sequencer is named for [Christopher Strachey](https://en.wikipedia.org/wiki/Christopher_Strachey), who (amongst many other accomplishments) was the first person in England to [program a computer to make music](https://link.springer.com/chapter/10.1007/978-3-319-53280-6_8), leading to the world's [first recording of computer-generated music](http://curation.cs.manchester.ac.uk/digital60/www.digital60.org/media/mark_one_digital_music/mark_one_digital_music.mp3).

Christopher Strachey developed [one of the world's first computer games](https://historyofinformation.com/detail.php?entryid=3731), and developed the programming language CPL, a precursor of C (which is used in the code which runs this 
STRACHEY sequencer).

STRACHEY implements my [Tuning Strategy for Klee-type Sequencers](https://github.com/m0xpd/TuningStrategyForVoltages) and, as such, 
it is directly inspired by Music Thing Modular's [Turing Machine](https://www.musicthing.co.uk/Turing-Machine/) and its [Voltages expander](https://www.musicthing.co.uk/Turing-Volts-Expander/). 

STRACHEY contains an implementation of the Turing Machine ('TM'), offering most of the features of the original hardware, including the ability to interface to expanders, such as [Pulses](https://www.musicthing.co.uk/Turing-Pulse-Expander/), [Volts](https://www.musicthing.co.uk/Turing-Volts-Expander/) and even [Voltages](https://www.musicthing.co.uk/Turing-Volts-Expander/). 
Most importantly, STRACHEY directly implements many of the fixed tunings presented in my [Tuning Strategy](https://github.com/m0xpd/TuningStrategyForVoltages), without the need to set these up on the sliders of a Voltages expander (which is a laborious and delicate task). This offers opportunity to quickly expand and develop the tunings (e.g. using octave expansions) and - uniquely - to instantly move between the tunings (allowing modulations and "chord progressions" to be made). However, STRACHEY does more...

STRACHEY has three channels of outputs: A, B and Y, all of which derive their timing from a master clock. This architecture reflects another source of inspiration for STRACHEY: Mutable Instruments' [Marbles](https://pichenettes.github.io/mutable-instruments-documentation/modules/marbles/). 

STRACHEY's clock signal can be applied from an external source to the Clock input (as in the TM) or (in the absence of an external clock) is generated by a simple 
oscillator integral to STRACHEY. Outputs A and Y both appear on every beat of this clock.

Channel Y is the conventional TM 'OUT' signal, formed of a weighted sum of the TM's gates 1:8  (the weights being an exponential series, proportional to 1, 0.5, 0.25, 0.125, ...). 

STRACHEY's Y signal is scaled to range between 0 and 5V and is provided for use as a general modulation source.

Channel A is the main STRACHEY output. It produces an output (to be interpreted as a 1V/octave pitch CV signal) at the rate of the main signal clock. 
It is set to span a maximum of around six and a half octaves at a resolution of 51 quantisation steps per semitone 
(meaning there will be less than a 2 cent error in tuning over the system's range).

Channel B is the secondary STRACHEY output. It operates at the same resolution as channel B but (for reasons which will become apparent), the pitch range 
of channel B is lower than that of channel A. 

The outputs on channel B occur on onsets produced by a Euclidean pattern generator, which has length determined by the Turing Machine's LENGTH parameter and density determined by the DENSITY controls. LENGTH and DENSITY are both controllable by front panel potentiometers and can further be controlled by CV inputs. This makes the onsets of the pattern on channel B: 
* a subset of the beats of the main system clock,
* a pattern which has rhythmic interest and
* a pattern which can be made to evolve.

The same gate sequence (generated by the Turing Machine) and the same initial weight vector (determined by the tuning selected by the TUNING controls) produce the channel A and B outputs, so the set of allowed pitches are the same. However, there are two changes which can be applied to the weight vector used in forming the output from channel A.

Firstly, the initial weight vector can be permuted before channel A's output is formed, giving STRACHEY an entirely new dimension of variability relative to other Klee sequencers, including the Turing Machine. 

Secondly, the initial weight vector can be subject to octave span extensions (under control of the SPAN controls - both potentiometer and CV input), which extend the pitch range of the channel A output. 

Neither the permutations or the octave extensions of channel A's weight vector are applied to channel B.

So - channel B has a generally reduced pitch span compared to channel A (as there is no octave extension added via SPAN) and there is no variation introduced by permutation. It also has less dense onsets; it samples notes from the set of pitches within the fundamental range of channel A's pitch distribution on a rhythmic sub-pattern of variable DENSITY. It is paricularly useful for forming bass or melody against a fuller, arpeggiated 'continuo' from channel A.

# Permuting the Weights of a Step Sequencer

The idea of introducing permutation between the gates and weights of a Random Looping Sequencer is (as far as I'm aware) a new idea. 

The idea of stopping and single-stepping a sequencer is, of course, familiar and I have [demonstrated some other effects](https://www.youtube.com/watch?v=kFBzPTS7XLM) obtained with multi-rate or asynchronous approaches. But synchronous permutation of the mapping between gates and weights is less familiar. One notable exception is the idea of reversing the scan direction of a sequencer, (which can be expressed as a simple permutation) and is seen on both 'DIY' sequencers from [MFOS](https://musicfromouterspace.com/analogsynth_new/SEQ16_2006/SEQ16_2006.php) and commercial units from e.g. [Doepfer](https://doepfer.de/a154.htm). STRACHEY can - of course - reverse it's scan direction, both by flipping the current permutation and by resetting to a reversed version of the starting weight vector.

There are other synchronous permutations worth exploring.

Back in 2017 I made a gate sequencer 

<p width=100%, align="center">
<img width=20%, src="https://github.com/m0xpd/STRACHEY/blob/main/Hardware/Graphics/Camp%20front%20perspective%20LoRes.jpg">
</p>

which was inspired by patterns used in [Change Ringing](https://en.wikipedia.org/wiki/Change_ringing), a perversely English way of sounding the bells of a Church. These patterns are called "Methods". The key ingredient of Change Ringing is an exploration of the permutations by which a number of bells may be sounded in sequence. In the case of my module, I implemented four of the traditional "Methods"  ([Rounds](https://jaharrison.me.uk/Ringing/Glossary/R.html#rounds), [Plain Hunt](https://en.wikipedia.org/wiki/Plain_hunt), [Grandsire](https://en.wikipedia.org/wiki/Grandsire) and [Plain Bob](https://www.ringing.info/plp/pb8/index.html)) to trigger any number of gates (any "[Stage](https://jaharrison.me.uk/Ringing/Glossary/S.html#stage)") between 4 and 8 and - for the purposes of demonstration - I added a 1V/octave pitch CV output, set to be typical of the diatonic tuning of a ring of bells. 

I was, therefore, entirely familiar with the idea of using permutations in general (and permutations from bell ringing in particular) in a step sequencer. The only further inventive step for me in the development of STRACHEY was the extension of these ideas to a Klee-type sequencer. That step involved the concept of the introduction of a [permutation matrix](https://en.wikipedia.org/wiki/Permutation_matrix) between the gates and the weights in the scalar product which forms the sequencer output - for both a conventional sequencer and a Klee sequencer. (The actual coding doesn't require matrix methods - it is achieved in [the code](https://github.com/m0xpd/STRACHEY/blob/main/Controller/Code/STRACHEY_Sequencer_1v0.ino) just by indexing within the scalar product. The matrix is just a conceptual and mathematical convenience.)

STRACHEY uses a fixed number of weights ("Stage") to form the pitch output from the gate vector: the eight inherited from MTM's Voltages expander. If these 8 weights are seen in analogy with 8 bells (which is the standard stage in a larger bell tower for change ringing), some of STRACHEY's methods for permuting the weights can be related to bell ringing.

STRACHEY currently implements two standard bell ringing methods; "[rounds](https://jaharrison.me.uk/Ringing/Glossary/R.html#rounds)" (which is the bell-ringing term when the permuatation matrix is fixed at the identity matrix) and "Plain Hunt Major" ('Plain Hunt' is - as we've seen - a [standard algorithm](https://en.wikipedia.org/wiki/Plain_hunt) for changing the permutation matrix and 'Major' is [bell-ringing jargon](https://jaharrison.me.uk/Ringing/Glossary/M.html#major) indicating that the algorithm is applied on a stage of 8 weights). 

In both cases, STRACHEY will implement [plain courses](https://jaharrison.me.uk/Ringing/Glossary/P.html#plaincourse) of these methods (however, there is a random variation below, similar to a bell-ringing ['single' change](https://jaharrison.me.uk/Ringing/Glossary/S.html#singlechange), by which the hunt may be changed, to extend the method toward a longer pattern). By this means, STRACHEY can be set in rounds or plain hunt, using the METHOD controls (potentiometer or CV), and set to run on course, by asserting the CHANGE input (either by pressing the Change button or holding down the Change CV input) with occasional calls to a random 'single' by occasionally changing the METHOD to the random single swap.  

STRACHEY can also intoduce variation through the permutation matrix by other means.

STRACHEY can sort the weights in pitch order, either descending or ascending. It can do this in two ways - either in an immediate sort or as one step of a [bubble sort](https://en.wikipedia.org/wiki/Bubble_sort) (such that a number of successive number of calls to this process are required to achieve the final sort). Each change is made at the start of the cycle (of length determined by the Turing Machine's LENGTH parameter), if requested by an 'Change' input during the previous cycle. STRACHEY can also reset the permutation matrix (to the identity matrix - playing 'rounds' in bell-ringing parlance), can fully randomise the permutation matrix or can introduce one random swap in the permutation matrix associated with swapping position of a random weight with one of its neighbours. (This last variation is rather like the underlying mechanism in [Call-changing](https://en.wikipedia.org/wiki/Call_changes) but is - in this case - randomised rather than designed.)

A table of all the (currently implemented) METHODS is presented below:





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

??? The Evolve input similarly responds to signals exceeding an (upward) threshold of 1.25V.

The Write input is held at mid-voltage (2.5V) by an internal resistor network. Pulling this voltage below xx V will write a '0' and above xx V will write a '1'.



