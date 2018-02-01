#include <avr/pgmspace.h>
//#include "pitches.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Adafruit_SHT31.h"
#include "uRTCLib.h"

//Pajungimas
//Buzzer
#define BUZZER_PIN    PD3
//Reles
#define RELAY_PIN_1   PD5 //sildytuvas
#define RELAY_PIN_2   PD4 //vanduo turetu buti
#define RELAY_PIN_3   PC1 //vartymas
#define RELAY_PIN_4   PC2 //ventiliatorius
//Myktukai
#define ADC_KEYPAD    PC0
//FAN
#define FAN_PWM       PD6
#define FAN_SENSE     PD7
//DHT22
#define DHT22         PB4


//uRTCLib rtc;
uRTCLib rtc(0x68, 0x56);
LiquidCrystal_I2C lcd(0x27,20,4);
Adafruit_SHT31 sht31 = Adafruit_SHT31();

//Mano library
#include "valdymas.h"
#include "adc_key.h"
#include "lcd_function.h"


void setup(void) {
  //Serial.begin(9600);
  InitADC();
  Wire.begin();
  //ijungiami portai
  DDRD|=((1 << BUZZER_PIN) | (1 << RELAY_PIN_1) | (1 << RELAY_PIN_2) | (1 << FAN_PWM) | (1 << FAN_SENSE));
  DDRC|=((1 << RELAY_PIN_3) | (1 << RELAY_PIN_4));
  //isjungiamos reles
  PORTD|=((1 << RELAY_PIN_1) | (1 << RELAY_PIN_2));
  PORTC|=((1 << RELAY_PIN_3) | (1 << RELAY_PIN_4));
  
  pwm_init();
  lcd.init();
  lcd.backlight();
  sht31.begin(0x44);
  nuskaityti();
  //nustatom i nuli, kad neatliktu tam tikru veiksmu, kol nepasikeicia busena
  first_time = 0;
}

void loop(void) {  
//TIMER kuris padeda atvaizdavimui, kad kazkas mirgsetu ir pan
  /*unsigned long skMillis = millis();
  if(skMillis - skaiciuotiMillis >= 1000){
    sk++; skaiciuotiMillis = skMillis;}*/
      
  //Nuskaitomas ADC KEYPAD
  unsigned long ADC_Millis = millis();
  if(ADC_Millis - previousMillis >= 100){
    previousMillis = ADC_Millis;
    read_key();
  }

  //Nuskaitomi temperturos ir dregmes davikliai
  unsigned long Sensor_Millis = millis();
  if(Sensor_Millis - readMillis >= 1000){
    readMillis = Sensor_Millis;
    //SHT3X daviklis
  t = sht31.readTemperature();
  h = sht31.readHumidity();
  hum = h + sht_dr1;
  cel = t + sht_t1;
  hum2 = h2 + sht_dr2;
  cel2 = t2 + sht_t2;
  }

//Nuskaitomi laikrodis davikliai
  unsigned long DS3231_Millis = millis();
  if(DS3231_Millis - timeMillis >= 500){
    timeMillis = DS3231_Millis;
    rtc.refresh();
    hours = rtc.hour();   
    minute = rtc.minute();
    second = rtc.second();
  }
//////////////////////////////////////////////////////////Piesiamas meniu///////////////////////////////////////
  unsigned long LCD_Millis = millis();
  if(LCD_Millis - piestiMillis >= 200){
    piestiMillis = LCD_Millis;
    
  switch (set_meniu) {
  //pagrindinis langas, HOME
  case 1:
  switch (meniu){
    case 1: elektra_rodyti(); break;
    case 2: temperatura_dregme(); break;
    case 3: laikrodis(); break;
    case 4: funkcija(); break;
    default: pradinis(); break;
    }
  break;
  //Laikas ir data
  case 2:
  switch (meniu){
    case 1: nustatyti_laika(); break;
    case 2: nustatyti_data(); break;
    case 3: nustatyti_savaites_diena(); break;
    case 4: setRTCTime(); meniu = 5; break;
    case 5: issaugota(); break;
    default:
    lcd.setCursor (7, 0 );
    lcd.print("LAIKAS");
    lcd.setCursor (9, 1 );
    lcd.print("IR");
    lcd.setCursor (8, 3 );
    lcd.print("DATA");
    break;
  }
  break;
  //Temperatura
  case 3:
  switch (meniu){
    case 1: nustatyti_temperatura(); break;
    case 2: irasyti_temperatura(); meniu = 3;  break;
    case 3: issaugota(); break;
    default:
    lcd.setCursor (4, 1 );
    lcd.print("TEMPERATURA");
    break;
  }
  break;
  //Dregnumas
  case 4:
  switch (meniu){
    case 1: nustatyti_dregme(); break;
    case 2: irasyti_dregme(); meniu = 3;  break;
    case 3: issaugota(); break;
    default:
    lcd.setCursor (5, 1 );
    lcd.print("DREGNUMAS");
    break;
  }
  break;
  //ventiliatorius
  case 5:
  switch (meniu){
    case 1: nustatyti_fan(); break;
    case 2: irasyti_fan(); meniu = 3;  break;
    case 3: issaugota(); break;
    default:
    lcd.setCursor (3, 1 );
    lcd.print("VENTILIATORIUS");
    break;
  }
  break;
   //kalibravimas
  case 6:
  switch (meniu){
    case 1: kalibracija(); break;
    case 2: kalibracija_2(); break;
    case 3: irasyti_kalibracija(); break;
    case 4: issaugota(); break;
    default:
    lcd.setCursor (4, 1 );
    lcd.print("KALIBRAVIMAS");
    break;
  }
  break;
  //Pauksciai
  case 7:
  switch (meniu){
    case 1: nustatyti_paukscius(); break;
    case 2: irasyti_paukscius(); meniu = 3; break;
    case 3: issaugota(); break;
    default:
    lcd.setCursor (5, 1 );
    lcd.print("PAUKSCIAI");
    break;
  }
  break;
  //Paleidimas
  case 8:
  switch (meniu){
    case 1: startas_inkubatorius(); break;
    case 2: startas_irasyti(); meniu = 3; break;
    case 3: issaugota(); break;
    default:
    lcd.setCursor (6, 1 );
    lcd.print("STARTAS");
    break;
  }
  break;
  //Kiti
  case 9:
    switch (meniu){
    case 1: nustatyti_kiti(); break;
    case 2: irasyti_kiti(); meniu = 3;  break;
    case 3: issaugota(); break;
    default:
    lcd.setCursor (2, 1 );
    lcd.print("KITI NUSTATYMAI");
    break;
  }
  break;
  //.....
  //Meniu langas
  case 10: meniu_sarasas(); break;
  //VARTYMAS
  case 11:
    switch (meniu){
    case 1: nustatyti_vartyma(); break;
    case 2: irasyti_vartyma(); meniu = 3; break;
    case 3: issaugota(); break;
    default:
    lcd.setCursor (6, 1 );
    lcd.print("VARTYMAS");
    break;
  }
  break;
 
  //Pasisveikininimas
  default:
  lcd.setCursor (4, 0 );
  lcd.print("INKUBATORIUS");
  lcd.setCursor (4, 1 );
  lcd.print("32 kiausiniu");
  lcd.setCursor (4, 3 );
  lcd.print("DMB-220 2018");
  //myktukai
  if(button!=btn){
     if(btn==5){
       set_meniu=1; btn = 0; lcd.clear();}}  
  break;
  }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////// INKUBATORIAU LOGIKA //////////////////////////////////
unsigned long INK_Millis = millis();
if(INK_Millis - inkuMillis >= 1000){
  inkuMillis = INK_Millis;
  vartymas_sk++;
  //skaiciuojam kiek laiko praejo
    if(pradzia_menuo != rtc.month()){
      praejo = praejo + rtc.day();
      praejo = menesiai[rtc.month()] - pradzia_diena;  
      }else{
        if(pradzia_diena != rtc.day()){
           praejo = rtc.day() - pradzia_diena;  
        }else{praejo = 0;}}
        
  //tikrinam ar inkubatorius ijungtas
  if(startas){
    //skaisciuojam kiek laiko ijungtas buna sildytuvas
    elektra();   
    //ijungiam ventiliatoriu, jei isjungtas
    if(fan_power){
        //ijungiam
        PORTC&=~(1 << RELAY_PIN_4); fan = 1;
        }else{
          //jei isjungtas nustatymuose
          PORTC|=(1 << RELAY_PIN_4); fan = 0;}
          
       //issaugojam dizdziausia ir maziausia reiksmes
       //dar galim i eeprom irasyt, tada gali nors ir menesio matyt kaip laikosi
       if(first_time){
         if(cel>max_temp){max_temp = cel;}
         if(cel<min_temp){min_temp = cel;}}
  
       //Ventiliatoriu galima pasidaryt kad suktusi pagal temperaturos skirtuma
       //if(sildymas){float mx_temp = maxi_temp - cell;}
       //Ijungiamas ventiliatorius
       fan_speed = map(f_reik, 0, 10, 0, 255);
       OCR0A = fan_speed;

       //jei temperatura per didele arba per maza
       if(garsas && first_time){
       if(cel>=maxi_temp+0.1){tone(3, 440, 100);}else{noTone(3);}
       if(cel<=mini_temp-0.1){tone(3, 880, 100);}else{noTone(3);}}
       
      //jei tempertura nukrepta zemiau MIN
      if(mini_temp >= cel && tempa == 1){
        //ijungiam rele vel sildyti
        PORTD&=~(1 << RELAY_PIN_1);
        sildymas = 1; f_reik = fan_reiksme; tempa = 0;
      }
      //jei temperatura pakyla virs MAX 
      if(maxi_temp <= cel && tempa == 0){
        //isjungiam rele
        PORTD|=(1 << RELAY_PIN_1);
        sildymas = 0; f_reik = fan_reiksme2; tempa = 1;
        //Riba pasiekata, gali atlikti jau darbus
        if(!first_time){first_time = 1;}
      }

      //isjungiam vartymas, kai praeina nurodytas kiekis dienu
     if(vartymas_power && praejo < isj_vartyma){
      //vartymas jei isjungtas
      if(vartymas == 0 && vartymas_sk == vartymas_max*60){
        vartymas_sk = 0;
        PORTC&=~(1 << RELAY_PIN_3);
        vartymas = 1;
        }
     //vartymas ijungimas   
     if(vartymas == 1 && vartymas_sk == vartymas_min*60){
        vartymas_sk = 0;
        PORTC|=(1 << RELAY_PIN_3);
        vartymas = 0;
        }
      }else{
        vartymas_sk = 0;
        PORTC|=(1 << RELAY_PIN_3);
        vartymas = 0;
        }
  }else{
    //isjungiam ventiliatoriu
    PORTC|=(1 << RELAY_PIN_4);
    fan = 0;
    //isjungiam sildima jei ijungtas
    PORTD|=(1 << RELAY_PIN_1);
    sildymas = 0; f_reik = 2; tempa = 1;
    //vartymas, isjungiam, jei ijungtas
    vartymas_sk = 0;
    PORTC|=(1 << RELAY_PIN_3);
    vartymas = 0;
    }
  }
}
