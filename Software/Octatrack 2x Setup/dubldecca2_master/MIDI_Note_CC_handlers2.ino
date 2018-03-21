void HandleNoteOn(byte channel, byte pitch, byte velocity) {
  pitchCV = (pitch * V_scale); // note-number to pitch value for DAC output
  pitchLED = map (pitch, 0, 127, 2*V_scale, AMAX);  // set brightness of pitch led
  
  // 1 octave = 1 volt
  // one note = 1/12 octave = 0.83333 volts
  // one midi note interval is one equally tempered semitone
  // one cent = 0.083 volts

  if (channel == CHANA) {
    int modNote = (whitekeys[pitch % 12] ) ;
    if (velocity != 0) {
      if (modNote) {
        analogWrite(out2pin[modNote], velocity * V_scale); // sends notes to trig outputs
      }
     
    }
    else bothNoteOff(channel, pitch, velocity);
  }
  if (channel == CHANB) {

    if (velocity != 0) {

      analogWrite(out2pin[0], velocity * V_scale);    // velocity output
      analogWrite(A14, pitchCV);        // pitch to v/oct output
      analogWrite(out2pin[1], pitchLED);       // light up v/oct LED 
      analogWrite(out2pin[2], AMAX);         // gate output
    }
    else bothNoteOff(channel, pitch, velocity);
  }
}

void HandleNoteOff(byte channel, byte pitch, byte velocity) {
  bothNoteOff(channel, pitch, velocity);
}

void bothNoteOff(byte channel, byte pitch, byte velocity) { //this is called by handle noteoff and note on when velocity = 0
  if (channel == CHANA) {
    int modNote = (whitekeys[pitch % 12] ) ;
    if (modNote) {
      analogWrite(out2pin[modNote], 0);
    }
  }
  if (channel == CHANB) {
    //analogWrite(out2pin[0], 0);
    analogWrite(out2pin[2], 0); // velocity off
    analogWrite(out2pin[1], 0); // note led off
    analogWrite(A14, 0); // note voltage off
    // THIS IS WHERE YOU MIGHT WANT TO TURN OFF VELOCITY, NOTE AND LED
  }
}


void HandleControlChange (byte channel, byte number, byte value) {
  if (channel == CHANA) {

    for (int i = 0; i < 5; i ++) {
      if ( number  == cc2active[i]) { //ignore wrong channel or CC numbers
        analogWrite(out2pin[cc2out[i]], value);
      }
    }
  }
}



