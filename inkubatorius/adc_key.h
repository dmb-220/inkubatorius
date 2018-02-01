//ADC
void InitADC(){
ADMUX=(1<<REFS0); // ADC Vref=AVCC, ADC0=in
ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); // enable, ADC prescaler 128 
}

uint16_t ReadADC(uint8_t ch){
   ch=ch&0b00000111;
   ADMUX|=ch;
   ADCSRA|=(1<<ADSC); // START ADC READ
   while(!(ADCSRA & (1<<ADIF))); //uzsiciklinam kol nebaigs darba ADC.
   ADCSRA|=(1<<ADIF);
   return(ADCW);
}

//nuskaitomas myktuko reiksme
void read_key(){
  //nuskaitoma ADC reiksme
//abutton=analogRead(ADC_KEYPAD);
abutton = ReadADC(0);
  //tikrinama koks myktukas buvo nuspaustas
  if (abutton<20){button=1; btn=1; /*Kaire*/ }else 
  if (abutton<550 && abutton>450){button=2; btn=2; /*Desine*/ }else  
  if (abutton<400 && abutton>300){button=3; btn=3; /*Zemyn*/ }else 
  if (abutton<200 && abutton>100){button=4; btn=4; /*Aukstyn*/ }else
  if (abutton<800 && abutton>700){button=5; btn=5; /*Meniu - Atgal - OK*/ }else{button=0;}  
}

