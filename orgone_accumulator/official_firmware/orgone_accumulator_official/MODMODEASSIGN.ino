void ASSIGNINCREMENTS(){

  switch(oscMode){ //switches which oscs get changed by FM and how much multiplier ;

  case 0:  
    UPDATECONTROLS_FM();  
    
     
    
    FMIndexContCubing = FMIndexCont/256.0;  
    FMIndex= (uint32_t((float)(((FMIndexContCubing*FMIndexContCubing*FMIndexContCubing)+(averageaInIAvCubing*averageaInIAvCubing*averageaInIAvCubing))*(inputVOct/4.0))));
    mixDetuneUp = mixDetune*0.787;//because there are 5 oscillators being mixed in the detune mix of ISR
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/2048.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn);  
    mixDetuneDn =  (2047-mixDetune)*0.97; 


    if (FMFixedOn){
      FMMult = (((averageratio>>1)/2.1)+1.0)*aInModRatio;  //FM+fixed mult control 
      osc_mult[0]=FMMult;
      osc_mult[1]=4;
      o2.phase_increment = inputConverter*osc_mult[1]  ;
      o4.phase_increment = inputConverter*osc_mult[1]+ detune[0];
      o6.phase_increment = inputConverter*osc_mult[1]+ detune[3];
      o8.phase_increment = inputConverter*osc_mult[1]- detune[2];
      o10.phase_increment = inputConverter*osc_mult[1] - detune[1];
      o1.phase_increment = inputConverterF*osc_mult[0] ;
      o3.phase_increment = inputConverterF*osc_mult[0]+ detune[0];
      o5.phase_increment = inputConverterF*osc_mult[0]+ detune[3];
      o7.phase_increment = inputConverterF*osc_mult[0]- detune[2];
      o9.phase_increment = inputConverterF*osc_mult[0]- detune[1];   
    }
    else {
      FMMult = ((int)((averageratio>>9)+1))*aInModRatio; //FM + free 
      osc_mult[0]=FMMult;
      osc_mult[1]=4;
      o2.phase_increment = inputConverter*osc_mult[1] ;
      o4.phase_increment = inputConverter*osc_mult[1]+ detune[0];
      o6.phase_increment = inputConverter*osc_mult[1]+ detune[3];
      o8.phase_increment = inputConverter*osc_mult[1]- detune[2];
      o10.phase_increment = inputConverter*osc_mult[1] - detune[1];
      o1.phase_increment = inputConverter*osc_mult[0] ;
      o3.phase_increment = inputConverter*osc_mult[0]+ detune[0];
      o5.phase_increment = inputConverter*osc_mult[0]+ detune[3];
      o7.phase_increment = inputConverter*osc_mult[0]- detune[2];
      o9.phase_increment = inputConverter*osc_mult[0] - detune[1];
    }
    break; 


  
  case 2://fm mode with x button pressed allows pitch bending on hi position and FM is LFO in fixed (no auto get freq). 

    UPDATECONTROLS_FMALT(); 
    
  

    FMIndexContCubing = FMIndexCont/256.0;  
    FMIndex= (uint32_t((float)(((FMIndexContCubing*FMIndexContCubing*FMIndexContCubing)+(averageaInIAvCubing*averageaInIAvCubing*averageaInIAvCubing))*(inputVOct/8.0))));
    mixDetuneUp = mixDetune*0.787;//because there are 5 oscillators being mixed in the detune mix of ISR
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/512.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn);  
    mixDetuneDn =  (2047-mixDetune)*0.97; 


    if (FMFixedOn){
      FMMult = (((averageratio>>1)/2.1)+1.0)*aInModRatio;  //FM+fixed mult control 
      osc_mult[0]=FMMult;
      osc_mult[1]=4;
      FMX_HiOffset=mixHi*FMX_HiOffsetCont;
      o2.phase_increment = inputConverter*osc_mult[1] + FMX_HiOffset ;
      o4.phase_increment = inputConverter*osc_mult[1]+ detune[0]+ FMX_HiOffset;
      o6.phase_increment = inputConverter*osc_mult[1]+ detune[3]+ FMX_HiOffset;
      o8.phase_increment = inputConverter*osc_mult[1]- detune[2]+ FMX_HiOffset;
      o10.phase_increment = inputConverter*osc_mult[1] - detune[1]+ FMX_HiOffset;
      o1.phase_increment = inputConverterF*osc_mult[0] ;
      o3.phase_increment = inputConverterF*osc_mult[0] ;
      o5.phase_increment = inputConverterF*osc_mult[0] ;
      o7.phase_increment = inputConverterF*osc_mult[0] ;
      o9.phase_increment = inputConverterF*osc_mult[0] ;   
    }
    else {
      FMMult = ((int)((averageratio>>9)+1))*aInModRatio; //FM + free 
      osc_mult[0]=FMMult;
      osc_mult[1]=4;
      FMX_HiOffset=mixHi*FMX_HiOffsetCont;
      o2.phase_increment = inputConverter*osc_mult[1]+ FMX_HiOffset ;
      o4.phase_increment = inputConverter*osc_mult[1]+ detune[0]+ FMX_HiOffset;
      o6.phase_increment = inputConverter*osc_mult[1]+ detune[3]+ FMX_HiOffset;
      o8.phase_increment = inputConverter*osc_mult[1]- detune[2]+ FMX_HiOffset;
      o10.phase_increment = inputConverter*osc_mult[1] - detune[1]+ FMX_HiOffset;
      o1.phase_increment = inputConverter*osc_mult[0] ;
      o3.phase_increment = inputConverter*osc_mult[0]+ detune[0];
      o5.phase_increment = inputConverter*osc_mult[0]+ detune[3];
      o7.phase_increment = inputConverter*osc_mult[0]- detune[2];
      o9.phase_increment = inputConverter*osc_mult[0] - detune[1];
    }
    break; 
case 1://cz

    UPDATECONTROLS_CZ(); 
    
  
    
    CZMix = constrain((FMIndexCont+(2047-(averageaInIAv/2.0))),0,2047); 
    mixDetuneUp = mixDetune*0.787;//because there are 5 oscillators being mixed in the detune mix of ISR 
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/2048.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn);  
    mixDetuneDn =  (2047-mixDetune)*0.97; 


    
    if (FMFixedOn){
      FMMult = (float)((((averageratio>>4)/1.1))+1.0)*aInModRatio; //CZ + fixed + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverterF*osc_mult[1]; 
      o4.phase_increment = inputConverterF*osc_mult[1];
      o6.phase_increment = inputConverterF*osc_mult[1];
      o8.phase_increment = inputConverterF*osc_mult[1];
      o10.phase_increment = inputConverterF*osc_mult[1];
      o1.phase_increment = inputConverter*osc_mult[0];
      o3.phase_increment = inputConverter*osc_mult[0]+ detune[3];
      o5.phase_increment = inputConverter*osc_mult[0]+ detune[2];
      o7.phase_increment = inputConverter*osc_mult[0]- detune[1];
      o9.phase_increment = inputConverter*osc_mult[0] - detune[0];
    }
    else{
      FMMult = (float)((((averageratio>>5)/7.0))+1.0)*aInModRatio; //CZ + free + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverter*osc_mult[1];
      o4.phase_increment = inputConverter*osc_mult[1]+ detune[3];
      o6.phase_increment = inputConverter*osc_mult[1]+ detune[2];
      o8.phase_increment = inputConverter*osc_mult[1]- detune[1];
      o10.phase_increment = inputConverter*osc_mult[1] - detune[0];
      o1.phase_increment = inputConverter*osc_mult[0];
      o3.phase_increment = inputConverter*osc_mult[0]+ detune[3];
      o5.phase_increment = inputConverter*osc_mult[0]+ detune[2];
      o7.phase_increment = inputConverter*osc_mult[0]- detune[1];
      o9.phase_increment = inputConverter*osc_mult[0] - detune[0];
    }
    break; 


  case 3://ALT CZ  

    UPDATECONTROLS_CZALT();
    
  

    CZMix = constrain((FMIndexCont+(2047-(averageaInIAv/2.0))),0,2047); 
    CZMix = (CZMix *((mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn)))>>11;  //mixing index with detune buttons.  

    mixDetuneUp = mixDetune*0.787;//because there are 5 oscillators being mixed in the detune mix of ISR 
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/2048.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = 2047;  //degraded for now, jkeep for adding CV detune mix to this mode
    mixDetuneDn =  (2047-mixDetune)*0.97; 


    
    if (FMFixedOn){
      FMMult = (float)((((averageratio>>4)/1.1))+1.0)*aInModRatio; //CZ + fixed + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverterF*osc_mult[1]; //modulation not detuned for better acid sound
      o4.phase_increment = inputConverterF*osc_mult[1];
      o6.phase_increment = inputConverterF*osc_mult[1];
      o8.phase_increment = inputConverterF*osc_mult[1];
      o10.phase_increment = inputConverterF*osc_mult[1];
      o1.phase_increment = inputConverter*osc_mult[0];
      o3.phase_increment = inputConverter*osc_mult[0]+ detune[3];
      o5.phase_increment = inputConverter*osc_mult[0]+ detune[2];
      o7.phase_increment = inputConverter*osc_mult[0]- detune[1];
      o9.phase_increment = inputConverter*osc_mult[0] - detune[0];
    }
    else{
      FMMult = (float)((((averageratio>>5)/7.0))+1.0)*aInModRatio; //CZ + free + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverter*osc_mult[1];
      o4.phase_increment = inputConverter*osc_mult[1]+ detune[3];
      o6.phase_increment = inputConverter*osc_mult[1]+ detune[2];
      o8.phase_increment = inputConverter*osc_mult[1]- detune[1];
      o10.phase_increment = inputConverter*osc_mult[1] - detune[0];
      o1.phase_increment = inputConverter*osc_mult[0];
      o3.phase_increment = inputConverter*osc_mult[0]+ detune[3];
      o5.phase_increment = inputConverter*osc_mult[0]+ detune[2];
      o7.phase_increment = inputConverter*osc_mult[0]- detune[1];
      o9.phase_increment = inputConverter*osc_mult[0] - detune[0];
    }

    break; 

  }

  oSQ.phase_increment = inputConverter*4;
  oSQ.PW = (envVal<<20)+(FMIndexCont<<20);   //pwm.phase inc

  //BSFfreq = min((o2.phase_increment>>16),2047); 

}

