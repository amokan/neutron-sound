void UPDATE_LEDS(){

  switch (ARC+1) {
    case 1:
    analogWrite(LED_Lo,(mixLo<<2)-LED_comp);
    break;
    case 2:
    analogWrite(LED_Mid,(mixMid<<2)-LED_comp);
    break;
    case 3:
    analogWrite(LED_Hi,(mixHi<<2)-LED_comp);
    break;
  }
}
