#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);


int flagmillis=false;
int flagmillisb2=false;

int startb1=0;
int flagb1=false;
int flagb2=false;
int flag1b1=false;


int countclockset=0;
int countclocksetb2=0;

int count=0;
int countb2=0;
int flagsnooze=false;

int readingb1=0;
int readingb2=0;
int readingb3=0;
int readingb4=0;

int beforereadingb1=0;
int beforereadingb2=0;
int beforereadingb3=0;
int beforereadingb4=0;

int ButtonStateb1=0;
int ButtonStateb2=0;
int ButtonStateb3=0;
int ButtonStateb4=0;

unsigned long debounceDelay=0.01;
unsigned long lastDebounceTimeb1=0;
unsigned long lastDebounceTimeb3=0;
unsigned long lastDebounceTimeb2=0;
unsigned long lastDebounceTimeb4=0;

int tempatureType=false;
int alarmType=false;
int ClockType=false;

float tempature;
float fahrenheit;

int flagclockset=false;
int flagclocksetb2=false;

int alarmpin=13;
int tempPin=0;
int b1=7;
int b2=8;
int b3=9;
int b4=10;

String time;
int hour=0;
int min=0;
int sec=0;
int hour1=0;
int x=0;
int y=0;
int alarmx=0;
int alarmy=0;

void setup()
{
cli();
  Serial.begin(9600);
  DDRD &=~(1<<PD7);  //pinMode(b1,INPUT);
  DDRB &=~(1<<PB0);// pinMode(b2,INPUT); 
  DDRB &=~(1<<PB1);//pinMode(b3,INPUT);
  DDRB &=~(1<<PB2);//pinMode(b4,INPUT);
  DDRC &=~(1<<PC0);//pinMode(tempPin,INPUT);
  DDRB |=(1<<PB5);//pinMode(alarmpin,OUTPUT);
  
//----------------TIMER1----------------------
  TCNT1 = 0;
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1<<WGM12);
  TCCR1B |= (1<<CS12)|(1<<CS10);
  OCR1A = 15624; 
  TIMSK1 |= (1<<OCIE1A);
  lcd.begin(16,2);
  
  sei();
}


void loop()
{
  
  readingb1=(PIND & (1<<PD7))>>PB7;//readingb1 = digitalRead(b1);
 
  tempature = analogRead(tempPin);
  tempature = (double)tempature / 1024;   
       tempature = tempature * 5;                  
       tempature = tempature - 0.5;                   
       tempature = tempature * 100;
  fahrenheit = ((tempature*9)/5)+32;
  
  
  
//-----------------b1 button------------------------------------  
    
  if((flagmillis==true) && (readingb1==1) && (flagb1==true)){
    
    flagmillis=false;
    flagb1 = false;
    countclockset++;
    flagclockset = true;
    x = hour;
    y = min;
  }
  if(readingb1 != beforereadingb1){
   lastDebounceTimeb1 = millis();
  }
  
  if((millis()-lastDebounceTimeb1)>debounceDelay){
    if(readingb1 != ButtonStateb1){
     ButtonStateb1 = readingb1;
    
    if(ButtonStateb1 == 1 ){
      if(flagb1 == false){
     
      count=0;
      flagb1 = true;
    
                       }
                          }
      else if((ButtonStateb1 == 0) && (flagb1 == true)){
        if(countclockset == 0  ){ 
        if(ClockType == false){
          ClockType = true;
                            }
        else{
          ClockType = false;
            }
        }
        flagb1 = false;
        if(flagclockset == true){
          countclockset++;
          if(countclockset>=3){
            
     
        hour = x;
        min = y;
        x = 0;
        y = 0;
        countclockset = 0;
        flagclockset = false;
          }
        }
                                                  }
      
                                 }
                                           }
  
  beforereadingb1 = readingb1;
//-------------------------b2----------------------------------- 
  readingb2=(PINB & (1<<PB0))>>PB0;//readingb2 = digitalRead(b2);
  if((flagmillisb2==true) && (readingb2==1) && (flagb2==true)){
    
    flagmillisb2=false;
    flagb2 = false;
    countclocksetb2++;
    flagclocksetb2 = true;
    
  }
  if(readingb2 != beforereadingb2){
   lastDebounceTimeb2 = millis();
  }
  
  if((millis()-lastDebounceTimeb2)>debounceDelay){
    if(readingb2 != ButtonStateb2){
     ButtonStateb2 = readingb2;
    
    if(ButtonStateb2 == 1 ){
      if(flagb2 == false){
     
      countb2=0;
      flagb2 = true;
                       }
                          }
      else if((ButtonStateb2 == 0) && (flagb2 == true)){
        if(countclocksetb2 == 0  ){ 
        if(alarmType == false){
          alarmType = true;
                            }
        else{
          alarmType = false;
          noTone(alarmpin);
          flagsnooze=false;
            }
        }
        flagb2 = false;
        if(flagclocksetb2 == true){
          countclocksetb2++;
          if(countclocksetb2>=3){
            
     
        alarmType=true;
        countclocksetb2 = 0;
        flagclocksetb2 = false;
          }
        }
                                                  }
      
                                 }
                                           }
  
  beforereadingb2 = readingb2;
  
//---------------------------b3----------------------------
 readingb3=(PINB & (1<<PB1))>>PB1;//readingb3 = digitalRead(b3);
 if(readingb3 != beforereadingb3){
  lastDebounceTimeb3 = millis();
  }
  
  if((millis()-lastDebounceTimeb3)>debounceDelay){
    if(readingb3 != ButtonStateb3){
     ButtonStateb3 = readingb3;
    
    if((ButtonStateb3 == 1) && (flagclockset == false) && (flagclocksetb2 == false) ){
      if(tempatureType == false){
          tempatureType = true;
                            }
        else{
          tempatureType = false;
            }
    }
      else if((ButtonStateb3 == 1) && (flagclockset == true) && (flagclocksetb2 == false)){
        if(countclockset == 1){
          y++;
          if(y>=60){
          y=0;
          }
        }
        else if(countclockset == 2){
          x++;
          if(x>=24){
            x=0;
          }
        }
      }
      else if((ButtonStateb3 == 1) && (flagclockset == false) && (flagclocksetb2 == true)){
      if(countclocksetb2 == 1){
          alarmy++;
          if(alarmy>=60){
          alarmy=0;
          }
        }
        else if(countclocksetb2 == 2){
          alarmx++;
          if(alarmx>=24){
            alarmx=0;
          }
        }
      }
      
    
  }
 }
  
  beforereadingb3=readingb3;
//-------------------------------b4----------------------------
  

  readingb4=(PINB & (1<<PB2))>>PB2;//readingb4 = digitalRead(b4);

  if(readingb4 != beforereadingb4){
   lastDebounceTimeb4 = millis();
  }
  
  if((millis()-lastDebounceTimeb4)>debounceDelay){
    if(readingb4 != ButtonStateb4){
     ButtonStateb4 = readingb4;
    
    if(ButtonStateb4 == 1 ){
      if(flagsnooze==true){
      for(int i=0;i<5;i++){
          alarmy++;
          if(alarmy>=60){
           alarmx++;
           alarmy=0;
          }
          if(alarmx>=24){
          alarmx=0;
          }
      
      } 
        flagsnooze=false;
        noTone(alarmpin);
      
      }
      
    }
                                 }
                                           }
  
  beforereadingb4 = readingb4;
  
  
  
  
  
//-----------------------------------------------------------  
  
  if(countclockset == 0  ){
    if(ClockType == false){
    lcd.setCursor(0,0);
    if(hour<10)lcd.print("0");
    lcd.print(hour);
    lcd.print(":");
  
 
  
    lcd.setCursor(3,0);
    if(min<10)lcd.print("0");
    lcd.print(min);
    lcd.setCursor(5,0);
    lcd.print("  ");
                        }
  else if(ClockType == true){
    if(hour>=12){time = "PM";}
    else{time = "AM";}
    if(hour>12){hour1 = (hour-12);}
  else hour1 = hour;
    
 
    
    lcd.setCursor(0,0);
    if(hour1<10)lcd.print("0");
    lcd.print(hour1);
    lcd.print(":");
  
 
  
    lcd.setCursor(3,0);
    if(min<10)lcd.print("0");
    lcd.print(min);
    lcd.setCursor(5,0);
    lcd.print(time);
    
  }
  }
  
  else if(countclockset == 1){// minute
    
    if(ClockType == false){
    
    lcd.setCursor(0,0);
    if(x<10)lcd.print("0");
    lcd.print(x);
    lcd.print(":");
    lcd.setCursor(3,0);
    if(y<10)lcd.print("0");
    lcd.print(y);
    lcd.setCursor(5,0);
    lcd.print("  ");
   
    lcd.setCursor(0,0);
    if(x<10)lcd.print("0");
    lcd.print(x);
    lcd.print(":");
    lcd.setCursor(3,0);
    lcd.print("  ");
    lcd.setCursor(5,0);
    lcd.print("  ");
    }
    
    else if(ClockType == true){
    if(x>=12){time = "PM";}
    else{time="AM";}
    if(x>12){hour1 = (x-12);}
  else hour1 = x;  
      
      
    lcd.setCursor(0,0);
    if(hour1<10)lcd.print("0");
    lcd.print(hour1);
    lcd.print(":");
    lcd.setCursor(3,0);
    if(y<10)lcd.print("0");
    lcd.print(y);
    lcd.setCursor(5,0);
    lcd.print(time);
   
     lcd.setCursor(0,0);
    if(hour1<10)lcd.print("0");
    lcd.print(hour1);
    lcd.print(":");
    lcd.setCursor(3,0);
    lcd.print("  ");
    lcd.setCursor(5,0);
    lcd.print(time);
    
    
    }
    
    
  }
  
  
  
  else if (countclockset == 2){
    if(ClockType == false){
       lcd.setCursor(0,0);
       if(x<10)lcd.print("0");
       lcd.print(x);
       lcd.print(":");
       lcd.setCursor(3,0);
       if(y<10)lcd.print("0");
       lcd.print(y);
       lcd.setCursor(5,0);
       lcd.print("  ");
       
       lcd.setCursor(0,0);
       lcd.print("  ");
       lcd.print(":");
       lcd.setCursor(3,0);
       if(y<10)lcd.print("0");
       lcd.print(y);
       lcd.setCursor(5,0);
       lcd.print("  ");
      
    }
    
    
    else if(ClockType==true){
       
    if(x>=12){time = "PM";}
    else{time = "AM";}
    if(x>12){hour1=(x-12);}
    else {hour1 = x;}  
      
      
    lcd.setCursor(0,0);
    if(hour1<10)lcd.print("0");
    lcd.print(hour1);
    lcd.print(":");
    lcd.setCursor(3,0);
    if(y<10)lcd.print("0");
    lcd.print(y);
    lcd.setCursor(5,0);
    lcd.print(time);
    
    lcd.setCursor(0,0);
    lcd.print("  ");
    lcd.print(":");
    lcd.setCursor(3,0);
    if(y<10)lcd.print("0");
    lcd.print(y);
    lcd.setCursor(5,0);
    lcd.print(time);
      
      
    }
    
    
    
    
  }
  if(countclocksetb2==0){
    if(alarmType==false){
    lcd.setCursor(9,0);
    lcd.print(" ");  
    lcd.setCursor(10,0);
    if(alarmx<10)lcd.print("0");
    lcd.print(alarmx);
    lcd.print(":");
  
 
  
    lcd.setCursor(13,0);
    if(alarmy<10)lcd.print("0");
    lcd.print(alarmy);

    }
    else{
    lcd.setCursor(9,0);
    lcd.print("*");  
    lcd.setCursor(10,0);
    if(alarmx<10)lcd.print("0");
    lcd.print(alarmx);
    lcd.print(":");
  
 
  
    lcd.setCursor(13,0);
    if(alarmy<10)lcd.print("0");
    lcd.print(alarmy);
   
    }
  }
  else if (countclocksetb2==1){
    alarmType=false;
    lcd.setCursor(9,0);
    lcd.print(" "); 
    lcd.setCursor(10,0);
    if(alarmx<10)lcd.print("0");
    lcd.print(alarmx);
    lcd.print(":");
    lcd.setCursor(13,0);
    if(alarmy<10)lcd.print("0");
    lcd.print(alarmy);
   
    lcd.setCursor(9,0);
    lcd.print(" "); 
    lcd.setCursor(10,0);
    if(alarmx<10)lcd.print("0");
    lcd.print(alarmx);
    lcd.print(":");
    lcd.setCursor(13,0);
    lcd.print("  ");
   
  }
  else if (countclocksetb2==2){
       lcd.setCursor(9,0);
       lcd.print(" "); 
     lcd.setCursor(10,0);
       if(alarmx<10)lcd.print("0");
       lcd.print(alarmx);
       lcd.print(":");
       lcd.setCursor(13,0);
       if(alarmy<10)lcd.print("0");
       lcd.print(alarmy);
      
       lcd.setCursor(9,0);
       lcd.print(" ");
       lcd.setCursor(10,0);
       lcd.print("  ");
       lcd.print(":");
       lcd.setCursor(13,0);
       if(alarmy<10)lcd.print("0");
       lcd.print(alarmy);
      
  
  }
  
  
  if(tempatureType == false){
    
    lcd.setCursor(8,1);
    
  if(tempature>=0 && tempature<10){lcd.print("  ");}
  else if(tempature>=10 && tempature <100){ lcd.print(" ");}
  else if(tempature<0 && tempature >-10){lcd.print(" ");}
     lcd.print(tempature);
     lcd.print("C");
      
  }
  
  
  else{
    
     lcd.setCursor(8,1);
    
    if(fahrenheit>=0 && fahrenheit<10){lcd.print("  ");}
    else if(fahrenheit>=10 && fahrenheit <100){ lcd.print(" ");}
    else if(fahrenheit<0 && fahrenheit >-10){lcd.print(" ");}

     lcd.print(fahrenheit);
     lcd.print("F");
      
  }

}




ISR(TIMER1_COMPA_vect){
  sec++;
  if(sec>=60){
    min++;
    sec=0;
  }
  if(min>=60){
    hour++;
    min=0;
    
  }
  if(hour>=24){
  hour=0;
  }
  
  if(flagb1==true){  
count++;
  }
 
  if((count>=3) && flagb1==true){
    flagmillis=true;
    count=0;
  }
  if(flagb2==true){
    countb2++;
  }
  if((countb2>=3) && flagb2==true){
    flagmillisb2=true;
    countb2=0;
  }
  
  if(hour==alarmx && min==alarmy && alarmType==true){
  tone(alarmpin,500);
  flagsnooze=true;
  }
}
