void HandleClock(void){
  if (playing){
  pulses ++;
  if (pulses > 5){
    pulses = 0;
    sixteenthnotes++;
  }
  if (pulses < 4){
//    analogWrite(out2pin[3],127);
//    digitalWriteFast(out2pin[3],HIGH);
  }
//   else analogWrite(out2pin[3],0);
//    else digitalWriteFast(out2pin[3],LOW);
}
}

 void HandleStart(){
  pulses = 0;
  thirtysecondths = 0;
  playing = 1;    
  if(playing) {
     digitalWriteFast(out2pin[3],HIGH);
  }
  }
  
 void HandleStop(){
  playing = 0; //remove this to have continuous clock pulses on dodeca after sequencer is stopped
  digitalWriteFast(out2pin[3],LOW);  //turn pulse off when stopped even if it is in the middle of "on" cycle
  }

  
  void HandleContinue(){
    //maybe only needed for song position pointer
    playing = 1; 
    pulses = 0;
    thirtysecondths = 0;
      if(playing) {
      digitalWriteFast(out2pin[3],HIGH);
      }
}
