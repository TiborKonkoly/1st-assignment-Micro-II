// MQ-2 plynovy senzor

#include <LiquidCrystal.h>             // zadefinujem si kniznicu pre lcd display
LiquidCrystal lcd(2, 3, 11, 10, 9, 8); // inicializacia pinov pre lcd display

#define digital 4                    // pin digitalneho vstupu
#define analog A0                    // pin analogoveho vstupu
int hodnota_plynu_analog = 0;        // premenne na citanie hodnoty senzora
unsigned long cas;                   // de finujem si premenne pre millis()- arduino hodinky
int percenta=0;

void setup() {
  lcd.begin(16, 2);                   // nastavim si lcd display- 16 stlpcov a 2 riadky
  Serial.begin(9600);                 // nastavenie rychlosti seriovej komunikacie
  pinMode(digital, INPUT);           // zadefinovanie pinov ako vstup
  pinMode(analog, INPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(12,OUTPUT);
}



void loop(){
  
 cas=millis();
  if ( cas > 180000 && cas < 181000){                             // ak uplynula odporucana doba potrebna na zohriatie senzora program nas upozorni
    Serial.println("-----UPLYNULA DOBA ZOHRIATIA-----");
  }
  
  hodnota_plynu_analog = analogRead(analog);
  Serial.print("Analogova hodnota senzora:   ");   // vypiseme hodnoty na serial monitor aj analogove aj v % - aby som dokazal vypisat v percentach musim prepocita5 analog -> %)
  Serial.print(hodnota_plynu_analog);
  Serial.print(" v percentach:  ");
  percenta=map(hodnota_plynu_analog, 0, 1023, 0, 100);  // prepocet z analog na %
  Serial.print(percenta);
  Serial.println("%");
  delay(1000);

  // upozornenie na vysoku koncentraciu plynu

  if(hodnota_plynu_analog >= 307){     // pri koncentraci 30% a viac sa zapne zelena dida
    digitalWrite(5,HIGH);}
   else{digitalWrite (5,LOW);}

    if (hodnota_plynu_analog >= 409){    // pri koncentracii  40% a viac sa zapne aj zlta dioda
    digitalWrite(6,HIGH);}
   else{digitalWrite (6,LOW);}
   
    if(hodnota_plynu_analog >= 511 ){   // // pri koncentracii  50% a viac sa zapne aj  cervena dioda, znamena vysoku koncentraciu plynu
    digitalWrite(7,HIGH);
    }
    
   else{
    digitalWrite (7,LOW);
    }

    if(hodnota_plynu_analog >=358 ){ // ak koncentracia plynu je 35% alebo viac, tak sa zapne buzzer, 4o upozorni pouzivatela aj hlasovo 
      digitalWrite(12,HIGH);
    }
    else{
      digitalWrite(12,LOW);
    }
 lcd.setCursor(0, 0);          // nastavim si kurzor na displeji: 1. riadok a 0. stlpec
 lcd.print("Koncentracia ");
 lcd.setCursor(0,1);           // 0. stlpec 2. riadok
 lcd.print("plynu je:");
 lcd.print(percenta);
 lcd.print("   %");
    
}

 


  

