void HandleClock(void){
  if (playing){
  pulses ++;
  if (pulses > 5){
    pulses = 0;
    sixteenthnotes++;
  }
  if (pulses <2 ){
//    analogWrite(out2pin[3],127);
    digitalWrite(out2pin[3],HIGH);
  }
//   else analogWrite(out2pin[3],0); 
   else digitalWrite(out2pin[3],LOW);
}
}

 void HandleStart(){
  pulses = -1;
  sixteenthnotes = 0;
  currentSPP = 0;
  playing = 1;    
  }
  
 void HandleStop(){
  playing = 0; //remove this to have continuous clock pulses on dodeca after sequencer is stopped
  digitalWriteFast(out2pin[3],LOW);  //turn pulse off when stopped even if it is in the middle of "on" cycle
  }

  
  void HandleContinue(){
    //maybe only needed for song position pointer
    pulses = currentSPP - 1;
    sixteenthnotes = currentSixteenthnotes;

//    quartertoggle = SPP/(4*timeSig);
//    sixteenthnotes = (SPP/4) % 4;
//    pulses = (SPP % 4) * 6;
    playing = 1;    
  }

  void HandleSongPosition(){
    quartertoggle = SPP/(4*timeSig);
    currentSixteenthnotes = (SPP/4) % 4;
    currentSPP = (SPP % 4) * 6;
    
  }
  
