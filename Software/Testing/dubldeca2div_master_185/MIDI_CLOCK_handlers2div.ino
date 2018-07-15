void HandleClock(void){
  if (playing){
  pulses ++;
  
// 24 pulses per quarter note
// change 5 to 11 it will do 1/8 (and change the 3 to 6)
// change to 23 and 12 for 1/4 notes

 //ok, you can make 2 variables from a cc. first reducing the bits from 7 to 3 with ccvalue>>4. so you have 0-7
// call it "dv" for now
// if (pulses < ((3<<dv)-1)) for that part.
// and  if (pulses > ((3<<dv)>>1)) for the high/low switching

    dv = clockdiv >> 4;
    if (pulses < ((3<<dv)-1)){
        pulses = 0;
        sixteenthnotes ++;     
    }
    if (pulses > ((3<<dv)>>1)){
        analogWrite(out2pin[3],AMAX-1); // clock LED on
    } else {
        analogWrite(out2pin[3],0); // clock LED off
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


