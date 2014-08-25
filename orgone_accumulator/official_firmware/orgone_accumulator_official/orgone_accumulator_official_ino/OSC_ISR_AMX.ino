void OSC_ISR_AMX(){
 

 
  
  oSQ.phase = oSQ.phase +  (uint32_t)oSQ.phase_increment; //square wave osc
  digitalWriteFast (oSQout,(oSQ.phase < oSQ.PW)); //pulse out 
  
 
  
    //----------------------------------------------ALT AM mode-----------------------------------------
   
    
    noiseTable[o1.phase>>23]= random(-32767,32767); //replace noise cells with random values.

lfo.phase = lfo.phase + lfo.phase_increment;
    lfo.wave = FMTableAMX[lfo.phase>>23];    
    
    //main oscillator
    o1.phaseOffset = (FMX_HiOffset * lfo.wave);   
    o1.phase = o1.phase + (o1.phase_increment + o1.phaseOffset);           
    o2.phase = o2.phase +  o2.phase_increment; 
    //unisone oscillators  ------------3-4---------
    o3.phaseOffset = (FMX_HiOffset * lfo.wave);   
    o3.phase = o3.phase + (o3.phase_increment + o3.phaseOffset);           
    o4.phase = o4.phase +  o4.phase_increment;  
    //---------------------------------5-6------------ 
    o5.phaseOffset = (FMX_HiOffset * lfo.wave);   
    o5.phase = o5.phase + (o5.phase_increment + o5.phaseOffset);           
    o6.phase = o6.phase +  o6.phase_increment;     
    //-------------------------------7-8-------------- 
    o7.phaseOffset = (FMX_HiOffset * lfo.wave);   
    o7.phase = o7.phase + (o7.phase_increment + o7.phaseOffset);           
    o8.phase = o8.phase +  o8.phase_increment; 
    //------------------------------9-10-------------------
    o9.phaseOffset = (FMX_HiOffset * lfo.wave);   
    o9.phase = o9.phase + (o9.phase_increment + o9.phaseOffset);           
    o10.phase = o10.phase +  o10.phase_increment; 
        
    //-----------------------------------------------------------------------
    //o2.wave = (((waveTableLink[o2.phase>>23]*mixHi)+(waveTable2Link[o2.phase>>23]*mixLo)+(waveTableMidLink[o2.phase>>23]*mixMid)))>>11;
    o2.wave = FMTable[o2.phase>>23];
    o4.wave = FMTable[o4.phase>>23];
    o6.wave = FMTable[o6.phase>>23];
    o8.wave = FMTable[o8.phase>>23];
    o10.wave = FMTable[o10.phase>>23];

    //CZmode
    o1.wave = (((waveTable2Link[o1.phase>>23]*mixLo)+(waveTableMidLink[o1.phase>>23]*(mixMid+mixHi)))>>11);
    o1.wave = ((o1.wave *(2047-CZMix))>>11)  +  ((int32_t)(((o1.wave) * ((o2.wave*CZMix)>>11))>>15)); 
    
    o3.wave = (((waveTable2Link[o3.phase>>23]*mixLo)+(waveTableMidLink[o3.phase>>23]*(mixMid+mixHi)))>>11);
    o3.wave = ((o3.wave *(2047-CZMix))>>11)  +  ((int32_t)(((o3.wave) * ((o4.wave*CZMix)>>11))>>15));    
    
    o5.wave = (((waveTable2Link[o5.phase>>23]*mixLo)+(waveTableMidLink[o5.phase>>23]*(mixMid+mixHi)))>>11);
    o5.wave = ((o5.wave *(2047-CZMix))>>11)  +  ((int32_t)(((o5.wave) * ((o6.wave*CZMix)>>11))>>15)); 
    
    o7.wave = (((waveTable2Link[o7.phase>>23]*mixLo)+(waveTableMidLink[o7.phase>>23]*(mixMid+mixHi)))>>11);
    o7.wave = ((o7.wave *(2047-CZMix))>>11)  +  ((int32_t)(((o7.wave) * ((o8.wave*CZMix)>>11))>>15)); 
    
    o9.wave = (((waveTable2Link[o9.phase>>23]*mixLo)+(waveTableMidLink[o9.phase>>23]*(mixMid+mixHi)))>>11);
    o9.wave = ((o9.wave *(2047-CZMix))>>11)  +  ((int32_t)(((o9.wave) * ((o10.wave*CZMix)>>11))>>15)); 
    
    


    AGCtest = ((((o9.wave+o7.wave+o5.wave+o3.wave+o1.wave)>>2)*((int)mixDetuneUp))>>14)  +  (((o1.wave*((int)mixDetuneDn))>>14)); //main out and mix detune
    
    analogWrite(aout2,AGCtest+4000);


}


