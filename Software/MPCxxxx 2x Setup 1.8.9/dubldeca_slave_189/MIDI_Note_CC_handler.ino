void HandleNoteOn(byte channel, byte pitch, byte velocity) {
  if (channel == CHANA) {
    int modNote = (whitekeys[pitch % 12] ) ;
    if (velocity != 0) {
      if (modNote) {
        digitalWriteFast(out2pin[modNote], HIGH);
        if (velocity > accentVel) {
               digitalWriteFast(out2pin[5], HIGH); 
        }
      }
    }
    else bothNoteOff(channel, pitch, velocity);
  }
  if (channel == CHANB) {

    if (velocity != 0) {

      analogWrite(out2pin[0], velocity);
      analogWrite(A14, pitch - 24);
      analogWrite(out2pin[2], 127);
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
      digitalWriteFast(out2pin[modNote], LOW);
      digitalWriteFast(out2pin[5], LOW);
    }
  }
  if (channel == CHANB) {
    //analogWrite(out2pin[0], 0);
    analogWrite(out2pin[2], 0);
  }
}


void HandleControlChange (byte channel, byte number, byte value) {
  if (channel == CHANA) {

    for (int i = 0; i < 3; i ++) {
      if ( number  == cc2active[i]) { //ignore wrong channel or CC numbers
        analogWrite(out2pin[cc2out[i]], value);
      }
    }
  }
}
