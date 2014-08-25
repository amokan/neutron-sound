void OSC_ISR_FM(){


 
 
  
 oSQ.phase = oSQ.phase +  (uint32_t)oSQ.phase_increment; //square wave osc
 digitalWriteFast (oSQout,(oSQ.phase < oSQ.PW)); //pulse out 
  
  

 
    
  //-----------------------------------------------FM MODE OSCILLATORS-----------------------------------------------
  
    noiseTable3[0]=noiseTable3[1]=(noiseTable3[0]+NT3Rate);
    

    //main oscillator
    o1.phase = o1.phase + o1.phase_increment; 
    noiseTable[o1.phase>>23]= random(-32767,32767); //replace noise cells with random values.  
    o1.wave = (FMTable[o1.phase>>WTShift]);
    //o1.wave = o2.wave;
    o1.index = (FMIndex * o1.wave);   
    o2.phase = o2.phase +  (o2.phase_increment+o1.index); 
    //unisone oscillators  ------------3-4---------
    o3.phase = o3.phase + o3.phase_increment;    
    o3.wave = (FMTable[o3.phase>>WTShift]);
    o3.index = (FMIndex * o3.wave);  
    o4.phase = o4.phase +  (o4.phase_increment+o3.index);   
    //---------------------------------5-6------------ 
    o5.phase = o5.phase + o5.phase_increment;   
    o5.wave = (FMTable[o5.phase>>WTShift]);
    o5.index = (FMIndex * o5.wave);  
    o6.phase = o6.phase + (o6.phase_increment+o5.index);   
    //-------------------------------7-8-------------- 
    o7.phase = o7.phase + o7.phase_increment;   
    o7.wave = (FMTable[o7.phase>>WTShift]);
    o7.index = (FMIndex * o7.wave);   
    o8.phase = o8.phase +  (o8.phase_increment+o7.index); 
    //------------------------------9-10-------------------
    o9.phase = o9.phase + o9.phase_increment;   
    o9.wave = (FMTable[o9.phase>>WTShift]);
    o9.index = (FMIndex * o9.wave);   
    o10.phase = o10.phase + (o10.phase_increment+o9.index);   
    //-----------------------------------------------------------------------

    o2.wave = (((waveTableLink[o2.phase>>23]*mixHi)+(waveTable2Link[o2.phase>>23]*mixLo)+(waveTableMidLink[o2.phase>>23]*mixMid)))>>11;
    o4.wave = (((waveTableLink[o4.phase>>23]*mixHi)+(waveTable2Link[o4.phase>>23]*mixLo)+(waveTableMidLink[o4.phase>>23]*mixMid)))>>11;
    o6.wave = (((waveTableLink[o6.phase>>23]*mixHi)+(waveTable2Link[o6.phase>>23]*mixLo)+(waveTableMidLink[o6.phase>>23]*mixMid)))>>11;
    o8.wave = (((waveTableLink[o8.phase>>23]*mixHi)+(waveTable2Link[o8.phase>>23]*mixLo)+(waveTableMidLink[o8.phase>>23]*mixMid)))>>11;
    o10.wave = (((waveTableLink[o10.phase>>23]*mixHi)+(waveTable2Link[o10.phase>>23]*mixLo)+(waveTableMidLink[o10.phase>>23]*mixMid)))>>11;    

    AGCtest = ((((o10.wave+o4.wave+o6.wave+o8.wave+o2.wave)>>2)*((int)mixDetuneUp))>>14)  +  (((o2.wave*((int)mixDetuneDn))>>14)); //main out and mix detune
    analogWrite(aout2,AGCtest+4000);
    
   
}


