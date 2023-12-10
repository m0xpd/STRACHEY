//
// Control Code for the STRACHEY Sequencer
//
// A Random Looping Sequencer, 
// named for Christopher Strachey
// https://en.wikipedia.org/wiki/Christopher_Strachey
//
// details at https://github.com/m0xpd/STRACHEY
//
//
// The STRACHEY sequencer implements the Tuning Strategy for  Klee-type Sequencers:
// https://github.com/m0xpd/TuningStrategyForVoltages
// and includes a new software implementation of the Turing Machine, an 
// open-source (CC BY-SA) design from Music Thing Modular. 
//
// STRACHEY incorporates Euclidean Rhythm generation, which was derived from:
// http://clsound.com/euclideansequenc.html
// itself derived from Tom Whitwell's code, available at:
// https://www.modwiggler.com/forum/viewtopic.php?p=607737#p607737
//
// version 1v0
//
// Paul Darlington
// m0xpd
// 10 December 2023
//
// This code published under Creative Commons CC BY-SA 4.0 License
// -----------------------------------------------------------------
// for Arduino NANO

int seqLength = 8;
int seqStep = 0;
byte upper_byte = 0x10;
byte lower_byte = 0;
const int StepsPerSemitone = 51;          
uint16_t euclidPattern;

//---------------------------------------------------------------------------------------------------|----------------------|
// Here are the tunings             Description                                                      |.. Tuning Strategy #..|
int weights[24][8] = {
  //                                                                                                 |                      |
  //                            Bank A - Basic Tunings                                               |                      |
  //                                                                                                 |                      |
  {0, 0, 7, 0, 0, 0, 0, 0},    // 0  Root and Fifth                                                  |         (3)          |
  {0, 0, 3, 0, 2, 0, 5, 0},    // 1  AEOLIAN - "Natural Minor"                                       |         14           |
  {0, 0, 7, 0, 3, 0, 0, 0},    // 2  Minor 7th                                                       |          5           |
  {0, 0, 7, 4, 0, 0, 0, 0},    // 3  Major 7th                                                       |          6           |
  {0, 0, 6, 0, 3, 0, 0, 0},    // 4  Dim 7                                                           |          8           | 
  {0, 0, 8, 0, 4, 0, 0, 0},    // 5  Augmented                                                       |          7           |
  {0, 0, 10, 7, 0, 0, 0, 0},   // 6  "Sus 7th" feel                                                  |         10           |
  {0, 0, 10, 0, 0, 4, 0, 0},   // 7  "9th Feel"                                                      |          0           |
  //-------------------------------------------------------------------------------------------------|--------------------- | 
  //                            Bank B - Modes etc                                                   |                      |
  //                                                                                                 |                      |
  {0, 0, 7, 0, 0, 0, 0, 0},    // 8  Root and Fifth                                                  |         (3)          |
  {0, 0, 3, 0, 2, 0, 5, 0},    // 9  AEOLIAN - "Natural Minor"                                       |         14           |
  {0, 0, 2, 0, 7, 0, 3, 0},    // 10 DORIAN                                                          |         11           |
  {0, 0, 7, 10, 5, 0, 2, 0},   // 11 PHRYGIAN                                                        |         13           |
  {0, 0, 2, 2, 0, 7, 5, 0},    // 12 IONIAN - Major (may alias as DORIAN through pdf)                |         18           |
  {0, 0, 2, 5, 7, 0, 7, 0},    // 13 Hexatonic Scale, close to Major but with no 7th degree          |         22           |
  {0, 0, 2, 5, 0, 4, 0, 0},    // 14 Octatonic Scale - Major Scale with added flat 5                 |         20           |
  {0, 0, 10, 7, 0, 2, 0, 0},   // 15 Hexatonic Scale with no third                                   |         23           |
  //-------------------------------------------------------------------------------------------------|----------------------|
  //                            Band C - Symmetric Scales etc                                        |                      |
  //                                                                                                 |                      |
  {0, 0, 12, 0, 0, 0, 0, 0},   // 16 Root and Octave                                                 |         (3)          |
  {0, 0, 6, 0, 6, 0, 0, 0},    // 17 Tritone                                                         |        (15)          |
  {0, 0, 8, 0, 4, 0, 0, 0},    // 18 Augmented                                                       |          7           |
  {0, 0, 6, 0, 3, 0, 0, 0},    // 19 diminished                                                      |          8           |
  {0, 0, 2, 0, 6, 0, 4, 0},    // 20 Whole-tone                                                      |         16           |
  {0, 0, 2, 1, 6, 0, 4, 0},    // 21 Chromatic Scale                                                 |         17           |
  {0, 0, 2, 5, 7, 7, 7, 0},    // 22 Major Scale (may alias as Dorian)                               |         19           |       
  {12, 11, 9, 7, 5, 4, 2, 0}   // 23 Descending Major Scale                                          |        N/A           |
};
//--------------------------------------------------------------------------------------------------------------------------|

int wA[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int wB[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int gates[16] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int gatecarry = 0;
int gateDisplay = 0;
int semitoneA = 0;
int semitoneB = 0;
int Offset = 0;
int Density = 0;
int oldDensity = 0;
int Turing = 0;   // Main Turing Control Knob Value
int TuringCurve = 0; // non-linear operation on the Turing Input
int Tune = 0;     // Slider Tuning
int oldTune = 0;  // Previous Slider Tuning
int Write = 0;    // Write Switch value
int Span = 0;     // Octave Span value;
int oldSpan = 0;  // old value of Span;
int oldseqLength = 0;
int TuneDisplay = 0;
int TuneDisplay2 = 0;
int lowTune = 0;
int highTune = 0;
int highTuneDisplay = 0;
int stroke = 1;

// Arduino pin allocations...
const int CLK_IN = 2;
const int  DAC_SDI = 4;         // MCP4922...
const int  DAC_SCK = 5;
const int  DAC_CS = 6;
const int  DAC_LDAC = 7;
const int latchPin2 = 8;        //Pin connected to SH_CP of second 74HC595 (pin 12)
const int latchPin = 9;         //Pin connected to SH_CP of 74HC595 (pin 12)
const int gateBPin = 11;
const int modePin = 12;          // INPUT for CHANGE call inputs
const int gateAPin = 13;

const int LengthKnob = 1;        // ANALOG INPUT for LENGTH Control
const int TuringKnob = 2;        // ANALOG INPUT for main TURING Machine Control
const int TuneKnob = 3;          // ANALOG INPUT for Weights TUNING Selection
const int WriteSwitch = 4;       // ANALOG INPUT for Write Switch Input
const int SpanKnob = 5;          // ANALOG INPUT for Octave SPAN input
const int DensityKnob = 6;       // ANALOG INPUT for Euclidean DENSITY input
const int ModeKnob = 7;          // ANALOG INPUT for weight change 'METHOD' inputs


bool modeIn = true;              // input from modePin
bool ChangeFlag = false;         // Flag for Change call
int mode = 0;


int CycleNo = 0;                // Pointer within the CycleSequence

// This is the vector which gets permuted on CHANGE calls, according to selected METHODs:
int gateIndex[8] = {0, 1, 2, 3, 4, 5, 6, 7};  

void setup() {
  setupHardware();
  randomSeed(millis());
  gateDisplay = 0;
  digitalWrite(latchPin, LOW);
  shiftOut(DAC_SDI, DAC_SCK, MSBFIRST, gateDisplay);
  digitalWrite(latchPin, HIGH);
  write_Tune_Display();
  seqLength = 2 + (analogRead(LengthKnob) / 72);
  if (seqLength < 2) {
    seqLength = 2;
  }
  oldseqLength = seqLength;
  Density = floor((1024 - analogRead(DensityKnob)) * seqLength / 1024);
  euclidPattern = euclid(seqLength, seqLength - Density, 0);
}

void loop() {

  while (digitalRead(CLK_IN) == 0) {
    Turing = analogRead(TuringKnob);      // Read controls during clock low phase...
    Tune = (analogRead(TuneKnob)) / 41.5;
    Span = analogRead(SpanKnob) / 256;
    mode = analogRead(ModeKnob) / 63.5;
    modeIn = digitalRead(modePin);
    if (modeIn == 0) {                    // and check for change calls
      ChangeFlag = true;
    }
  }
                                 // Now we're at clock 'High" phase
  if (CycleNo == 0) {            // if it's the start of the pattern cycle, set the 'START' indication
    bitSet(TuneDisplay2, 7);
  }
  else {                          // otherwise, clear it
    bitClear(TuneDisplay2, 7);
  }

  modeIn = digitalRead(modePin);  // check for a CHANGE call
  if (modeIn == 0) {
    ChangeFlag = true;
  }

  write_Gate_Display();           // write the Gates
  write_Tune_Display();           // and other LEDs
                                  // and calculate the Turing update curve (a non-inear fn of the TURING control setting)...
  TuringCurve = floor(512.0 * (1.0 - cos((1.0 * Turing) * 3.1412 / 1024.0)));

  int newseqLength = 2 + (analogRead(LengthKnob) / 72);                 // Read LENGTH and
  Density = floor((1024 - analogRead(DensityKnob)) * seqLength / 1024); // DENSITY inputs and
  if (newseqLength != seqLength) {                                      // (if required)
    if (newseqLength < 2) {                                             // update...
      newseqLength = 2;
    }
    seqLength = newseqLength;
  }
  if (Density != oldDensity) {                                          // if Density has changed,
    oldDensity = Density;                                               // record the change
    euclidPattern = euclid(seqLength, seqLength - Density, 0);          // and re-calculate the Euclid pattern
  }

  if (Tune != oldTune) {                                                // if a new TUNING has been selected
    write_Tune_Display();                                               // update the display
    for (int i = 0; i < 8; i++) {                                       // and the weights
      wA[i] = weights[Tune][i];
      wB[i] = weights[Tune][i];
    }
    wB[0] = 0;
    wB[1] = 0;
    wB[7] = 0;
    oldTune = Tune;                                                     // and remember the change
 
  }
  if (Span != oldSpan) {                                                // if there has been a change on the SPAN input
    switch (Span) {                                                     // see what the new value is 
      case 0:                                                           // and change the (channel A) weight vector accordingly...
        wA[0] = 0;
        wA[1] = 0;
        wA[7] = 0;
        break;
      case 1:
        wA[0] = 12;
        wA[1] = 0;
        wA[7] = 0;
        break;
      case 2:
        wA[0] = 12;
        wA[1] = 12;
        wA[7] = 0;
        break;
      case 3:
        wA[0] = 12;
        wA[1] = 12;
        wA[7] = 12;
        break;
    }
    oldSpan = Span;                                                       // and remember the change
  }
  if (seqLength != oldseqLength) {                                        // if there's a change on the LENGTH input
    oldseqLength = seqLength;
    euclidPattern = euclid(seqLength, seqLength - Density, 0);            // re-calculate the Euclidean pattern for the new sequence Length
  }

  semitoneA = 0;                                      // clear the semitones, ready for the new values
  semitoneB = 0;
  int j = 0;
  for (int i = 0; i < 8; i++) {                       // and form the new scalar products
    j = gateIndex[i];                                 // of gates and weights
    semitoneA = semitoneA + gates[j] * wA[i];         // for channel A (INCLUDING THE PERMUTATION)
    semitoneB = semitoneB + gates[i] * wB[i];         // and channel B
  }
  
  Set_DAC_A(semitoneA * StepsPerSemitone);            // play the channel A output - set the DAC
  
  bool Bplay = bitRead(euclidPattern, CycleNo);       // Is there an onset in the Euclidean pattern at this point (Bplay=true)?
  if (Bplay) {                                        // do we have to play channel B on this step?
    Set_DAC_B(semitoneB * StepsPerSemitone);          // if yes, set the DAC channel
    digitalWrite(gateBPin, HIGH);
  }
  digitalWrite(gateAPin, HIGH);
  while (digitalRead(CLK_IN) == 1) {                  // wait until the end of the clock HIGH phase, reading the WRITE switch
    Write = analogRead(WriteSwitch);
  }
  modeIn = digitalRead(modePin);                      // then take one more last-ditch read of the CHANGE input
  if (modeIn == 0) {
    ChangeFlag = true;
  }

  digitalWrite(gateAPin, LOW);
  digitalWrite(gateBPin, LOW);
  // =============================================================================
  // This is the MAIN PART of the SOFTWARE IMPLEMENTATION OF THE TURING MACHINE...
  // ============================================================================= 
  // first, bump the gate vector...
  gatecarry = gates[seqLength - 1];
  for (int i = 15; i > 0; i = i - 1) {
    gates[i] = gates[i - 1];
  }
  // then set gate[0], and get two random variables ready...
  byte randgate = random(0, 2); // a random boolean (0 or 1)
  int decide = random(1, 511);  // and a random integer (1:510)
  // check the value read from the write switch...
  if (Write > 900) {    // here Write was HIGH, so we are writing ones into gate 0
    gates[0] = 1;
  }
  else if (Write < 100) { // here Write was low, so we are writing zeros into gate 0
    gates[0] = 0;
  }
  else {                // here the Write swich was inactive, and the update proceeds according to the setting of the TURING control
    if (Turing >= 512) { // Here, we're in the right-hand side of the TURING control
      if (decide < 1024 - TuringCurve) { // compare the random variable 'decide' with 1024-Turing Curve ; if it's smaller 
        gates[0] = randgate;             // randomise gate 0
      }
      else {                             // otherwise,
        gates[0] = (gatecarry);          // feedback the bit from the selected point in the shift register into gate 0
      }
    }
    else {              // Here, we're in the left-hand side of the TURING control
      if (decide < TuringCurve) {    // compare the random variable 'decide' with Turing Curve ; if it's smaller 
        gates[0] = randgate;         // randomise gate 0
      }
      else {                         // otherwise,
        gates[0] = not(gatecarry);   // feedback the complement of the bit from the selected point in the shift register into gate 0
      }
    }
  }

  CycleNo = CycleNo + 1;          // maintain a count of the Cycle 
  if (CycleNo >= seqLength) {     // in mod LENGTH
    CycleNo = 0;                  // and if we're at 0...
    if (ChangeFlag == true) {     // work the CHANGE, if any is called...
      switch (mode) {
        case 0:
          gateIndexReset();
          ChangeFlag = false;
          break;
        case 1:
          gateIndexHighSort();
          ChangeFlag = false;
          break;
        case 2:
          gateIndexLowSort();
          ChangeFlag = false;
          break;         
        case 3:
          gateAscendingSingleSort();
          ChangeFlag = false;
          break;
        case 4:
         gateDescendingSingleSort();
          ChangeFlag = false;
          break;          
        case 5:
          gateRandomSingle();
          ChangeFlag = false;
          break;          
        case 6:
          PlainHunt();
          ChangeFlag = false;
          break;
        case 8:
          gateIndexRoR();
          ChangeFlag = false;
          break;
        case 9:
          gateIndexRoL();
          ChangeFlag = false;
          break;          
        case 12:
          gateIndexReverse();
          ChangeFlag = false;
          break;             
        case 13:
          gateIndexFlip();
          ChangeFlag = false;
          break;                             
        case 15:
          gateIndexShuffle();
          ChangeFlag = false;
          break;

        default:
          // catch all the other (up-populated) cases
          ChangeFlag = false;
          break;
      }
    }

  }
  if (ChangeFlag == true) {
    // flash the Method LEDs if a CHANGE has been called...
    write_Tune_Display_ModeOFF();
  }
  // end of loop
  // ----------------------------------------------------------------------------------------------------------
}


// just subroutines below here...

void write_Gate_Display() {
  // Display Gates on LEDs via a 74HC595 shift 
  gateDisplay = 0;
  for (int i = 0; i < 8; i++) {
    gateDisplay = gateDisplay + (gates[i] << i);
  }
  digitalWrite(latchPin, LOW);
  shiftOut(DAC_SDI, DAC_SCK, MSBFIRST, gateDisplay);
  digitalWrite(latchPin, HIGH);
}

void write_Tune_Display(){
  // Display TUNING and other status info on LEDs
  // via 2 74HC595 shifts 
  lowTune = Tune % 8;
  highTune = Tune / 8;
  highTuneDisplay = 0;

  switch (highTune) {
    case 0:
      highTuneDisplay = 0x1;
      break;
    case 1:
      highTuneDisplay = 0x2;
      break;
    case 2:
      highTuneDisplay = 0x4;
      break;
  }
  TuneDisplay = 1 << lowTune;

  int wTuneDisplay2 = TuneDisplay2 | mode << 3;
  wTuneDisplay2 = wTuneDisplay2 | highTuneDisplay;
  digitalWrite(latchPin2, LOW);
  shiftOut(DAC_SDI, DAC_SCK, MSBFIRST, wTuneDisplay2);
  shiftOut(DAC_SDI, DAC_SCK, MSBFIRST, TuneDisplay);
  digitalWrite(latchPin2, HIGH);
}

void write_Tune_Display_ModeOFF()
{
  // Turn off the mode/method LEDs to implement a FLASH...
  TuneDisplay = 1 << lowTune;
  int wTuneDisplay2 = TuneDisplay2 | (0) << 3;
  wTuneDisplay2 = wTuneDisplay2 | highTuneDisplay;
  digitalWrite(latchPin2, LOW);
  shiftOut(DAC_SDI, DAC_SCK, MSBFIRST, wTuneDisplay2);
  shiftOut(DAC_SDI, DAC_SCK, MSBFIRST, TuneDisplay);
  digitalWrite(latchPin2, HIGH);
}


void Set_DAC_A(int Input_Value) {
  // subroutine to set DAC channel A
  lower_byte = Input_Value & 0xff;
  upper_byte = (Input_Value >> 8) & 0x0f;
  bitSet(upper_byte, 4);
  bitSet(upper_byte, 5);
  digitalWrite(DAC_CS, LOW);
  shiftOut(DAC_SDI, DAC_SCK, MSBFIRST, (upper_byte));
  shiftOut(DAC_SDI, DAC_SCK, MSBFIRST, (lower_byte));
  digitalWrite(DAC_SDI, LOW);
  digitalWrite(DAC_CS, HIGH);
  digitalWrite(DAC_LDAC, LOW);
  digitalWrite(DAC_LDAC, HIGH);
}

void Set_DAC_B(int Input_Value) {
  // subroutine to set DAC channel B
  lower_byte = Input_Value & 0xff;
  upper_byte = (Input_Value >> 8) & 0x0f;
  bitSet(upper_byte, 4);
  bitSet(upper_byte, 5);
  bitSet(upper_byte, 7);
  digitalWrite(DAC_CS, LOW);
  shiftOut(DAC_SDI, DAC_SCK, MSBFIRST, (upper_byte));
  shiftOut(DAC_SDI, DAC_SCK, MSBFIRST, (lower_byte));
  digitalWrite(DAC_SDI, LOW);
  digitalWrite(DAC_CS, HIGH);
  digitalWrite(DAC_LDAC, LOW);
  digitalWrite(DAC_LDAC, HIGH);
}


void gateIndexShuffle() {
  // Shuffle gateIndex vector
  for (int i = 0; i < 8; i++) {
    int n = random(0, 8);
    int temp = gateIndex[n];
    gateIndex[n] =  gateIndex[i];
    gateIndex[i] = temp;
  }
// end of gateIndexShuffle()
}

void gateIndexReset() {
  // Reset gateIndex vector
  gateIndex[0] = 0;
  gateIndex[1] = 1;
  gateIndex[2] = 2;
  gateIndex[3] = 3;
  gateIndex[4] = 4;
  gateIndex[5] = 5;
  gateIndex[6] = 6;
  gateIndex[7] = 7;
// end of gateIndexReset()
}

void gateIndexReverse() {
  // Reverse gateIndex vector to run sequencer 'backwards'
  gateIndex[0] = 7;
  gateIndex[1] = 6;
  gateIndex[2] = 5;
  gateIndex[3] = 4;
  gateIndex[4] = 3;
  gateIndex[5] = 2;
  gateIndex[6] = 1;
  gateIndex[7] = 0;
// end of gateIndexReverse()
}

void gateIndexFlip() {
  // Flip order of gateIndex vector (a double transpose)
  int temp = 0;
  for(int i=0; i<4; i++){
    temp=gateIndex[i];
    gateIndex[i]=gateIndex[7-i];
    gateIndex[7-i]=temp;
  } 
// end of gateIndexFlip()
}


void gateIndexRoR() {
  // Rotate Right gateIndex vector
  int temp = gateIndex[7];
  for(int i=0; i<7; i++){
    gateIndex[7-i]=gateIndex[6-i];
  } 
  gateIndex[0]=temp;
// end of gateIndexRoR()
}

void gateIndexRoL() {
  // Rotate Left gateIndex vector
  int temp = gateIndex[0];
  for(int i=0; i<7; i++){
    gateIndex[i]=gateIndex[i+1];
  } 
  gateIndex[7]=temp;
// end of gateIndexRoL()
}

void gateAscendingSingleSort(){
  // single pass of Ascending Bubble sort
  for (int i = 0; i<7; i++){   
  if(wA[gateIndex[i]]<wA[gateIndex[i+1]]){
  int temp = gateIndex[i];
  gateIndex[i] = gateIndex[i+1];
  gateIndex[i+1] = temp;
  break;
  }
  }
}

void gateDescendingSingleSort(){
  // single pass of Descending Bubble sort
  for (int i = 0; i<7; i++){   
  if(wA[gateIndex[i]]>wA[gateIndex[i+1]]){
  int temp = gateIndex[i];
  gateIndex[i] = gateIndex[i+1];
  gateIndex[i+1] = temp;
  break;
  }
  }
}

void gateRandomSingle(){
  // generate a random single gateIndex pair change
  int i=random(1,8);
  int temp = gateIndex[i];
  gateIndex[i] = gateIndex[i+1];
  gateIndex[i+1] = temp;
  
}

void gateIndexHighSort() {
  // bubble sort the weights into increasing order of pitch
  // and sort the gate index to play a rising pitch sequence
  // on a delta function (single gate) sequence
  int wAsort[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  int indexMax = 0;
  int changes[7] = {0, 0, 0, 0, 0, 0, 0};
  int changeSum = 0;
  int gateIndexChange[8] = {0, 1, 2, 3, 4, 5, 6, 7};
  int newgateIndex[8] = {0, 0, 0, 0, 0, 0, 0, 0};

  // first pass...
  for (int i = 0; i < 8; i++) { //copy the active weight vector into the sort vector
    wAsort[i] = wA[i];
  }
  for (int i = 0; i < 7; i++) {
    if (wAsort[i] < wAsort[i + 1]) {
      int temp = wAsort[i];
      int temp2 = gateIndexChange[i];
      wAsort[i] = wAsort[i + 1];
      gateIndexChange[i] = gateIndexChange[i + 1];
      wAsort[i + 1] = temp;
      gateIndexChange[i + 1] = temp2;
      changes[i] = 1;
    }
    changeSum = 0;
    for ( int i = 0; i < 7; i++) {
      changeSum += changes[i];
    }
  }
  // second pass

  while (changeSum > 0) {
    for (int i = 0; i < 7; i++) {
      changes[i] = 0;
      if (wAsort[i] < wAsort[i + 1]) {
        int temp = wAsort[i];
        int temp2 = gateIndexChange[i];
        wAsort[i] = wAsort[i + 1];
        gateIndexChange[i] = gateIndexChange[i + 1];
        wAsort[i + 1] = temp;
        gateIndexChange[i + 1] = temp2;
        changes[i] = 1;
      }
    }
    changeSum = 0;
    for ( int i = 0; i < 7; i++) {
      changeSum += changes[i];
    }
  }
  for (int i = 0; i < 8; i++) {
    int temp3 = gateIndexChange[i];  
    newgateIndex[temp3] = i;
  }
  for (int i = 0; i < 8; i++) {
    gateIndex[i] = newgateIndex[i];
  }
  // end of gateIndexHighSort
}




void gateIndexLowSort() {
  // bubble sort the weights into increasing order of pitch
  // and sort the gate index to play a rising pitch sequence
  // on a delta function (single gate) sequence
  int wAsort[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  int indexMax = 0;
  int changes[7] = {0, 0, 0, 0, 0, 0, 0};
  int changeSum = 0;
  int gateIndexChange[8] = {0, 1, 2, 3, 4, 5, 6, 7};
  int newgateIndex[8] = {0, 0, 0, 0, 0, 0, 0, 0};

  // first pass...
  for (int i = 0; i < 8; i++) { //copy the active weight vector into the sort vector
    wAsort[i] = wA[i];
  }
  for (int i = 0; i < 7; i++) {
    if (wAsort[i] > wAsort[i + 1]) {
      int temp = wAsort[i];
      int temp2 = gateIndexChange[i];
      wAsort[i] = wAsort[i + 1];
      gateIndexChange[i] = gateIndexChange[i + 1];
      wAsort[i + 1] = temp;
      gateIndexChange[i + 1] = temp2;
      changes[i] = 1;
    }
    changeSum = 0;
    for ( int i = 0; i < 7; i++) {
      changeSum += changes[i];
    }
  }
  // second pass

  while (changeSum > 0) {
    for (int i = 0; i < 7; i++) {
      changes[i] = 0;
      if (wAsort[i] > wAsort[i + 1]) {
        int temp = wAsort[i];
        int temp2 = gateIndexChange[i];
        wAsort[i] = wAsort[i + 1];
        gateIndexChange[i] = gateIndexChange[i + 1];
        wAsort[i + 1] = temp;
        gateIndexChange[i + 1] = temp2;
        changes[i] = 1;
      }
    }
    changeSum = 0;
    for ( int i = 0; i < 7; i++) {
      changeSum += changes[i];
    }
  }
  for (int i = 0; i < 8; i++) {
    int temp3 = gateIndexChange[i];
    newgateIndex[temp3] = i;
  }
  for (int i = 0; i < 8; i++) {
    gateIndex[i] = newgateIndex[i];
  }
}


void PlainHunt(){
  // Implement 'Plain Hunt' on the gateIndex vector on sequential subroutine calls
  // https://en.wikipedia.org/wiki/Plain_hunt
  // The algorithm is slightly different 
  // if we're on Hand stroke (stroke = 1) 
  // or Back stroke (stroke = 0)
  if(stroke==1){
    for(int i = 0; i < 4; i++){
      int temp = gateIndex[2*i];
      gateIndex[2*i] = gateIndex[2*i+1];
      gateIndex[2*i+1] = temp;
    }
    stroke = 0;
  }
  else if(stroke==0){
     for(int i = 0; i < 3; i++){
      int temp = gateIndex[1+2*i];
      gateIndex[1+2*i] = gateIndex[2*i+2];
      gateIndex[2*i+2] = temp;
    }
    stroke = 1; 
  }
  // end of PlainHunt
}


void setupHardware() {
  // temporary 595 setup...
  pinMode(latchPin, OUTPUT);
  pinMode(latchPin2, OUTPUT);
  // end of temp 595 setup

  // DAC Setup...
  pinMode(DAC_CS, OUTPUT);
  pinMode(DAC_SCK, OUTPUT);
  pinMode(DAC_SDI, OUTPUT);
  pinMode(DAC_LDAC, OUTPUT);
  // Gates...
  pinMode(gateAPin, OUTPUT);
  pinMode(gateBPin, OUTPUT);
  pinMode(modePin, INPUT_PULLUP);
  pinMode(CLK_IN, INPUT);
  // Initialise outputs...
  digitalWrite(DAC_CS, HIGH);
  digitalWrite(DAC_LDAC, HIGH);
  digitalWrite(DAC_SCK, LOW);
  digitalWrite(DAC_SDI, HIGH);
  digitalWrite(gateAPin, LOW);
  digitalWrite(gateBPin, LOW);
}

// ================================================================================
// Euclid calculation function
// copied from: http://clsound.com/Resources/Euclidean%20Sequencer%20VERS%201.1.zip
// (which is derived from Tombola's (Tom Whitwell's) original source code,
// available here:
// https://www.modwiggler.com/forum/viewtopic.php?p=607737#p607737 )
// 

unsigned int euclid(int n, int k, int o) { // inputs: n=total, k=beats, o = offset
  int pauses = n - k;
  int pulses = k;
  int offset = o;
  int steps = n;
  int per_pulse = pauses / k;
  int remainder = pauses % pulses;
  unsigned int workbeat[n];
  unsigned int outbeat;
  uint16_t outbeat2;
  unsigned int working;
  int workbeat_count = n;
  int a;
  int b;
  int trim_count;

  for (a = 0; a < n; a++) { // Populate workbeat with unsorted pulses and pauses
    if (a < pulses) {
      workbeat[a] = 1;
    }
    else {
      workbeat[a] = 0;
    }
  }

  if (per_pulse > 0 && remainder < 2) { // Handle easy cases where there is no or only one remainer
    for (a = 0; a < pulses; a++) {
      for (b = workbeat_count - 1; b > workbeat_count - per_pulse - 1; b--) {
        workbeat[a] = ConcatBin(workbeat[a], workbeat[b]);
      }
      workbeat_count = workbeat_count - per_pulse;
    }

    outbeat = 0; // Concatenate workbeat into outbeat - according to workbeat_count
    for (a = 0; a < workbeat_count; a++) {
      outbeat = ConcatBin(outbeat, workbeat[a]);
    }

    if (offset > 0) {
      outbeat2 = rightRotate(offset, outbeat, steps); // Add offset to the step pattern
    }
    else {
      outbeat2 = outbeat;
    }

    return outbeat2;
  }

  else {
    if (pulses == 0) {
      pulses = 1;  //  Prevent crashes when k=0 and n goes from 0 to 1
    }
    int groupa = pulses;
    int groupb = pauses;
    int iteration = 0;
    if (groupb <= 1) {
    }

    while (groupb > 1) { //main recursive loop
      /*Serial.print("Pulses: ");   //  Help debug crash
        Serial.println(pulses);
        Serial.print("Pauses: ");
        Serial.println(pauses);
        Serial.print("Iterations: ");
        Serial.println(iteration);*/
      if (groupa > groupb) { // more Group A than Group B
        int a_remainder = groupa - groupb; // what will be left of groupa once groupB is interleaved
        trim_count = 0;
        for (a = 0; a < groupa - a_remainder; a++) { //count through the matching sets of A, ignoring remaindered
          workbeat[a] = ConcatBin(workbeat[a], workbeat[workbeat_count - 1 - a]);
          trim_count++;
        }
        workbeat_count = workbeat_count - trim_count;

        groupa = groupb;
        groupb = a_remainder;
      }

      else if (groupb > groupa) { // More Group B than Group A
        int b_remainder = groupb - groupa; // what will be left of group once group A is interleaved
        trim_count = 0;
        for (a = workbeat_count - 1; a >= groupa + b_remainder; a--) { //count from right back through the Bs
          workbeat[workbeat_count - a - 1] = ConcatBin(workbeat[workbeat_count - a - 1], workbeat[a]);

          trim_count++;
        }
        workbeat_count = workbeat_count - trim_count;
        groupb = b_remainder;
      }

      else if (groupa == groupb) { // groupa = groupb
        trim_count = 0;
        for (a = 0; a < groupa; a++) {
          workbeat[a] = ConcatBin(workbeat[a], workbeat[workbeat_count - 1 - a]);
          trim_count++;
        }
        workbeat_count = workbeat_count - trim_count;
        groupb = 0;
      }

      else {
        //Serial.println("ERROR");
      }
      iteration++;
    }

    outbeat = 0; // Concatenate workbeat into outbeat - according to workbeat_count
    for (a = 0; a < workbeat_count; a++) {
      outbeat = ConcatBin(outbeat, workbeat[a]);
    }

    if (offset > 0) {
      outbeat2 = rightRotate(offset, outbeat, steps); // Add offset to the step pattern
    }
    else {
      outbeat2 = outbeat;
    }

    return outbeat2;
  }
}

//------------------end euclidian math-------------------------

// Function to concatenate two binary numbers bitwise
unsigned int ConcatBin(unsigned int bina, unsigned int binb) {
  int binb_len = findlength(binb);
  unsigned int sum = (bina << binb_len);
  sum = sum | binb;
  return sum;
}

/*Function to right rotate n by d bits*/

uint16_t rightRotate(int shift, uint16_t value, uint8_t pattern_length) {
  uint16_t mask = ((1 << pattern_length) - 1);
  value &= mask;
  return ((value >> shift) | (value << (pattern_length - shift))) & mask;
}

// Function to find the binary length of a number by counting bitwise
int findlength(unsigned int bnry) {
  boolean lengthfound = false;
  int length = 1; // no number can have a length of zero - single 0 has a length of one, but no 1s for the sytem to count
  for (int q = 32; q >= 0; q--) {
    int r = bitRead(bnry, q);
    if (r == 1 && lengthfound == false) {
      length = q + 1;
      lengthfound = true;
    }
  }
  return length;
}
