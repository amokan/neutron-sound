void UPDATECONTROLS_CHAOS(){

  switch (ARC+1) {

  case 7:
    

    
    break;

  case 9:      
    break;

  case 3:
      buh = digitalReadFast(tuneLockSwitch);
    if (tuneLockOn != buh){
      tuneLockOn = buh;
      if (tuneLockOn == 1) {digitalWriteFast(LED_TuneLock,1);}
      else {digitalWriteFast(LED_TuneLock,0);}      
    }             
    detuneAmountCont = analogControls[2];
    //detuneAmountCont = (detuneAmountContCubing*detuneAmountContCubing*detuneAmountContCubing)/1024.0;  
    break;

  case 4:

    chaosMult2 = pow(((analogControls[5]>>4)+0.1),3.0)/1000000000;///mid frequency     
    
    break;

  case 5:
    //select wave lo freq
    chaosMult1 = pow(((analogControls[8]>>4)+0.1),3.0)/1000000000;
    break;

  case 6: //select hi freq
    chaosMult3 = pow(((analogControls[4]>>4)+0.1),3.0)/1000000000;

    break;  

  case 1:     
    mixPos = (analogControls[6]>>4)<<3; 
    
//    CZmodeOn = !digitalReadFast(CZmodeSwitch);
//    xModeOn = !digitalReadFast(xModeSwitch);
    
    FMFixedOn = !digitalReadFast(FMFixedSwitch);
    if (FMFixedOn && !FMFixedOnToggle){inputConverterF = inputConverter;} //sets fixed frequency to current frequency when fixed is pushed.
    FMFixedOnToggle = FMFixedOn;         
    
    oscMode = (!digitalReadFast(xModeSwitch)<<1)+ digitalReadFast(CZmodeSwitch);   
    break; 

  case 8:
  primeDetuneOn = !digitalReadFast(primeSwitch);
    detuneLoOn = !digitalReadFast(detuneLoSwitch); 
    detuneMidOn = !digitalReadFast(detuneMidSwitch); 
    detuneHiOn = !digitalReadFast(detuneHiSwitch);    

    break;

  case 2:
    totalratio = totalratio - readingsratio[controlAveragingIndex]; 
    readingsratio[controlAveragingIndex] = analogControls[0];
    totalratio = totalratio + readingsratio[controlAveragingIndex];
    controlAveragingIndex = controlAveragingIndex + 1;
    if (controlAveragingIndex >= numreadingsratio) controlAveragingIndex = 0;
    averageratio = totalratio / numreadingsratio;    
     break; 

  case 10:
    FMIndexCont = (analogControls[1]/4.0);
   
    
//    else {
//      FMIndexContCubing = (analogControls[8])/1024.0;
//      FMIndexCont = (int) (FMIndexContCubing* FMIndexContCubing*FMIndexContCubing); 
//    }
    
     switch (analogControls[3]>>9){
    case 0: 
      FMTable = sinTable; 
      break;
    case 1: 
      FMTable = triTable; 
      break;
    case 2: 
      FMTable = FMTableS180; 
      break;
    case 3: 
      FMTable = FMTableSQ; 
      break;
    case 4: 
      FMTable = FMTableSQR; 
      break;
    case 5: 
      FMTable = AKWF_0003; 
      break;
    case 6: 
      FMTable = pnoTable; 
      break;
    case 7: 
      FMTable = bassTable1; 
      break;
    case 8: 
      FMTable = bassTable2; 
      break;
    case 9: 
      FMTable = celloTable; 
      break;
    case 10: 
      FMTable = violTable; 
      break;
    case 11: 
      FMTable = FMTableFM98; 
      break;
    case 12: 
      FMTable = FMTablehvoice26; 
      break;
    case 13: 
      FMTable = voiceTable; 
      break;
    case 14: 
      FMTable = sawTable; 
      break;
    case 15: 
      FMTable = noiseTable2; 
      break;    
    }
    

    break;   


  }
}

