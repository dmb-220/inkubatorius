//EEPROM atminties adresai
#define TMIN              0  //FLOAT 32bit, uzima 4 vietas
#define TMAX              4  //FLOAT 32bit, uzima 4 vietas
//dregme
#define DMIN              8  //CHAR 8bit, uzima 1 vietas
#define DMAX              9  //CHAR 8bit, uzima 1 vietas
//ventiliatorius
#define FAN_POWER         11 //CHAR 8bit, uzima 1 vietas
#define FAN               12 //CHAR 8bit, uzima 1 vietas
//vandens padavimas
#define VANDUO_POWER      13 //CHAR 8bit, uzima 1 vietas
//sildimo maitinimas
#define SILDYMAS_POWER    14 //CHAR 8bit, uzima 1 vietas
//kiausiniu vartymas
#define VARTYMAS_POWER    15 //CHAR 8bit, uzima 1 vietas
//perinimas ijungtas
#define PERINIMAS_POWER   16 //CHAR 8bit, uzima 1 vietas
#define PRADZIA_METAI     17 //CHAR 8bit, uzima 1 vietas
#define PRADZIA_MENUO     18 //CHAR 8bit, uzima 1 vietas
#define PRADZIA_DIENA     19 //CHAR 8bit, uzima 1 vietas
//Perinimo dienu skaicius
#define PERINIMAS_PAUKSTIS  20 //CHAR 8bit, uzima 1 vietas
#define PERINIMAS_DIENOS    21 //CHAR 8bit, uzima 1 vietas
#define VARTYMAS_DIENOS     22 //CHAR 8bit, uzima 1 vietas
//KAlibracija
#define SHT_D1              23  //INT 16bit, uzima 2 vietas
#define SHT_D2              25  //INT 16bit, uzima 2 vietas
#define SHT_T1              27  //FLOAT 32bit, uzima 4 vietas
#define SHT_T2              31  //FLOAT 32bit, uzima 4 vietas
//garsas ijungtas
#define GARSAS_POWER        35 //CHAR 8bit, uzima 1 vietas
//VEntil. min nustatymas
#define FAN_2               36 //CHAR 8bit, uzima 1 vietas
//VArtymas
#define VARTYMAS_MIN        37 //CHAR 8bit, uzima 1 vietas
#define VARTYMAS_MAX        38 //CHAR 8bit, uzima 1 vietas

const char* meniu_list[4][3] = {
  {"Pauksciai","Temperatura","Dregnumas"},
  {"Ventiliatorius","Kalibravimas","Kiti nustatymai"},
  {"Paleidimas","Laikas ir Data", "Vartymas"},
  {"Atgal","",""}};

char * const pauksciai[5] = {
        "Vistos", "Antys", "Zasys", "Kalakutai", "Putpeles",     
        };
char * const menesiai[12] = {"31", "28", "31", "30", "31", "30","31", "31", "30", "31", "30", "31"};
//Kintamieji
unsigned int button, btn, abutton;
//meniu kintamieji
unsigned char meniu = 0, set_meniu = 0;
//meniu uzpildymas is masyvo
char eile = 0, vieta = 0;
unsigned char pos = 0, pos_old = 0, sk = 0;
//uzdelsimo kintamieji
unsigned long readMillis, previousMillis, timeMillis, inkuMillis, piestiMillis;
//davikliu kintamieji
float t = 0, h = 0, cel = 0, hum = 0;
float t2 = 0, h2 = 0, cel2 = 0, hum2 = 0;
//laikrodzio kintamieji
unsigned char hours, minute, second;
unsigned char set_hours = 12, set_minutes = 30, set_second = 0, set_menesis, set_diena, set_savaite;
//nes 2018 i char netelpa
int set_metai;
//ventiliatorius, sildymas
unsigned char fan_power = 0, fan = 0, fan_reiksme = 0, fan_reiksme2 = 0, fan_speed = 0, f_reik = 0;
//Temperaturos, dregmes, issaugotos perinimui
float mini_temp = 0, maxi_temp = 0;
unsigned char maxi_dreg = 0, mini_dreg = 0;
//kitamieji, temperaturai palaikyti, vartymas, sildymas, vanduo;
unsigned char tempa = 1, vartymas = 0, vartymas_power = 0, vartymas_min = 0, vartymas_max = 0, sildymas = 0, sildymas_power, vanduo = 0, vanduo_power = 0;
unsigned int vartymas_sk = 0;
//inkubatoriaus paleidimas
unsigned char startas = 0, pradzia_metai = 0, pradzia_menuo = 0, pradzia_diena = 0, liko = 0, praejo = 0, garsas = 0;
//davikliu temperaturu, dregmes kalibravimas
float sht_t1 = 0.0, sht_t2 = 0.0;
int sht_dr1 = 0, sht_dr2 = 0;
//pauksciai
unsigned char paukstis, dienu_sk = 21, isj_vartyma = 18;
//MAX, MIN
float max_temp = 0, min_temp = 50;
//kiti kintamieji
unsigned char first_time;
//elektra
unsigned int el_sk = 0, el_min = 0, el_val = 0, el_day = 0; 

void setRTCTime(){
  rtc.set(set_second, set_minutes, set_hours, set_savaite, set_diena, set_menesis, set_metai-2000);
  //RTCLib::set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
}

void pwm_init(){
  OCR0A = 0;
  TCCR0A |= (1 << COM0A1);
  TCCR0A |= (1 << WGM01) | (1 << WGM00);
  TCCR0B |= (1 << CS01);
}

void pasirinkimas(){
  for(int i=0; i<=3; i++){
    if(i == pos){
      lcd.setCursor(19,i);
      lcd.print((char)255);}else{
        lcd.setCursor(19,i);
        lcd.print(" ");
    }
  }
}

void elektra(){
  //skaisciuojam kiek laiko ijungtas buna sildytuvas
  if(sildymas){el_sk++;}
  if(el_sk>59){el_min++; el_sk = 0;}   
  if(el_min>59){el_val++; el_min = 0;}
  if(el_val>24){el_day++; el_val = 0;}  
  }
//priskiriamos reiksmes jei norima keisti laiko nustatymus
void set_time(){
  //LAikas
  set_second = rtc.second();
  set_hours = rtc.hour();
  set_minutes = rtc.minute();
  //DATA
  set_metai = rtc.year()+2000;
  set_menesis = rtc.month();
  set_diena = rtc.day();
  set_savaite = rtc.dayOfWeek();
}

//meniu langas, pasirinkimas
void meniu_sarasas(){
  lcd.setCursor (5, 0 );
  lcd.print("NUSTATYMAI");
  
  for (int i=0; i <= 2; i++){
    lcd.setCursor (0, i+1 );
    if(vieta == i){
      lcd.print("> ");
    }else{lcd.print("  ");}
    lcd.print(meniu_list[eile][i]);
    }
    
   //Myktukai
  if(button!=btn){
    if(btn == 5){
       //laikas ir data  
      if(eile == 2 && vieta == 1){
        set_meniu=2; meniu=1; pos=1; btn = 0; set_time(); lcd.clear();} 
      //Temperatura  
      if(eile == 0 && vieta == 1){
        set_meniu=3; meniu=1; pos=1; btn = 0; lcd.clear();} 
      //Dregme 
      if(eile == 0 && vieta == 2){
        set_meniu=4; meniu=1; pos=1; btn = 0; lcd.clear();} 
      //Ventiliatorius  
      if(eile == 1 && vieta == 0){
        set_meniu=5; meniu=1; pos=0; btn = 0; lcd.clear();} 
        //Kalibravimas 
      if(eile == 1 && vieta == 1){
        set_meniu=6; meniu=1; pos=2; btn = 0; lcd.clear();}   
        //Pauksciai
      if(eile == 0 && vieta == 0){
        set_meniu=7; meniu=1; btn = 0; lcd.clear();} 
        //Paleidimas  
      if(eile == 2 && vieta == 0){
        set_meniu=8; meniu=1; pos=1; btn = 0;lcd.clear();} 
      //Kiti  
      if(eile == 1 && vieta == 2){
        set_meniu=9; meniu=1;  pos=0; btn = 0;  lcd.clear();}
      //VArtymas
      if(eile == 2 && vieta == 2){
        set_meniu=11; meniu=1; pos = 0; btn = 0; lcd.clear();}  
      //Atgal
      if(eile == 3 && vieta == 0){
        set_meniu=1; meniu=0; btn = 0; vieta = 0; eile = 0; lcd.clear();}
        }
    if(btn==3){
      if(vieta<3){
        //toks nedidelis apejimas, jei ne pilnas meniu masyvas :D
        if(eile != 3){vieta++;}else{eile = 0; vieta = 0;}
        /*vieta++;*/ btn=0;
        if(vieta == 3 && eile == 0){eile = 1; vieta = 0; lcd.clear();}      
        if(vieta == 3 && eile == 1){eile = 2; vieta = 0; lcd.clear();}
        if(vieta == 3 && eile == 2){eile = 3; vieta = 0; lcd.clear();}              
        if(vieta == 3 && eile == 3){eile = 0; vieta = 0; lcd.clear();}
        }}
    if(btn==4){
      if(vieta>-1){
        vieta--; btn=0;
        if(vieta == -1 && eile == 2){eile = 1; vieta = 2; lcd.clear();}
        if(vieta == -1 && eile == 1){eile = 0; vieta = 2; lcd.clear();}
        if(vieta == -1 && eile == 0){eile = 3; vieta = 0; lcd.clear();}       
        if(vieta == -1 && eile == 3){eile = 2; vieta = 2; lcd.clear();}
        }}
        } 
}

void elektra_rodyti(){
  lcd.setCursor(0, 0); lcd.print("VRT: ");
  lcd.print(vartymas_sk); lcd.print("s");
  lcd.setCursor(0, 1); lcd.print("ON: ");
  lcd.print(vartymas_min*60); lcd.print("s");
  lcd.setCursor(10, 1); lcd.print("OFF: ");
  lcd.print(vartymas_max*60); lcd.print("s");
  
  lcd.setCursor(0, 3); lcd.print("SLD: ");
  if(el_day<10){lcd.print("0");}
  lcd.print(el_day); lcd.print(" - ");
  if(el_val<10){lcd.print("0");}
  lcd.print(el_val); lcd.print(":"); 
  if(el_min<10){lcd.print("0");}
  lcd.print(el_min); lcd.print(":");
  if(el_sk<10){lcd.print("0");}
  lcd.print(el_sk);
  
  if(button!=btn){if(btn==5){meniu = 0; btn=0; lcd.clear();}}
}

void temperatura_dregme(){
  lcd.setCursor(0, 0);
  lcd.print("SHT31");
  lcd.setCursor (6, 0);
  lcd.print(cel);
  lcd.print((char)223);
  lcd.print("C ");
  lcd.setCursor (14, 0);
  lcd.print(hum);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("SHT31");
  lcd.setCursor (6, 1);
  lcd.print(cel2);
  lcd.print((char)223);
  lcd.print("C ");
  lcd.setCursor (14, 1);
  lcd.print(hum2);
  lcd.print("%");
  
  lcd.setCursor(0, 3);
  lcd.print("MIN ");
  lcd.print(min_temp);
  lcd.setCursor(11, 3);
  lcd.print("MAX ");
  lcd.print(max_temp);
  //myktukai
  if(button!=btn){
    if(btn==5){meniu = 0; btn=0; lcd.clear();}}
}

void laikrodis(){
  lcd.setCursor(0, 0); lcd.print(rtc.year()+2000); lcd.print("-");
  if(rtc.month()<10){lcd.print("0");}
  lcd.print(rtc.month());
  lcd.print("-");
  if(rtc.day()<10){lcd.print("0");}
  lcd.print(rtc.day());
  lcd.print("  ");
  if(hours<10){lcd.print("0");}
  lcd.print(hours);
  lcd.print(":");
  if(minute<10){lcd.print("0");}
  lcd.print(minute);
  lcd.print(":");
  if(second<10){lcd.print("0");}
  lcd.print(second);

  if(startas){
    lcd.setCursor(0,1); lcd.print("LIKO:");  lcd.print(dienu_sk - praejo); 
    lcd.setCursor(10,1); lcd.print("PRAEJO:");  lcd.print(praejo);
    lcd.setCursor(0,2); lcd.print("Ijungtas:");
    lcd.setCursor(10,2); lcd.print(pradzia_metai+2000); lcd.print("-");
    if(pradzia_menuo<10){lcd.print("0");} lcd.print(pradzia_menuo); lcd.print("-"); 
    if(pradzia_diena<10){lcd.print("0");} lcd.print(pradzia_diena);
    if(praejo >= isj_vartyma){lcd.setCursor(0,3); lcd.print("Vartymas isjungtas!"); }
    }else{lcd.setCursor(0,1); lcd.print("Inkubatorius isjung.");}

  //myktukai
  if(button!=btn){
    if(btn==5){meniu = 0; btn=0; lcd.clear();}}
}

void pradinis(){
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(cel);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor (0, 1 );
  lcd.print("RH:");
  lcd.print(h);
  lcd.print("%");
  //FAN , SILDYMAS
  lcd.setCursor(11, 0);
  lcd.print("FAN: ");
  if(fan){lcd.print("ON ");}else{lcd.print("OFF");}
  lcd.setCursor(11, 1);
  lcd.print("VND: ");
  if(vanduo){lcd.print("ON ");}else{lcd.print("OFF");}
  lcd.setCursor(11, 2);
  lcd.print("SLD: ");
  if(sildymas){lcd.print("ON ");}else{lcd.print("OFF");}
  lcd.setCursor(11, 3);
  lcd.print("VRT: ");
  if(vartymas){lcd.print("ON ");}else{lcd.print("OFF");}
  
  //myktukai
  if(button!=btn){
    if(btn==5){set_meniu=10; btn = 0; lcd.clear();}
    if(btn==1){meniu = 3; btn=0; lcd.clear();}
    if(btn==2){meniu = 4; btn=0; lcd.clear();}
    if(btn==4){meniu = 1; btn=0; lcd.clear();}
    if(btn==3){meniu = 2; btn=0; lcd.clear();}}
}

void funkcija(){
  lcd.setCursor(0, 0); lcd.print("Tmin"); lcd.print(mini_temp);
  lcd.setCursor(10, 0); lcd.print("Tmax"); lcd.print(maxi_temp);
  lcd.setCursor(0, 1); lcd.print("Dmin: "); lcd.print(mini_dreg);
  lcd.setCursor(10, 1); lcd.print("Dmax: "); lcd.print(maxi_dreg);
  lcd.setCursor(0, 2); lcd.print(pauksciai[paukstis]);
  lcd.setCursor(12, 2); lcd.print("GRS: "); if(garsas){lcd.print("ON ");}else{lcd.print("OFF");}
  lcd.setCursor(0, 3); lcd.print("RPM: ");
  lcd.print(f_reik*10);
    if(f_reik!=10){lcd.print(" ");}
  lcd.print("%");
    
    if(button!=btn){
      if(btn==5){meniu = 0; btn=0; lcd.clear();}}
}

