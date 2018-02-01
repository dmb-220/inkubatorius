//isvalyti pasirinkta eilute duomenu atnaujinimui
void valyti_eilute(int nr){
  for(int i=0; i<=20; i++){
     lcd.setCursor (i, nr );
     lcd.print(" ");
    }
  }

void valyti_eilute2(int nr, int nuo, int iki){
  for(int i=nuo; i<=iki; i++){
     lcd.setCursor (i, nr );
     lcd.print(" ");
    }
  }
  
void issaugota(){
  lcd.setCursor (5, 1);
   lcd.print("ISSAUGOTA!");
    if(button!=btn){
     if(btn == 5){set_meniu=1; meniu=0; btn = 0; lcd.clear();}}
  }

void nuskaityti(){
  //Pauksciai
  rtc.eeprom_read(PERINIMAS_PAUKSTIS, &paukstis);
  rtc.eeprom_read(PERINIMAS_DIENOS, &dienu_sk);
  rtc.eeprom_read(VARTYMAS_DIENOS, &isj_vartyma);
  //Garsas
  rtc.eeprom_read(GARSAS_POWER, &garsas);
  //temperatura
  rtc.eeprom_read(TMIN, &mini_temp);
  rtc.eeprom_read(TMAX, &maxi_temp);
  //dregme
  rtc.eeprom_read(DMIN, &mini_dreg);
  rtc.eeprom_read(DMAX, &maxi_dreg);
  //ventiliatorius
  rtc.eeprom_read(FAN, &fan_reiksme);
  rtc.eeprom_read(FAN_2, &fan_reiksme2);
  rtc.eeprom_read(FAN_POWER, &fan_power);
  //vartymo nustatymai
  rtc.eeprom_read(VARTYMAS_POWER, &vartymas_power);
  rtc.eeprom_read(VARTYMAS_MIN, &vartymas_min);
  rtc.eeprom_read(VARTYMAS_MAX, &vartymas_max);
  //sildymo ir vandens ISJUNGIMAS /IJUNGIMAS
  rtc.eeprom_read(VANDUO_POWER, &vanduo_power);
  rtc.eeprom_read(SILDYMAS_POWER, &sildymas_power);
  //Kalibravamas
  rtc.eeprom_read(SHT_D1, &sht_dr1);
  rtc.eeprom_read(SHT_D2, &sht_dr2);
  rtc.eeprom_read(SHT_T1, &sht_t1);
  rtc.eeprom_read(SHT_T2, &sht_t2);
  //Inkubatoriaus STARTAS
  rtc.eeprom_read(PERINIMAS_POWER, &startas);
  rtc.eeprom_read(PRADZIA_METAI, &pradzia_metai);
  rtc.eeprom_read(PRADZIA_MENUO, &pradzia_menuo);
  rtc.eeprom_read(PRADZIA_DIENA, &pradzia_diena);
  }
////////////////////////////////////////// LAIKAS IR DATA ///////////////////////////////  
void nustatyti_laika(){
  lcd.setCursor (7, 0 ); lcd.print("LAIKAS");
  lcd.setCursor (3*pos, 1 ); lcd.print("__");
 
  lcd.setCursor(3, 2); lcd.print("<-");
  
  lcd.setCursor(6, 2);
  if(set_hours<10){
    lcd.print('0'); }
  lcd.print(set_hours);
  
  lcd.setCursor(8, 2); lcd.print(':'); 
  
  lcd.setCursor(9, 2);
  if(set_minutes<10){
    lcd.print('0'); }
  lcd.print(set_minutes);
  
  lcd.setCursor(11, 2); lcd.print(':'); 
  
  lcd.setCursor(12, 2);
  if(set_second<10){
    lcd.print('0'); }
  lcd.print(set_second);
  
  lcd.setCursor(15, 2); lcd.print("->");       
            
  if(button!=btn){
    if(btn == 4 && pos == 2){if(set_hours<23){set_hours++;} btn=0;}
    if(btn == 3 && pos == 2){if(set_hours>0){set_hours--;} btn=0;}
    if(btn == 4 && pos == 3){if(set_minutes<59){set_minutes++;} btn=0;}
    if(btn == 3 && pos == 3){if(set_minutes>0){set_minutes--;} btn=0;}
    if(btn == 4 && pos == 4){if(set_second<59){set_second++;} btn=0;}
    if(btn == 3 && pos == 4){if(set_second>0){set_second--;} btn=0;}

    if(btn == 5 && pos == 5){meniu=2; pos=1; btn=0; lcd.clear();}
    if(btn == 5 && pos == 1){set_meniu=10; meniu=0, btn = 0; lcd.clear();}
    
    if(btn == 2){if(pos<5){pos++;} btn=0;}
    if(btn == 1){if(pos>1){pos--;} btn=0;}}
    //isvaloma norima eilute
    if(pos != pos_old){
      valyti_eilute(1); pos_old = pos;}
    }

void nustatyti_data(){
  lcd.setCursor (8, 0 ); lcd.print("DATA");
  if(pos == 2){lcd.setCursor (2*pos+1, 1 ); lcd.print("____");}else
  if(pos == 1){lcd.setCursor (2*pos, 1 ); lcd.print("__");}else{
    lcd.setCursor (3*pos+1, 1 ); lcd.print("__");}
  
  lcd.setCursor(2, 2); lcd.print("<-");
  lcd.setCursor(5, 2); lcd.print(set_metai);
  lcd.setCursor(9, 2); lcd.print('-'); 
  
  lcd.setCursor(10, 2);
  if(set_menesis<10){
    lcd.print('0'); }
  lcd.print(set_menesis);
    
  lcd.setCursor(12, 2); lcd.print('-'); 
    
  lcd.setCursor(13, 2);
  if(set_diena<10){
    lcd.print('0'); }
  lcd.print(set_diena);
    
  lcd.setCursor(16, 2); lcd.print("->");

  if(button!=btn){
    if(btn == 4 && pos == 2){if(set_metai<2030){set_metai++;} btn=0;}
    if(btn == 3 && pos == 2){if(set_metai>2010){set_metai--;} btn=0;}
    if(btn == 4 && pos == 3){if(set_menesis<12){set_menesis++;} btn=0;}
    if(btn == 3 && pos == 3){if(set_menesis>1){set_menesis--;} btn=0;}
    if(btn == 4 && pos == 4){if(set_diena<31){set_diena++;} btn=0;}
    if(btn == 3 && pos == 4){if(set_diena>1){set_diena--;} btn=0;}

    if(btn == 5 && pos == 5){meniu=3; pos=1; btn = 0; lcd.clear();}
    if(btn == 5 && pos == 1){meniu=1, pos = 5; btn = 0; lcd.clear();}
    
    if(btn == 2){if(pos<5){pos++;} btn=0;}
    if(btn == 1){if(pos>1){pos--;} btn=0;}}
    //isvaloma norima eilute
    if(pos != pos_old){
      valyti_eilute(1); pos_old = pos;}
    }

void  nustatyti_savaites_diena(){
  char * const savaites_dienos[7] = {
        "Pirmadienis", "Antradienis", "Treciadienis", "Ketvirtadienis", "Penktadienis", "Sestadienis", "Sekmadienis",     
        };
  lcd.setCursor (3, 0 ); lcd.print("SAVAITES DIENA");
  if(pos==1){lcd.setCursor (0, 1 ); lcd.print("__");}
  if(pos==2){lcd.setCursor (9, 1 ); lcd.print("__");}
  if(pos==3){lcd.setCursor (18, 1 ); lcd.print("__");}
 
  lcd.setCursor(0, 2); lcd.print("<-");
  
  lcd.setCursor(3, 2);
  lcd.print(savaites_dienos[set_savaite-1]);
  
  
  lcd.setCursor(18, 2); lcd.print("[]");       
            
  if(button!=btn){
    if(btn == 4 && pos == 2){if(set_savaite<7){set_savaite++; valyti_eilute(2);} btn=0;}
    if(btn == 3 && pos == 2){if(set_savaite>1){set_savaite--; valyti_eilute(2);} btn=0;}

    if(btn == 5 && pos == 1){meniu=2; pos=5; btn=0; lcd.clear();}
    if(btn == 5 && pos == 3){meniu=4, pos=0; btn = 0; lcd.clear();}
    
    if(btn == 2){if(pos<3){pos++;} btn=0;}
    if(btn == 1){if(pos>1){pos--;} btn=0;}}
    //isvaloma norima eilute
    if(pos != pos_old){
      valyti_eilute(1);
      pos_old = pos;}
  }

////////////////////////////////////////////// PAUKSCIAI ////////////////////////////////////////
void nustatyti_paukscius(){
  pasirinkimas();
  //paukstis = 0;
  //RUSIS
  lcd.setCursor(1, 0);
  lcd.print("#");
  lcd.setCursor(3, 0);
  lcd.print("<- ");
  lcd.print(pauksciai[paukstis]);
  lcd.setCursor(16, 0);
  lcd.print("->");
  //DIENOS
  lcd.setCursor(0, 1);
  lcd.print("Dienos");
  lcd.setCursor(8, 1);
  lcd.print("<- ");
  lcd.setCursor(12, 1);
  lcd.print(dienu_sk);
  lcd.setCursor(16, 1);  
  lcd.print("->");
  //ISJUNGTI vartyma
  lcd.setCursor(0, 2);
  lcd.print("Isj VRT");
  lcd.setCursor(8, 2);
  lcd.print("<- ");
  lcd.setCursor(12, 2);
  lcd.print(isj_vartyma);
  lcd.setCursor(16, 2);  
  lcd.print("->");
  
  //issaugoti
  lcd.setCursor(6, 3);
  lcd.print("ISSAUGOTI []");
  //myktukai
  if(button!=btn){
    if(btn == 3){if(pos<3){pos++;} btn=0;}
    if(btn == 4){if(pos>0){pos--;} btn=0;}
    
    if(btn == 2 && pos == 0){if(paukstis<4){paukstis++; valyti_eilute2(0, 6, 14);} btn=0;}
    if(btn == 1 && pos == 0){if(paukstis>0){paukstis--; valyti_eilute2(0, 6, 14);} btn=0;}
    
    if(btn == 2 && pos == 1){if(dienu_sk<40){dienu_sk++;}  btn=0;}
    if(btn == 1 && pos == 1){if(dienu_sk>15){dienu_sk--;}  btn=0;}

    if(btn == 2 && pos == 2){if(isj_vartyma<40){isj_vartyma++;}  btn=0;}
    if(btn == 1 && pos == 2){if(isj_vartyma>15){isj_vartyma--;}  btn=0;}
    
    if(btn == 5 && pos == 3){meniu = 2; pos=1; btn=0; lcd.clear();}
    if(btn == 5){set_meniu=10; meniu=1; btn = 0; lcd.clear();}}
  }

void irasyti_paukscius(){
  rtc.eeprom_write(PERINIMAS_PAUKSTIS, paukstis);
  rtc.eeprom_write(PERINIMAS_DIENOS, dienu_sk);
  rtc.eeprom_write(VARTYMAS_DIENOS, isj_vartyma);
  }

////////////////////////////////////////////// TEMPERATURA ////////////////////////////////////////////////
void nustatyti_temperatura(){
  pasirinkimas();
  
  //RUSIS, rodo kai nustati kokia veisle perinsi
  lcd.setCursor(5, 0);
  lcd.print(pauksciai[paukstis]);
  //MINIMALI
  lcd.setCursor(0, 1);
  lcd.print("MIN:");
  lcd.setCursor(5, 1);
  lcd.print("<- ");
  lcd.print(mini_temp);
  lcd.setCursor(13, 1);
  lcd.print((char)223);
  lcd.print("C ");
  lcd.print("->");
  //MAXIMALI
  lcd.setCursor(0, 2);
  lcd.print("MAX:");
  lcd.setCursor(5, 2);
  lcd.print("<- ");
  lcd.print(maxi_temp);
  lcd.setCursor(13, 2);
  lcd.print((char)223);
  lcd.print("C ");
  lcd.print("->");
  //issaugoti
  lcd.setCursor(6, 3);
  lcd.print("ISSAUGOTI []");

  //mini_temp = 35.40;
  //maxi_temp = 39.40;
  if(button!=btn){
    //i sonus
    if(btn == 3){if(pos<3){pos++;} btn=0;}
    if(btn == 4){if(pos>1){pos--;} btn=0;}
    //i virsu, apacia
    if(btn == 2 && pos == 2){if(maxi_temp<50){maxi_temp = maxi_temp + 0.1;} btn=0;}
    if(btn == 1 && pos == 2){if(maxi_temp>20){maxi_temp = maxi_temp - 0.1;} btn=0;}
    if(btn == 2 && pos == 1){if(mini_temp<50){mini_temp = mini_temp + 0.1;} btn=0;}
    if(btn == 1 && pos == 1){if(mini_temp>20){mini_temp = mini_temp - 0.1;} btn=0;}
    //issaugoti
    if(btn == 5 && pos == 3){meniu = 2; pos=1; btn=0; lcd.clear();}
    //iseiti 
    if(btn == 5){set_meniu=10; meniu=1; btn = 0; lcd.clear();}}
  }

void irasyti_temperatura(){
  rtc.eeprom_write(TMIN, mini_temp);
  rtc.eeprom_write(TMAX, maxi_temp);
  }

////////////////////////////////////////////// DREGNUMAS ////////////////////////////////////////////////
void nustatyti_dregme(){
  pasirinkimas();
  //RUSIS
  lcd.setCursor(5, 0);
  lcd.print(pauksciai[paukstis]);
  //MINIMALI
  lcd.setCursor(0, 1);
  lcd.print("MIN:");
  lcd.setCursor(7, 1);
  lcd.print("<- ");
  lcd.print(mini_dreg);
  lcd.setCursor(12, 1);
  lcd.print("% ");
  lcd.print("->");
  //MAXIMALI
  lcd.setCursor(0, 2);
  lcd.print("MAX:");
  lcd.setCursor(7, 2);
  lcd.print("<- ");
  lcd.print(maxi_dreg);
  lcd.setCursor(12, 2);  
  lcd.print("% ");
  lcd.print("->");
  //issaugoti
  lcd.setCursor(6, 3);
  lcd.print("ISSAUGOTI []");

  //mini_dreg = 45;
  //maxi_dreg = 75;
  if(button!=btn){
    //i sonus
    if(btn == 3){if(pos<3){pos++;} btn=0;}
    if(btn == 4){if(pos>0){pos--;} btn=0;}
    //i virsu, apacia
    if(btn == 2 && pos == 2){if(maxi_dreg<80){maxi_dreg++;} btn=0;}
    if(btn == 1 && pos == 2){if(maxi_dreg>30){maxi_dreg--;} btn=0;}
    if(btn == 2 && pos == 1){if(mini_dreg<80){mini_dreg++;} btn=0;}
    if(btn == 1 && pos == 1){if(mini_dreg>30){mini_dreg--;} btn=0;}
    //issaugoti
    if(btn == 5 && pos == 3){meniu = 2; pos=1; btn=0; lcd.clear();}
    //iseiti 
    if(btn == 5){set_meniu=10; meniu=1; btn = 0; lcd.clear();}}
  }

void irasyti_dregme(){
  rtc.eeprom_write(DMIN, mini_dreg);
  rtc.eeprom_write(DMAX, maxi_dreg);
  }

///////////////////////////////////////////////// VENTILIATORIUS /////////////////////////
void nustatyti_fan(){
  pasirinkimas();
  //ON / OFF
  lcd.setCursor(0, 0); lcd.print("FAN: ");
  lcd.setCursor(6, 0); lcd.print("<- ");
  lcd.setCursor(10, 0);
  if(fan_power){lcd.print("ON ");}else{lcd.print("OFF");}
  lcd.setCursor(16, 0); lcd.print("->");
  //nustatyti MIN
  lcd.setCursor(0, 1);lcd.print("MIN: ");
  lcd.setCursor(6, 1);lcd.print("<- ");
  lcd.setCursor(10, 1);
  lcd.print(fan_reiksme2*10);
  if(fan_reiksme2!=10){lcd.print(" ");}
  lcd.setCursor(13, 1); lcd.print("% "); lcd.print(" ->");  
  //nustatyti max
  lcd.setCursor(0, 2);lcd.print("MAX: ");
  lcd.setCursor(6, 2); lcd.print("<- ");
  lcd.setCursor(10, 2); lcd.print(fan_reiksme*10);
  if(fan_reiksme!=10){lcd.print(" ");}
  lcd.setCursor(13, 2); lcd.print("% "); lcd.print(" ->");
  //issaugoti
  lcd.setCursor(6, 3); lcd.print("ISSAUGOTI []");

  if(button!=btn){
    //i sonus
    if(btn == 3){if(pos<3){pos++;} btn=0;}
    if(btn == 4){if(pos>1){pos--;} btn=0;}
    //i virsu, apacia
    if(btn == 2 && pos == 0){fan_power = !fan_power; btn=0;}
    if(btn == 1 && pos == 0){fan_power = !fan_power; btn=0;}
    
    if(btn == 2 && pos == 1){if(fan_reiksme2<8){fan_reiksme2++;} btn=0;}
    if(btn == 1 && pos == 1){if(fan_reiksme2>0){fan_reiksme2--;} btn=0;}
    if(btn == 2 && pos == 2){if(fan_reiksme<10){fan_reiksme++;} btn=0;}
    if(btn == 1 && pos == 2){if(fan_reiksme>2){fan_reiksme--;} btn=0;}
    //issaugoti
    if(btn == 5 && pos == 3){meniu = 2; pos=1; btn=0; lcd.clear();}
    //iseiti 
    if(btn == 5){set_meniu=10; meniu=1; btn = 0; lcd.clear();}}
  }
void irasyti_fan(){
  rtc.eeprom_write(FAN, fan_reiksme);
  rtc.eeprom_write(FAN_2, fan_reiksme2);
  rtc.eeprom_write(FAN_POWER, fan_power);
  }

/////////////////////////////////////// KALIBRACIJA ////////////////////////////////////////
void kalibracija(){
  pasirinkimas();

  lcd.setCursor(1, 0);
  lcd.print("DAVIKLIS #1 SHT31");

  lcd.setCursor(1, 1); lcd.print(cel); lcd.print((char)223); lcd.print("C ");
  lcd.setCursor(11, 1); lcd.print(hum); lcd.print("%");
  
  lcd.setCursor(0, 2); lcd.print("TMP: ");
  lcd.setCursor(7, 2); lcd.print("<- ");
  lcd.setCursor(10, 2); lcd.print(sht_t1); lcd.print(" ");
  lcd.setCursor(16, 2); lcd.print("->");
  
  lcd.setCursor(0, 3); lcd.print("DRG: ");
  lcd.setCursor(7, 3); lcd.print("<- ");
  lcd.setCursor(11, 3); lcd.print(sht_dr1); lcd.print(" "); 
  lcd.setCursor(16, 3); lcd.print("->");
  
  //myktukai
  if(button!=btn){
    if(btn == 3){if(pos<4){pos++; if(pos == 4){meniu = 2; pos=2; lcd.clear();}} btn=0;}
    if(btn == 4){if(pos>1){pos--;  if(pos == 1){set_meniu = 10; pos=1; lcd.clear();}} btn=0;}
    
    if(btn == 2 && pos == 2){if(sht_t1<5){sht_t1 = sht_t1 + 0.05;} btn=0;}
    if(btn == 1 && pos == 2){if(sht_t1>-5){sht_t1 = sht_t1 - 0.05;} btn=0;}
    
    if(btn == 2 && pos == 3){if(sht_dr1<15){sht_dr1++;}  btn=0;}
    if(btn == 1 && pos == 3){if(sht_dr1>-15){sht_dr1--;}  btn=0;}

    if(btn == 5){set_meniu=10; meniu=1; btn = 0; lcd.clear();}}
  }

void kalibracija_2(){
  pasirinkimas();
  //RUSIS
  lcd.setCursor(1, 0); lcd.print("DAVIKLIS #2 SHT31");

  lcd.setCursor(1, 1); lcd.print(cel2); lcd.print((char)223); lcd.print("C ");
  lcd.setCursor(11, 1); lcd.print(hum2); lcd.print("%");
  
  lcd.setCursor(0, 2); lcd.print("TMP: "); 
  lcd.setCursor(7, 2); lcd.print("<- ");
  lcd.setCursor(10, 2); lcd.print(sht_t2); lcd.print(" ");
  lcd.setCursor(16, 2); lcd.print("->");
  
  lcd.setCursor(0, 3); lcd.print("DRG: ");
  lcd.setCursor(7, 3); lcd.print("<- ");
  lcd.setCursor(11, 3); lcd.print(sht_dr2); lcd.print(" ");
  lcd.setCursor(16, 3); lcd.print("->");
  
  //myktukai
  if(button!=btn){
    if(btn == 3){if(pos<4){pos++; if(pos == 4){meniu = 3; pos=1; lcd.clear();}} btn=0;}
    if(btn == 4){if(pos>1){pos--;if(pos == 1){meniu = 1; pos=3; lcd.clear();}} btn=0;}
    
    if(btn == 2 && pos == 2){if(sht_t2<5){sht_t2 = sht_t2 + 0.05;} btn=0;}
    if(btn == 1 && pos == 2){if(sht_t2>-5){sht_t2 = sht_t2 - 0.05;} btn=0;}
    
    if(btn == 2 && pos == 3){if(sht_dr2<15){sht_dr2++;}  btn=0;}
    if(btn == 1 && pos == 3){if(sht_dr2>-15){sht_dr2--;}  btn=0;}
    
    if(btn == 5 && pos == 3){meniu = 2; pos=1; btn=0; lcd.clear();}
    if(btn == 5){set_meniu=10; meniu=1; btn = 0; lcd.clear();}}
  }
  
  void issaugoti_kalibracija(){
    rtc.eeprom_write(SHT_D1, sht_dr1);
    rtc.eeprom_write(SHT_D2, sht_dr2);
    rtc.eeprom_write(SHT_T1, sht_t1);
    rtc.eeprom_write(SHT_T2, sht_t2);
    }

  void irasyti_kalibracija(){
    pasirinkimas();
    lcd.setCursor(0, 0); lcd.print("Irasyti pakeitimus?");
    lcd.setCursor(16, 1); lcd.print("NE");
    lcd.setCursor(14, 2); lcd.print("TAIP");
    //myktukai
  if(button!=btn){
    if(btn == 3){if(pos<2){pos++;} btn=0;}
    if(btn == 4){if(pos>0){pos--; if(pos == 0){meniu = 1; pos=3; lcd.clear();}} btn=0;}
    //iseiti
    if(btn == 5 && pos == 1){set_meniu = 10; btn=0; lcd.clear();}
    //issaugoti
    if(btn == 5 && pos == 2){meniu = 4; issaugoti_kalibracija(); btn=0; lcd.clear();}}
    }

//////////////////////////////////// STARTUOJAM, PALEIDIMAS ////////////////////////////////////////
void startas_inkubatorius(){
  pasirinkimas();
  
  lcd.setCursor(4, 0);
  lcd.print("STARTUOJAM ?");

  lcd.setCursor(0, 1);
  lcd.print("Ijungti");
  lcd.setCursor(8, 1);
  lcd.print("<- ");
  if(startas){lcd.setCursor(11, 1); lcd.print("TAIP");}else{lcd.setCursor(11, 1); lcd.print(" NE ");}
  lcd.setCursor(16, 1);  
  lcd.print("->");

  lcd.setCursor(0, 2);
  lcd.print("Garsas");
  lcd.setCursor(8, 2);
  lcd.print("<- ");
  if(garsas){lcd.setCursor(11, 2); lcd.print("TAIP");}else{lcd.setCursor(11, 2); lcd.print(" NE ");}
  lcd.setCursor(16, 2);  
  lcd.print("->");
  
  //issaugoti
  lcd.setCursor(6, 3);
  lcd.print("ISSAUGOTI []");

    //myktukai
  if(button!=btn){
    if(btn == 2 && pos == 1){startas = !startas; btn=0;}
    if(btn == 1 && pos == 1){startas = !startas; btn=0;}
    if(btn == 2 && pos == 2){garsas = !garsas;  btn=0;}
    if(btn == 1 && pos == 2){garsas = !garsas;  btn=0;}
    if(btn == 3){if(pos<3){pos++;} btn=0;}
    if(btn == 4){if(pos>1){pos--;} btn=0;}
    if(btn == 5 && pos == 3){meniu = 2; pos=1; btn=0; lcd.clear();}
    if(btn == 5){set_meniu=10; meniu=1; btn = 0; lcd.clear();}}
}

void startas_irasyti(){
  if(startas){
   rtc.eeprom_write(PERINIMAS_POWER, startas);
   rtc.eeprom_write(PRADZIA_METAI, rtc.year());
   rtc.eeprom_write(PRADZIA_MENUO, rtc.month());
   rtc.eeprom_write(PRADZIA_DIENA, rtc.day());
   rtc.eeprom_write(GARSAS_POWER, garsas);
   pradzia_metai = rtc.year(); pradzia_menuo = rtc.month(); pradzia_diena = rtc.day();
  }else{
    rtc.eeprom_write(PERINIMAS_POWER, startas);
    rtc.eeprom_write(PERINIMAS_POWER, startas);
    rtc.eeprom_write(PRADZIA_METAI, 0);
    rtc.eeprom_write(PRADZIA_MENUO, 0);
    rtc.eeprom_write(PRADZIA_DIENA, 0);
    rtc.eeprom_write(GARSAS_POWER, 0);
    pradzia_metai = 0; pradzia_menuo = 0; pradzia_diena = 0;
  }
}

//////////////////////////////////////////////////////////// KITI /////////////////////////////////////////
void nustatyti_kiti(){
  pasirinkimas();
  //ON / OFF
  lcd.setCursor(0, 0);
  lcd.print("Sildymas");
  lcd.setCursor(9, 0);
  lcd.print("<- ");
  lcd.setCursor(12, 0);
  if(sildymas_power){lcd.print("ON ");}else{lcd.print("OFF");}
  lcd.setCursor(16, 0);  
  lcd.print("->");

  lcd.setCursor(0, 1);
  lcd.print("Vanduo");
  lcd.setCursor(9, 1);
  lcd.print("<- ");
  lcd.setCursor(12, 1);
  if(vanduo_power){lcd.print("ON ");}else{lcd.print("OFF");}
  lcd.setCursor(16, 1);  
  lcd.print("->");
  
  //issaugoti
  lcd.setCursor(6, 3);
  lcd.print("ISSAUGOTI []");

  //fan = 2;
  if(button!=btn){
    //i sonus
    if(btn == 3){if(pos<3){pos++;} btn=0;}
    if(btn == 4){if(pos>0){pos--;} btn=0;}
    //i virsu, apacia
    if(btn == 2 && pos == 0){sildymas_power = !sildymas_power; btn=0;}
    if(btn == 1 && pos == 0){sildymas_power = !sildymas_power; btn=0;}
    if(btn == 2 && pos == 1){vanduo_power = !vanduo_power; btn=0;}
    if(btn == 1 && pos == 1){vanduo_power = !vanduo_power; btn=0;}
    //issaugoti
    if(btn == 5 && pos == 3){meniu = 2; pos=1; btn=0; lcd.clear();}
    //iseiti 
    if(btn == 5){set_meniu=10; meniu=1; btn = 0; lcd.clear();}}
}
void irasyti_kiti(){
  rtc.eeprom_write(VANDUO_POWER, vanduo_power);
  rtc.eeprom_write(SILDYMAS_POWER, sildymas_power);
}

/////////////////////////////////////////////////// VARTYMAS //////////////////////////////////////////
void nustatyti_vartyma(){
  pasirinkimas();
  //ON / OFF
  lcd.setCursor(0, 0); lcd.print("VRT: ");
  lcd.setCursor(6, 0); lcd.print("<- ");
  lcd.setCursor(10, 0);
  if(vartymas_power){lcd.print("ON ");}else{lcd.print("OFF");}
  lcd.setCursor(16, 0); lcd.print("->");
  //nustatyti MIN
  lcd.setCursor(0, 1);lcd.print(" ON: ");
  lcd.setCursor(6, 1);lcd.print("<- ");
  lcd.setCursor(10, 1);
  if(vartymas_min<10){lcd.print("0");}
  lcd.print(vartymas_min);
  lcd.setCursor(13, 1); lcd.print("m "); lcd.print(" ->");  
  //nustatyti max
  lcd.setCursor(0, 2);lcd.print("OFF: ");
  lcd.setCursor(6, 2); lcd.print("<- ");
  lcd.setCursor(10, 2);
  if(vartymas_max<10){lcd.print("0");}
  lcd.print(vartymas_max);
  lcd.setCursor(13, 2); lcd.print("m "); lcd.print(" ->");
  //issaugoti
  lcd.setCursor(6, 3); lcd.print("ISSAUGOTI []");

  if(button!=btn){
    //i sonus
    if(btn == 3){if(pos<3){pos++;} btn=0;}
    if(btn == 4){if(pos>1){pos--;} btn=0;}
    //i virsu, apacia
    if(btn == 2 && pos == 0){vartymas_power = !vartymas_power; btn=0;}
    if(btn == 1 && pos == 0){vartymas_power = !vartymas_power; btn=0;}
    
    if(btn == 2 && pos == 1){if(vartymas_min<10){vartymas_min++;} btn=0;}
    if(btn == 1 && pos == 1){if(vartymas_min>2){vartymas_min--;} btn=0;}
    if(btn == 2 && pos == 2){if(vartymas_max<60){vartymas_max++;} btn=0;}
    if(btn == 1 && pos == 2){if(vartymas_max>15){vartymas_max--;} btn=0;}
    //issaugoti
    if(btn == 5 && pos == 3){meniu = 2; pos=1; btn=0; lcd.clear();}
    //iseiti 
    if(btn == 5){set_meniu=10; meniu=1; btn = 0; lcd.clear();}}
  }
void irasyti_vartyma(){
  rtc.eeprom_write(VARTYMAS_POWER, vartymas_power);
  rtc.eeprom_write(VARTYMAS_MIN, vartymas_min);
  rtc.eeprom_write(VARTYMAS_MAX, vartymas_max);
  }
