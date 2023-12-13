# STRACHEY

<p width=100%, align="center">
<img width=40%, src="https://github.com/m0xpd/STRACHEY/blob/main/Hardware/Graphics/STRACHEY%20front%20perspective%20LoRes.jpg">
</p>

STRACHEY is a new kind of sequencer for electronic music applications. 

STRACHEY's novelty is two-fold: 
* it directly implements my [tuning strategy](https://github.com/m0xpd/TuningStrategyForVoltages) for Klee-type sequencers and
* it introduces a dynamic [Permutation Matrix](https://en.wikipedia.org/wiki/Permutation_matrix) between the gates and the weights, adding a new dimension of variability

I you wish to build one, or if you're just curious, you can read or download [details of the hardware, including PCB and front panel designs](https://github.com/m0xpd/STRACHEY/tree/main/Hardware) and [a listing of the controller code](https://github.com/m0xpd/STRACHEY/tree/main/Controller).

There are some [specifications here](https://github.com/m0xpd/STRACHEY/blob/main/README.md#specifications) and some details of [Calibration and Configuration here](https://github.com/m0xpd/STRACHEY/blob/main/README.md#calibration-and-configuration). Further description of STRACHEY follows below.

STRACHEY is published under a Creative Commons BY-SA 4.0 [License](https://github.com/m0xpd/STRACHEY/blob/main/LICENSE.txt). 

# Background

The STRACHEY sequencer is named for [Christopher Strachey](https://en.wikipedia.org/wiki/Christopher_Strachey), who (amongst many other accomplishments) was the first person in England to [program a computer to make music](https://link.springer.com/chapter/10.1007/978-3-319-53280-6_8), leading to the world's [first recording of computer-generated music](http://curation.cs.manchester.ac.uk/digital60/www.digital60.org/media/mark_one_digital_music/mark_one_digital_music.mp3).

Christopher Strachey developed [one of the world's first computer games](https://historyofinformation.com/detail.php?entryid=3731), and developed the programming language CPL, a precursor of C (which is used in the code which runs this STRACHEY sequencer).

STRACHEY implements my [Tuning Strategy for Klee-type Sequencers](https://github.com/m0xpd/TuningStrategyForVoltages) and, as such, 
it is directly inspired by Music Thing Modular's [Turing Machine](https://www.musicthing.co.uk/Turing-Machine/) and its [Voltages expander](https://www.musicthing.co.uk/Turing-Volts-Expander/). STRACHEY was built on my own experiences and habits, formed when using the Turing Machine with its Voltages expander; STRACHEY tries to capture and make accessible all which I found *musically useful* within the vast space covered by the Turing Machine. 

STRACHEY contains an implementation of the Turing Machine ('TM'). The control labelled "TURING" at top left of the module (and the associated CV input) is the equivalent of the large, conspicuous knob on the original TM hardware, and operates in exactly the same way. 

STRACHEY offers (almost) all the features of the original hardware, including the ability to interface to expanders, such as [Pulses](https://www.musicthing.co.uk/Turing-Pulse-Expander/), [Volts](https://www.musicthing.co.uk/Turing-Volts-Expander/) and even [Voltages](https://www.musicthing.co.uk/Turing-Volts-Expander/). It even adds several new features to its TM implementation (such as the START output and CV control over the Length parameter and the Write function).

More importantly, STRACHEY directly implements the fixed tunings presented in my [Tuning Strategy](https://github.com/m0xpd/TuningStrategyForVoltages), without the need to set these up on the sliders of a Voltages expander, which is a laborious and delicate task. This offers opportunity to quickly expand and develop the tunings (e.g. using octave expansions) and - uniquely - to instantly *move between* the tunings, allowing modulations and "chord progressions" to be explored. However, STRACHEY does more...

STRACHEY has three channels of analog output: A, B and Y, all of which derive their timing from a master clock. 

STRACHEY's clock signal can be applied from an external source to the Clock input (as in the TM). In the absence of an external signal, a clock is generated by a simple oscillator integral to STRACHEY. Outputs A and Y both appear on every beat of this clock.

Channel Y is the conventional TM 'OUT' signal, formed of a weighted sum of the TM's gates 1:8  (the weights being an exponential series, proportional to 1, 0.5, 0.25, 0.125, ...). STRACHEY's Y output is scaled to range between 0 and 5V and is provided for use as a general modulation source.

Channel A is the main STRACHEY output. It produces an output (to be interpreted as a 1V/octave pitch CV signal) at the rate of the main signal clock. 
It is set to span six and a half octaves at a resolution of 51 quantisation steps per semitone, meaning there will be less than a 2 cent error in tuning over the system's range, if we can trust the DAC linearity (experience to date has been entirely positive).

# STRACHEY Tunings

The control at top right of the panel, labelled "TUNING" (and the associated CV input) select pre-detemined settings of "weights", equivalent to the slider settings on a Turing Machine 'VOLTAGES' expander, or the knobs on any other sequencer. These weights, together with the gates generated by the Turing Machine, form the channel A (and channel B) outputs.

The weight settings are called 'Tunings' and they are selected from my [Tuning Strategy](https://github.com/m0xpd/TuningStrategyForVoltages) to be those which give an output which is musically useful. 

The tunings are arrange in three 'Banks'; 
* Bank A are "Basic" Tunings, 
* Bank B are mainly MODES
* Bank C are mainly 'Symmetric Scales'

The tunings presently implemented in the code are tabulated below:

| Tuning# | Description | Tuning Strategy # | Bank | Display |
|---|---|---|---|---|
| 0 | Root & Fifth | (3) | A | 10000000 |
| 1 | AEOLIAN (Natural minor) | 14 | A | 01000000 |
| 2 | Minor 7th | 5 | A | 00100000 |
| 3 | Major 7th | 6 | A | 00010000 |
| 4 | Diminished 7th | 8 | A | 00001000 |
| 5 | Augmented | 7 | A | 00000100 |
| 6 | "Sus 7th" Feel | 10 | A | 00000010 |
| 7 | "9th" Feel | 9 | A | 00000001 |
| 8 | Root & Fifth | (3) | A | 10000000 |
| 9 | AEOLIAN | 14 | B | 01000000 |
| 10 | DORIAN | 11 | B | 00100000 |
| 11 | PHRYGIAN | 13 | B | 00010000 |
| 12 | IONIAN | 18 | B | 00001000 |
| 13 | Hexatonic, IONIAN, missing 7th degree | 22 | B | 00000100 |
| 14 | Octatonic, IONIAN, with added flat 5 | 20 | B | 00000010 |
| 15 | Hexatonic, with no third | 23 | B | 00000001 |
| 16 | Root & Octave | (3) | C | 10000000 |
| 17 | Tritone | (15) | C | 01000000 |
| 18 | Augmented | 7 | C | 00100000 |
| 19 | Diminshed | 8 | C | 00010000 |
| 20 | Whole-tone | 16 | C | 00001000 |
| 21 | Chromatic | 17 | C | 00000100 |
| 22 | Major (IONIAN) | 19 | C | 00000010 |
| 23 | Descending Major Scale | N/A | C | 00000001 |

'Bank' is indicated by the stack of three LEDs in the centre, middle of the module. Bank A is indicated by the lowest LED.

'Display' shows the pattern illuminated on the 'TUNING' LEDs.

A bracket surrounding the Tuning Strategy number indicates that it is modified. 

Some tunings are intentionally repeated in the table above for ease of use - some *appear* repeated, but are different forms.

STRACHEY goes on to develop outputs using these initial tunings by a series of modifications and manipulations, which are now described.

# Weight Modifications in STRACHEY

Channel B is the secondary STRACHEY output. It operates at the same resolution as channel B but (for reasons which are explained below), the pitch range of channel B is lower than that of channel A. 

The outputs on channel B occur at the onsets of a Euclidean pattern, generated by STRACHEY. This pattern has length determined by the Turing Machine's LENGTH parameter and density determined by STRACHEY's DENSITY controls. LENGTH and DENSITY are both controllable by front panel potentiometers - "DENSITY" is the third of STRACHEY's main potentiometers. Both Length and Density and can further be controlled by CV inputs. 

This makes the onsets of the output from channel B: 

* a subset of the beats of the main system clock,
* a pattern which has rhythmic interest and
* a pattern which can be made to change (by modulating the Density CV input)

The same gate sequence (generated by the Turing Machine) and the same initial weight vector (selected by the TUNING controls) produce the channel A and B outputs, so the *set of allowed pitches* are the same (as described at tedious length in the [Tuning Strategy](https://github.com/m0xpd/TuningStrategyForVoltages)). However, STRACHEY can apply two modifications to the weight vector used in forming the output from channel A. 

Firstly, the initial weight vector can be permuted (i.e. changed in order) before channel A's output is formed, during operation, giving STRACHEY an entirely new dimension of variability relative to other Klee sequencers, including the Turing Machine. 

Secondly, the initial weight vector can be subject to octave span extensions (under control of the SPAN controls - both potentiometer and CV input), which extend the pitch range of the channel A output. 

Neither the permutations or the octave extensions of channel A's weight vector are applied to channel B.

So - channel B has a generally reduced pitch span compared to channel A (as there is no octave extension added via SPAN) and there is no variation introduced by permutation. It also has less dense onsets; it '*samples*' notes from the set of pitches within the fundamental range of channel A's pitch distribution on a rhythmic sub-pattern of variable DENSITY. Channel B is particularly useful for forming bass or melody against a fuller, arpeggiated 'continuo' from channel A.

# Permuting the Weights of a Step Sequencer

The idea of introducing permutation between the gates and weights of a Random Looping Sequencer is (as far as I'm aware) novel. 

The practice of stopping and single-stepping a sequencer is, of course, familiar and I have [demonstrated some other effects](https://www.youtube.com/watch?v=kFBzPTS7XLM) obtained with multi-rate or asynchronous scanning of a Klee sequencer. But synchronous permutation of the mapping between gates and weights is less familiar. One notable exception is the idea of reversing the scan direction of a sequencer, (which can be expressed as a simple permutation) and is seen on both 'DIY' sequencers from [MFOS](https://musicfromouterspace.com/analogsynth_new/SEQ16_2006/SEQ16_2006.php) and commercial units from e.g. [Doepfer](https://doepfer.de/a154.htm). 

STRACHEY can - of course - reverse its scan direction, either by flipping the current permutation (Method# 13)  or by resetting to a 'reversed' version of the starting weight vector (Method# 12).

There are other synchronous permutations worth exploring.

Back in 2017 I made a gate sequencer 

<p width=100%, align="center">
<img width=20%, src="https://github.com/m0xpd/STRACHEY/blob/main/Hardware/Graphics/Camp%20front%20perspective%20LoRes.jpg">
</p>

which was inspired by patterns used in [Change Ringing](https://en.wikipedia.org/wiki/Change_ringing), a perversely English way of sounding the bells of a Church. These patterns are called "Methods". The key ingredient of Change Ringing is an exploration of the permutations by which a number of bells may be sounded in sequence. In the case of my module, I implemented four of the traditional "Methods"  ([Rounds](https://jaharrison.me.uk/Ringing/Glossary/R.html#rounds), [Plain Hunt](https://en.wikipedia.org/wiki/Plain_hunt), [Grandsire](https://en.wikipedia.org/wiki/Grandsire) and [Plain Bob](https://www.ringing.info/plp/pb8/index.html)) to trigger any number of gates (any "[Stage](https://jaharrison.me.uk/Ringing/Glossary/S.html#stage)") between 4 and 8. Although the sequencer was made as a percussion trigger source rather than in attempt to simulate the sound of church bells, I added - for the purposes of demonstration - two 1V/octave pitch CV outputs, one set to be typical of the diatonic tuning of a ring of bells and one set (for comedic purposes!) to a minor pentatonic scale. 

I was, therefore, entirely familiar with the idea of using permutations in general (and permutations from bell ringing in particular) in a step sequencer. The only further inventive step for me in the development of STRACHEY was the extension of these ideas to a Klee-type sequencer. 

That step involved the introduction of a [permutation matrix](https://en.wikipedia.org/wiki/Permutation_matrix) between the gates and the weights in the scalar product which forms the sequencer output - for both a conventional sequencer and a Klee sequencer. (The actual coding doesn't require matrix methods - it is achieved in [the code](https://github.com/m0xpd/STRACHEY/blob/main/Controller/Code/STRACHEY_Sequencer_1v0.ino) just by indexing within the scalar product. The matrix is just a conceptual and mathematical convenience.)

STRACHEY uses a fixed number of weights ("Stage") to form the pitch output from the gate vector: the eight inherited from the 8 sliders on MTM's Voltages expander. If these 8 weights are seen in analogy with 8 bells (which is the standard stage in a larger bell tower for change ringing), some of STRACHEY's methods for permuting the weights can be related to bell ringing.

STRACHEY currently implements two standard bell ringing methods; "[rounds](https://jaharrison.me.uk/Ringing/Glossary/R.html#rounds)" (which is the bell-ringing term when the permuatation matrix is fixed at the identity matrix)  and "Plain Hunt Major" ('Plain Hunt' is - as we've seen - a [standard algorithm](https://en.wikipedia.org/wiki/Plain_hunt) for changing the permutation matrix and 'Major' is [bell-ringing jargon](https://jaharrison.me.uk/Ringing/Glossary/M.html#major) indicating that the algorithm is applied on a stage of 8 weights) . 

In both cases, STRACHEY will implement [plain courses](https://jaharrison.me.uk/Ringing/Glossary/P.html#plaincourse) of these methods (just as my gate sequencer did back in 2017). However, in STRACHEY there is possibility to introduce variation, described below, similar to a bell-ringing ['single' change](https://jaharrison.me.uk/Ringing/Glossary/S.html#singlechange), by which the hunt may be changed, to extend the sequence to a longer pattern. By this means, STRACHEY can be set in rounds (Method# 0) or plain hunt (Method# 6), using the METHOD controls (potentiometer or CV), and set to run on course, with occasional calls to a random 'single' by changing the METHOD to the random single change call (Method# 5 - all the METHODs are tabulated below).  

STRACHEY can introduce variation by other means.

STRACHEY can *sort* the weights in pitch order, either descending or ascending. It can do this in two ways - either in an immediate sort or as one step of a [bubble sort](https://en.wikipedia.org/wiki/Bubble_sort) (such that a number of successive number of calls to this process are required to achieve the final sort). Each change is made at the start of the cycle (of length determined by the Turing Machine's LENGTH parameter), if requested by an 'Change' input during the previous cycle. 

STRACHEY can also reset the permutation matrix (to the identity matrix - playing 'rounds' in bell-ringing parlance), can fully randomise the permutation matrix or can introduce one random swap in the permutation matrix associated with swapping position of a random weight with one of its neighbours. (This last method is the analogy with the underlying technique in [Call-changing](https://en.wikipedia.org/wiki/Call_changes) - the 'single' described above,  but is - in this case - randomised rather than designed.)

A table of all the (currently implemented) METHODS is presented below, along with the boundaries for the voltages which should be applied at the Method CV input if it is desired to select the METHOD using this means. 

|  Method #   |  Description   |  Vlow   |  Vhigh  |
|------|----|----|----|
|  0  | Reset |  0  |  0.3125  |
|  1  | SortAscending |  0.31  |  0.63  |
|  2  | SortDescending |  0.63  |  0.94 |
|  3  | SingleSortUp |  0.94  |  1.25  |
|  4  | SingleSortDown |  1.25  |  1.56  |
|  5  | RandomSingle |  1.56  |  1.88  |
|  6  | PlainHunt |  1.88  |  2.19  |
|  7  | *Not Implemented*  |  2.19  |  2.5  |
|  8  | RotateR |  2.5  |  2.81  |
|  9  | RotateL |  2.81  |  3.13  |
|  10  | *Not Implemented* |  3.13  |  3.44  |
|  11  | *Not Implemented* |  3.44  |  3.75  |
|  12  | Reverse |  3.75  |  4.06  |
|  13  | Flip |  4.06  |  4.38  |
|  14  | *Not Implemented* |  4.38  |  4.69  |
|  15  | Reset |  4.69  |  5  |

Note that the **Method #** is displayed (in binary) on the four red LEDs above the METHOD control. 

The METHOD display will flash after a CHANGE call is made (either by pressing the CHANGE button or pulling down the Change CV input) until the selected subroutine call is completed at the start of the next cycle. For continuous methods such as running Plain Hunt (Method # 6) or continuously flipping the order on successive passes (Method # 13) it is appropriate to keep Change continually asserted (e.g. by tying the Change CV low). The Method LEDs will then flash continually, pausing only on the first beat of each cycle when START=1.      

# Calibration and Configuration

STRACHEY has one aspect requiring **calibration** before it will operate correctly; trimmers TR1 and TR2 must be adjusted to ensure that outputs A and B (respectively) are correctly tuned in V/octave terms. The MC4922 DAC is operated over a 0:5V output range, but the DAC's output is further passed through non-inverting amplifier stages (IC4D for channel A and IC4 C for channel B) with gain of 2. The code expects the full-scale 5V output from the DAC to be broken down into 2^12 steps and uses 51 steps per semitone. 

Accordingly, I have calculated that *in an ideal system* the trimmers should be set to a ratio of 0.669 (i.e. a 1k trimmer should have the lower leg of the potential divider set to 669 Ohms). In reality, where all the components have tolerances and there are some offsets etc., this ratio will not be quite correct - hence the decision to use trimmers rather than fixed resistors. I just measured my own trimmers (which have - so far - been set only 'by ear') and found that TR1 is set at a ratio of 0.696 and TR2 is at a ratio of 0.689. Start off at 0.7 and you'll be close!

There is one feature of STRACHEY that requires **configuration**. There is provided on the main board an Turing Machine expansion port in the standard  Music Thing Modular format. It can be used *either* as a GATES expander (by bridging pins 1 and 2 of JP3, which connects the 'EXP_SEL' (Expander Select) line to 5V) or as a PULSES expander (by bridging pins 2 and 3 of JP3, which connects the 'EXP_SEL' (Expander Select) line to the main clock). The GATES expander port is used with [VOLTS](https://www.musicthing.co.uk/Turing-Volts-Expander/) and [VOLTAGES](https://www.musicthing.co.uk/Turing-Voltages-Expander/) and the PULSES expander port is used with [PULSES](https://www.musicthing.co.uk/Turing-Pulse-Expander/). The red stripe on the expander ribbon cable goes towards the bottom edge of STRACHEY's Main board (I forgot to put a marker on the silkscreen). 

# Specifications

**Width:** 

STRACHEY is **18HP wide**.

**Depth:**

STRACHEY extends **43 mm** behind the [front panel](https://github.com/m0xpd/STRACHEY/blob/main/Hardware/Panel/README.md) when a conventional Eurorack power header **with strain relief** is inserted (this is the same depth as the [original Turing Machine](https://www.musicthing.co.uk/Turing-Machine/)).

If your power header doesn't have a strain relief (which is probably more typical, judging by the power cables delivered with commercial modules) the depth is limited by the Arduino's USB receptacle; in this situation STRACHEY extends **42mm** behind the [front panel](https://github.com/m0xpd/STRACHEY/blob/main/Hardware/Panel/README.md).

**Power Consumption:**

| Power Rail | Current |
|---|---|
| +12V | **48mA** |
| -12V | **10mA** |
| 5V | **0** |


(peak currents, measured with nothing connected to STRACHEY's expansion port).

**Miscellaneous:**

All inputs are protected against over/under voltage.

Most of the CV inputs are intended to operate over a 0:5V control range. However, the Density and Method CV inputs are applied to attenuverters; these inputs will respond to signals spanning the entire bipolar Eurorack voltage range (+/- 12V). 

It is my habit to set up my attenuverter controls such that full counterclockwise rotation gives unity gain and full clockwise rotation gives gain of -1. This is **opposite to common practice**.

The external Clock input is triggered by signals exceeding an **(upward) threshold of 1.25V**.

The Change CV input is ACTIVE LOW - it must be pulled low to call one of the CHANGE METHODs and held high to retain the status quo. This input similarly responds to signals exceeding an (upward) threshold of 1.25V but, given the ACTIVE LOW nature of this control, the **downward threshold of 1.05V** is more important.

The Write input is usually held at mid-voltage (2.5V) by an internal resistor network. When an input is applied to the Write CV jack, this 2.5V is disconnected, so any external device should provide a voltage close to 2.5V. Pulling this voltage **below 0.49 V will write a '0'** and **above 4.39 V will write a '1'**.


