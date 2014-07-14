void loop() { 

  int buh = random(0,512);

  //slow generated signals
  noiseTable2[buh]= random(-32767,32767); //hypnotoad noise (noiseTable2)
  
  SWC ++;
  if (SWC > ((analogControls[0]>>6))){
  NT3Rate = (random(-7,8))-(noiseTable3[0]/4198); //LF noise (noiseTable3)
  SWC = 0;}


  ARC ++;
  if ((ARC == 7 || ARC == 9)&& tuneLockOn) ARC ++; //skip reading tuning knobs if tunelock is on.
  if (ARC > 9) {
    ARC = 0;
  }  //cycle through analog controls. skip tuning controls if tunelock is on.

  //--------------------------------------------------------  
  inCV = (analogRead(A0)); //main v/oct CV in. only use 12 bits of analog in SEPERATE AINS BY CODE 
  //--------------------------------------------------------  

  //______________TUNING OPTIONS
  //change notesize*1 to notesize*2 or notesize*3 you will have wider range tuning but 2 or 3 semitone steps
  int tuner = inCV+((analogControls[9]>>8)*(noteSize*1))+(analogControls[7]>>4);//coarse and fine tuning
  //comment out above line and uncomment following line for analog style non stepped tuning 
  //int tuner = inCV+(analogControls[9]>>1)+(analogControls[7]>>4);
  //_____________END TUNINGOPTIONS
  
  inputScaler = float(tuner/octaveSize);  
  inputVOct = pow(2.0,inputScaler); //"real time" exponentiation of CV input!  
  inputConverter = inputVOct*59000; //<-----------------------------number is MASTER TUNING also affected by ISR speed 
  //divide by 4 if you want to use -1, -2 octaves

  //------------------------------Position CV---------------------
  aInPos = 4095-((analogRead(A16))) ;  
  //------------------------------------------------------------------
  aInModDetuneCubing = max((aInModDetune+detuneAmountCont),0)/64.0;
  aInModDetune = ((aInModDetuneCubing*aInModDetuneCubing*aInModDetuneCubing)/8.0);
  //switches between prime and even spaced detune modes.
  if (primeDetuneOn){   //Detune does not follow pitch 
    detuneScaler = aInModDetune * mixDetune ;
    for (int i=0; i <= 3; i++){  
      detune[i] = (uint32_t)((detuneScaler/300000.0) * primes[i]); 

    }
  }
  else{  //detune follows pitch, detune up to "hoover"
    detuneScaler = aInModDetune;
    detune[1] = detune[3]=(uint32_t)((detuneScaler/32768.0)*(inputConverter));
    detune[2] = detune[0]=(uint32_t)((detuneScaler/16384.0)*(inputConverter)) ; 
  }

  //---------------------------------------------------------------------
  analogControls[ARC] = analogRead(ARC+2);//step through control knob readings one per cycle, humans are slow
  //----------------------------------------------------------------------  

  //running average filter of ratio CV and index CV they are sensetive to noise.
  totalaInRAv = totalaInRAv - readingsaInRAv[indexaInRAv]; 
  totalaInIAv = totalaInIAv - readingsaInIAv[indexaInRAv];

  readingsaInRAv[indexaInRAv] = AInRawFilter = (8191-analogRead(A17)); //adjust numreadingsaInRAv on first page for filtering.    
  readingsaInIAv[indexaInRAv] = aInModIndex;

  totalaInRAv = totalaInRAv + readingsaInRAv[indexaInRAv];
  totalaInIAv = totalaInIAv + readingsaInIAv[indexaInRAv];

  indexaInRAv = indexaInRAv + 1;
  if (indexaInRAv >= numreadingsaInRAv) indexaInRAv = 0;

  averageaInRAv = (totalaInRAv / numreadingsaInRAv);
  averageaInIAvCubing = (4095-(totalaInIAv / numreadingsaInRAv))/512.0;
  averageaInIAv = totalaInIAv / numreadingsaInRAv;



  envVal = constrain((aInPos + mixPos),0,4095); //mix the position knob with the modulation from the CV input (fix for bipolar)
  //AGCoffset = 8191 - AGCslow;

  
   mixMid = constrain((2047-abs(envVal-2047)),0,2047);//sets the level of the midpoint wave  
  mixHi = constrain((((envVal))-2047),0,2047);//sets the level of the high wave
  mixLo = constrain((2047-((envVal))),0,2047);//sets the level of the low wave

  //---------------------------Detune CV----------------
  aInModDetune = ((4095-analogRead(A12))<<1);  
  //--------------------------------------------------

  //see if the gate input changed, trigger resets.

  gateTest =digitalReadFast(gateIn);
  //digitalWriteFast(LED_gate,!gateTest);
  if (gateTest > gateOld) {
    gate=1;
  } //gate gets set to zero after oscs reset.
  gateOld = gateTest;       

  //---------------------------Index CV---------------------------------
  aInModIndex = analogRead(A15);
  //----------------------------------------------------------------------

  if (gate){  //reset oscillators to zero phase on gate input.

    //oSQ.phase = 0; leave PWM osc free running uncomment to have it reset
    o1.phase = 
      o2.phase = 
      o3.phase = 
      o4.phase = 
      o5.phase = 
      o6.phase = 
      o7.phase =
      o8.phase = 
      o9.phase = 
      o10.phase = 0;
    detuneScaler = 0;
    gate = 0;
    randomSeed(analogControls[0]>>5);  
    ;
  }

  else ASSIGNINCREMENTS();  

  UPDATE_LEDS();

}




