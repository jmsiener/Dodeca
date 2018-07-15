void HandleClock(void){
    if (playing){
    pulses ++;

    dv = clockdiv >> 4;
    if (pulses > ((3<<dv)-1)){
       pulses = 0;
       sixteenthnotes ++;     
     }
     if (pulses < ((3<<dv)>>1)){
        analogWrite(out2pin[3],AMAX-1); // clock LED on
       //  digitalWrite(ledPin, HIGH);   // set the LED on
     } else {
        analogWrite(out2pin[3],0); // clock LED off
      //  digitalWrite(ledPin, LOW);    // set the LED off
     }

   }
}

 void HandleStart(){
  pulses = 0;
  sixteenthnotes = 0;
  playing = 1;    
  }
  
 void HandleStop(){
  playing = 0; //remove this to have continuous clock pulses on dodeca after sequencer is stopped
  digitalWriteFast(out2pin[3],LOW);  //turn pulse off when stopped even if it is in the middle of "on" cycle
  }

  
  void HandleContinue(){
    //maybe only needed for song position pointer
  }


