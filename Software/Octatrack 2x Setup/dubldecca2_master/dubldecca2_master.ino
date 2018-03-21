/*
   Neutron magpie dodeca: 

Right Side Dodceca - DUBDECA layout

1) Velocity (synth voice) Midi Channel 4
2) Note out (synth voice) Midi Channel 4
3) Gate (synth voice) Midi Channel 4
4) 12) MIDI Clock out
5) Note to Gate/Trig - C Midi Channel 2
6) CC #72 MIDI Channel 2
7) Note to Gate/Trig - D Midi Channel 2
😎 CC #73 MIDI Channel 2
9) Note to Gate/Trig - E Midi Channel 2
10) CC #74 MIDI Channel 2
11) CC #75 MIDI Channel 2
12) CC #76 MIDI Channel 2

  
 * */

#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

const uint8_t CHANA = 2;//set the MIDI channel here!
const uint8_t CHANB = 4;

// output array is {vel, pitchled, trig, clock, trig, cc, trig, cc, trig, cc, cc, cc}
uint8_t out2pin[] = {23, 32, 22, 25, 20, 6, 21, 5, 9, 4, 10, 3};//output number to actual teensy pin, dont change.
// dig pins 4/6/8?  {x,  x,  0,  0,  0,  x,  0, x, 0, x,  x, x}

uint8_t whitekeys[] = {4, 0, 6, 0, 8, 0, 0, 0, 0, 0, 0, 0}; //non zero items are trigs sent to output number.

uint8_t pulses;
uint8_t sixteenthnotes; 
uint8_t quartertoggle;
uint8_t wholetoggle;
bool playing;
word pitchCV;
uint8_t pitchLED;
uint8_t RES;
uint16_t AMAX;
word V_scale;

byte CLOCK = 248; 
byte START = 250; 
byte CONTINUE = 251; 
byte STOP = 252; 

uint8_t cc2active[] = {72, 73, 74, 75, 76 };
uint8_t cc2out[] = {5, 7, 9, 10, 11};



void setup() {
  // Initiate MIDI communications, listen to all channels

  for (int i = 0; i < 12; i ++) {
    if (out2pin[i]) {
      pinMode(out2pin[i], OUTPUT);
      analogWriteFrequency(out2pin[i], 200000);
    }
  }

RES = 10;
//  RES = 7;
  analogWriteResolution(RES); // set resolution for DAC
  AMAX = pow(2,RES);
  V_scale = pow(2,(RES-7));
  
   //start up LED animation
   for (int i = 0; i < 12; i ++) {
    for (int j = 0; j < 256; j ++) {
	  analogWrite(out2pin[i], j );
//      if (out2pin[i] == 0) analogWrite(A14, (j ));
//      else analogWrite(out2pin[i], j );
      delay(1);
    }
    
    //if (out2pin[i] == 0) analogWrite(A14, 0);
    analogWrite(out2pin[i], 0);
    analogWrite(A14, 0);
  }
  //end of start up animantion

  MIDI.begin(MIDI_CHANNEL_OMNI);
  // Connect the Handlers to the library, so it is called upon reception.
  MIDI.setHandleNoteOn(HandleNoteOn);  // Put only the name of the function
  usbMIDI.setHandleNoteOn(HandleNoteOn);  // Put only the name of the function
  MIDI.setHandleControlChange(HandleControlChange);
  usbMIDI.setHandleControlChange(HandleControlChange);
  MIDI.setHandleNoteOff(HandleNoteOff);
  usbMIDI.setHandleNoteOff(HandleNoteOff);

  MIDI.setHandleClock(HandleClock);
  MIDI.setHandleStart(HandleStart);
  MIDI.setHandleStop(HandleStop);
  MIDI.setHandleContinue(HandleContinue);
  usbMIDI.setHandleRealTimeSystem(RealTimeSystem); 

  Serial.begin(9600);
}

void loop() {
  // Call MIDI.read the fastest you can for real-time performance.
  MIDI.read();
  usbMIDI.read();

  // There is no need to check if there are messages incoming if they are bound to a Callback function.
}
void RealTimeSystem(byte realtimebyte) { 
  if(realtimebyte == CLOCK) { 
    HandleClock();
  } 
  if(realtimebyte == STOP) { 
    HandleStop();
  } 
  if(realtimebyte == START) { 
    HandleStart();
  }
  if(realtimebyte == CONTINUE) { 
    HandleContinue();
  }
} 
