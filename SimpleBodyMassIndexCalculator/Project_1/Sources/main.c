// Sema Köse
// 141044002
// Exercise2


// Control PTH and get the value from PTH. - Done

// Play 3 different songs for 15 seconds according to what is selected at
// the two least significant DIP switches (00, 01, 10, 11).  - Done

// Light PORTB LEDs according to the music. (It is up to you but at least
// you can get use of the frequencies, i.e. notes.) - Done

// Show the number of the song on 7-segment LEDs. -Done

// If 00 is selected, play all three songs and each for 5 seconds. -Done

// 10s and 5s delay will be implemented by using Timer Overflow
// Property of Timer Module.  -Done

// The different frequencies will be generated using Output Compare
// Property of Timer Module. -Done

// BONUS
// Alternatively communicating with the PC (instead of DIP Switches)
// using Serial Communication Module will bring you 15pts additionally. 
// Not Entirely True


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#define cpuFREQ 24000000
#define LCD_DAT PORTK /* Port K drives LCD data pins, E, and
RS */
#define LCD_DIR DDRK /* Direction of LCD port */
#define LCD_E 0x02 /* LCD E signal */
#define LCD_RS 0x01 /* LCD Register Select signal */
#define CMD 0 /* Command type for put2lcd */
#define DATA 1 

int count = 0;

unsigned char res;

#define FREQ 16

#define Width 1

void MSDelay(unsigned int);
void play(unsigned int freq, unsigned long int time);
void stop(unsigned long int time);
void lightSensor(void);
void keypadCode(void);
void openlcd(void);
void puts2lcd (char *ptr);
void put2lcd(char c, char type);
void lcdCode(char *msg1, char *msg2);
void enableSevenSegment(int num);
void lightSevenSegment(char c);
void MDelay(unsigned int itime);



const unsigned char keypad[4][4] =
{
'1','2','3','A',
'4','5','6','B',
'7','8','9','C',
'*','0','#','D'
};
unsigned char column,row;
unsigned char boy[3];
unsigned char kilo[3];
unsigned char sonuc2[3];
unsigned char kalori[4];
unsigned char yas[2];
unsigned int dummy = 0;
int vucutKitleIndexi(void);
void boyKilo(void);
unsigned int count2 = 0;
unsigned int yasInt = 0;
unsigned int kaloriIhtiyaci = 0;
unsigned int boyInt = 0;
unsigned int kiloInt = 0;
unsigned int kaloriInt = 0;
unsigned int fark = 0;
void main(void) 
{
  unsigned char choise = 0;   
  DDRH = 0x00;
  DDRP = 0xFF;
  DDRT = DDRT | 0b00100000;    // PTT5 as output 
  TSCR1 = 0x80;
  TSCR2 = 0x00;
  TIOS = 0x20;
  TCTL1 = 0x04;
      play(12151, 1000/3);  //B5
      PORTB = 12151;
      play(18206, 1250/3);  //E5
      PORTB = 18206;
      TCTL1 = 0x00;
      //lightSensor();
  for(;;){
     
     unsigned int sonuc = 0;
     char *msg1 = "Boyunuz?";
     char *msg2 = "";
     
     
     TCTL1 = 0x00;
     
     
     dummy = 0; 
     count2 = 0;
     lcdCode(msg1, msg2);
     keypadCode();
     put2lcd(boy[0],DATA);
     put2lcd(boy[1],DATA);
     put2lcd(boy[2],DATA);
     MSDelay(1000);
     MSDelay(1000);
     dummy = 1;
     count2 = 0;
     msg1 = "Kilonuz?";
     lcdCode(msg1, msg2);
     keypadCode();
     
     put2lcd(kilo[0],DATA);
     put2lcd(kilo[1],DATA);
     put2lcd(kilo[2],DATA);
     MSDelay(1000);
     MSDelay(1000);
     
     sonuc = vucutKitleIndexi();
     
     dummy = 2;
     count2 = 0;
     msg1 = "Yasiniz?";
     lcdCode(msg1, msg2);
     keypadCode();
     
     put2lcd(yas[0],DATA);
     put2lcd(yas[1],DATA);
     MSDelay(1000);
     MSDelay(1000);
     
     if(sonuc>1000){
      sonuc2[0] = (sonuc/1000) + '0';
      sonuc2[1] = (sonuc/100) + '0';
      sonuc2[2] = (sonuc/10) + '0';
      sonuc2[3] = (sonuc%10) + '0';
     }else if(sonuc>100){
      sonuc2[0] = (sonuc/100) + '0';
      sonuc2[1] = (sonuc/10) + '0';
      sonuc2[2] = (sonuc%10) + '0';
     } else{
      sonuc2[0] = (sonuc/10) + '0';
      sonuc2[1] = (sonuc%10) + '0';
     }
     
     /*put2lcd(sonuc2[0],DATA);
     put2lcd(sonuc2[1],DATA);
     put2lcd(sonuc2[2],DATA);
     put2lcd(sonuc2[3],DATA);
     MSDelay(1000);*/
     
     msg1 = "1.Kitle Indexi";
     msg2 = "2.Kalori Farki";
     lcdCode(msg1, msg2);
     MSDelay(1000);
     MSDelay(1000);
     MSDelay(1000);
     MSDelay(1000);
     
     choise = PTH | 0xFC; //get the input
     PORTB = choise;
     
     if(choise == 0xFD){
     
        msg1 = "Vucut Kitle";
        msg2 = "Indexiniz:";
       
        lcdCode(msg1, msg2);
        MSDelay(1000);
       
        msg1 = (char*)sonuc2;
        msg2 = "";
        lcdCode(msg1, msg2);
        MSDelay(1000);
        if(sonuc <= 18){
        msg1 = "Zayif!";
        msg2 = ":(";
        lcdCode(msg1, msg2);
        put2lcd(kalori[0],DATA);
        put2lcd(kalori[1],DATA);
        put2lcd(kalori[2],DATA);
        put2lcd(kalori[3],DATA);
        MSDelay(1000);
        
       }else if((sonuc>18) && (sonuc<25)){
        msg1 = "Normal!";
        msg2 = ":)";
        lcdCode(msg1, msg2);
        MSDelay(1000);
       }else if(sonuc>=25){
        msg1 = "Fazla Kilolu!";
        msg2 = ":(";
        TCTL1 = 0x04;
        lcdCode(msg1, msg2);
        play(12151, 1000/3);  //B5
        PORTB = 12151;
        play(18206, 1250/3);  //E5
        PORTB = 18206;
        play(12151, 1000/3);  //B5
        PORTB = 12151;
        play(18206, 1250/3);  //E5
        PORTB = 18206;
        MSDelay(1000);
        TCTL1 = 0x00;
        /*put2lcd(kalori[0],DATA);
        put2lcd(kalori[1],DATA);
        put2lcd(kalori[2],DATA);
        put2lcd(kalori[3],DATA);*/
        lcdCode(msg1, msg2);
        MSDelay(1000);
       }
     } else if(choise == 0xFE){
        kaloriIhtiyaci = 665+(9*kiloInt)+(2*boyInt)-(5*yasInt);
     
       msg1 = "Bugun aldiginiz";
       msg2 = "kalori?";
       dummy = 3;
       count2 = 0;
       lcdCode(msg1, msg2);
       keypadCode();
       
       put2lcd(kalori[0],DATA);
       put2lcd(kalori[1],DATA);
       put2lcd(kalori[2],DATA);
       put2lcd(kalori[3],DATA);
       MSDelay(1000);
       
       fark = kaloriIhtiyaci - kaloriInt;
       
       msg1 = "Fark";
       msg2 = "Hesaplaniyor...";
       lcdCode(msg1, msg2);
       MSDelay(1000);
       MSDelay(1000);
       
       if(fark < 0){
        msg1 = "Cok";
        msg2 = "Fazla";
        TCTL1 = 0x04;
        lcdCode(msg1, msg2);
        play(12151, 1000/3);  //B5
        PORTB = 12151;
        play(18206, 1250/3);  //E5
        PORTB = 18206;
        play(12151, 1000/3);  //B5
        PORTB = 12151;
        play(18206, 1250/3);  //E5
        PORTB = 18206;
        MSDelay(1000);
        TCTL1 = 0x00;
       }else if(fark > 0){
        kalori[0] = (fark/1000) + '0';
        kalori[1] = (fark/100) + '0';
        kalori[2] = (fark/10) + '0';
        kalori[3] = (fark%10) + '0';
        msg1 = "Kalori";
        msg2 = "Az";
        lcdCode(msg1, msg2);
        MSDelay(1000);
       }else if(fark == 0){
        msg1 = "Yeterli";
        msg2 = "";
        lcdCode(msg1, msg2);
        MSDelay(1000);
       }
     }
     
     
     PORTB = kaloriInt;
     MSDelay(1000);
     MSDelay(1000);
     /*PORTB = boyInt;
     MSDelay(1000);
     PORTB = kiloInt;
     MSDelay(1000);
     PORTB = kaloriInt;
     MSDelay(1000);*/
     
     
  }
     
     /*put2lcd(sonuc2[0],DATA);
     put2lcd(sonuc2[1],DATA);
     put2lcd(sonuc2[2],DATA);*/
     
     /*put2lcd(boy[0],DATA);
     put2lcd(boy[1],DATA);
     put2lcd(boy[2],DATA);
     
     put2lcd(kilo[0],DATA);
     put2lcd(kilo[1],DATA);
     put2lcd(kilo[2],DATA);
     MSDelay(1000);*/
}


void MSDelay(unsigned int itime)  //msec delay
  {
    unsigned int i; unsigned int j;
    for(i=0;i<itime;i++)
      for(j=0; j<4000; ++j);
  }
void MDelay(unsigned int itime)  //msec delay
  {
    unsigned int i; unsigned int j;
    for(i=0x00;i<itime;i++) {
      TSCR1 = 0x80;
      TSCR2 = 0x00;
      
      TFLG2 = 0x80;
      while((TFLG2 & 0x80)!=0x80);
    }
  }
  
void play(unsigned int freq, unsigned long int time){  //play the song
    unsigned long int i, maxOF;
    maxOF = (time*1000)/2730; //compute the overflow
    
    
    for(i=0; i<maxOF;){
      TC5 += freq;
      while(!(TFLG1 & TFLG1_C5F_MASK)); //output compare
      TFLG1 = TFLG1 | TFLG1_C5F_MASK;
      if(TFLG2 & 0x80){
         ++i;
         TFLG2 = 0x80;
      }
       
      //MSDelay(10);
    }
}
void stop(unsigned long int time){ /*delay 2*/
    unsigned long int i, maxOF;
    maxOF = (time*1000)/2730;
    TCTL1 = 0x00;
    for(i=0; i<maxOF;++i){
    }
}

void lightSensor(void){
    DDRB = 0xFF;    //PORTB as output
    DDRJ = 0xFF;    //PTJ as output for Dragon12+ LEDs
    PTJ=0x0;        //Allow the LEDs to dsiplay data on PORTB pins
    
    ATD0CTL2 = 0x80;     //Turn on ADC,..No Interrupt
    MSDelay(5);
    ATD0CTL3 = 0x08;  //one conversion, no FIFO
    ATD0CTL4 = 0xEB;  //8-bit resolu, 16-clock for 2nd phase,
                      //prescaler of 24 for Conversion Freq=1MHz  
    for(;;)
    {
    ATD0CTL5 = 0x84;  //Channel 4 (right justified, unsigned,single-conver,one chan only) 

    while(!(ATD0STAT0 & 0x80));
      PORTB = ATD0DR0L;  //dump it on LEDs
      
      MSDelay(50);  //optional
    }
}

void keypadCode(void){
   unsigned int i = 0;
   DDRB = 0xFF;                           //MAKE PORTB OUTPUT
   DDRJ |=0x02; 
   PTJ &=~0x02;                            //ACTIVATE LED ARRAY ON PORT B
   DDRP |=0x0F;                           //
   PTP |=0x0F;                            //TURN OFF 7SEG LED
   DDRA = 0x0F;                           //MAKE ROWS INPUT AND COLUMNS OUTPUT
   
   
 
   while(1){                              //OPEN WHILE(1)
      do{                                 //OPEN do1
         PORTA = PORTA | 0x0F;            //COLUMNS SET HIGH
         row = PORTA & 0xF0;              //READ ROWS
      }while(row == 0x00);                //WAIT UNTIL KEY PRESSED //CLOSE do1



      do{                                 //OPEN do2
         do{                              //OPEN do3
            MSDelay(1);                   //WAIT
            row = PORTA & 0xF0;           //READ ROWS
         }while(row == 0x00);             //CHECK FOR KEY PRESS //CLOSE do3
         
         MSDelay(15);                     //WAIT FOR DEBOUNCE
         row = PORTA & 0xF0;
      }while(row == 0x00);                //FALSE KEY PRESS //CLOSE do2

      while(1){                           //OPEN while(1)
         PORTA &= 0xF0;                   //CLEAR COLUMN
         PORTA |= 0x01;                   //COLUMN 0 SET HIGH
         row = PORTA & 0xF0;              //READ ROWS
         if(row != 0x00){                 //KEY IS IN COLUMN 0
            column = 0;
            break;                        //BREAK OUT OF while(1)
         }
         PORTA &= 0xF0;                   //CLEAR COLUMN
         PORTA |= 0x02;                   //COLUMN 1 SET HIGH
         row = PORTA & 0xF0;              //READ ROWS
         if(row != 0x00){                 //KEY IS IN COLUMN 1
            column = 1;
            break;                        //BREAK OUT OF while(1)
         }

         PORTA &= 0xF0;                   //CLEAR COLUMN
         PORTA |= 0x04;                   //COLUMN 2 SET HIGH
         row = PORTA & 0xF0;              //READ ROWS
         if(row != 0x00){                 //KEY IS IN COLUMN 2
            column = 2;
            break;                        //BREAK OUT OF while(1)
         }
         PORTA &= 0xF0;                   //CLEAR COLUMN
         PORTA |= 0x08;                   //COLUMN 3 SET HIGH
         row = PORTA & 0xF0;              //READ ROWS
         if(row != 0x00){                 //KEY IS IN COLUMN 3
            column = 3;
            break;                        //BREAK OUT OF while(1)
         }
         row = 0;                         //KEY NOT FOUND
      break;                              //step out of while(1) loop to not get stuck
      }                                   //end while(1)

      if(row == 0x10){
         PORTB=keypad[0][column];         //OUTPUT TO PORTB LED
         res = keypad[0][column];
         enableSevenSegment(0);
         lightSevenSegment(res);
      }
      else if(row == 0x20){
         PORTB=keypad[1][column];
         res = keypad[1][column];
         enableSevenSegment(0);
         lightSevenSegment(res);
      }
      else if(row == 0x40){
         PORTB=keypad[2][column];
         res = keypad[2][column];
         enableSevenSegment(0);
         lightSevenSegment(res);
      }
      else if(row == 0x80){
         PORTB=keypad[3][column];
         res = keypad[3][column];
         enableSevenSegment(0);
         lightSevenSegment(res);
      }
      do{
         MSDelay(15);
         PORTA = PORTA | 0x0F;            //COLUMNS SET HIGH
         row = PORTA & 0xF0;              //READ ROWS
      }while(row != 0x00);                //MAKE SURE BUTTON IS NOT STILL HELD
      
      boyKilo();
      ++count2;
      
      if(((dummy == 0) && (count2==3)) || ((dummy == 1) && (count2==3)) || ((dummy == 2) && (count2==2)) || ((dummy == 3) && (count2==4))){
        break;
      }
      
   }                         
}

void openlcd(void)
{
  LCD_DIR = 0xFF; /* configure LCD_DAT port for output */
  MSDelay(100); /* Wait for LCD to be ready */
  put2lcd(0x28, CMD); /* set 4-bit data, 2-line display, 5x7 font */
  put2lcd(0x0F, CMD); /* turn on display, cursor, blinking */
  put2lcd(0x06, CMD); /* move cursor right */
  put2lcd(0x01, CMD); /* clear screen, move cursor to home */
  MSDelay(2); /* wait until "clear display" command complete */
}

void puts2lcd (char *ptr)
{
  while (*ptr) { /* While character to send */
  put2lcd(*ptr, DATA); /* Write data to LCD */
  MSDelay(1); /* Wait for data to be written */
  ptr++; /* Go to next character */} 
}

void put2lcd(char c, char type){
  char c_lo, c_hi;
  c_hi = (c & 0xF0) >> 2; /* Upper 4 bits of c */
  c_lo = (c & 0x0F) << 2; /* Lower 4 bits of c */
  LCD_DAT &= (~LCD_RS);
  if (type == DATA)
  LCD_DAT = c_hi | LCD_RS; /* output upper 4 bits, E, RS high */
  else
  LCD_DAT = c_hi; /* output upper 4 bits, E, RS low */
  LCD_DAT |= LCD_E; /* pull E signal to high */
  __asm(nop); /* Lengthen E */
  __asm(nop);
  __asm(nop);
  LCD_DAT &= (~LCD_E); /* pull E to low */
  if (type == DATA)
  LCD_DAT = c_lo | LCD_RS; /* output lower 4 bits, E, RS high */
  else
  LCD_DAT = c_lo; /* output lower 4 bits, E, RS low */
  LCD_DAT |= LCD_E; /* pull E to high */
  __asm(nop); /* Lengthen E */
  __asm(nop);
  __asm(nop);
  LCD_DAT &= (~LCD_E); /*pull E to low */
  MSDelay(1); /* Wait for command to execute */
}

void lcdCode(char *msg1, char *msg2){
  openlcd(); // Initialize LCD display
  puts2lcd(msg1); // Send first line
  put2lcd(0xC0,CMD); // move cursor to 2nd row, 1st column
  puts2lcd(msg2); // Send second line

}

int vucutKitleIndexi(void){
  unsigned int index = 0;
  int i,j;
  unsigned long int a = 0;
  unsigned long int b = 0;
  
  boyInt = 100*(boy[0]-'0') + 10*(boy[1]-'0')  + (boy[2]-'0') ;
  
  
  
  if(kilo[0] == '0')
     kiloInt = 10*(kilo[1]-'0') + (kilo[1]-'0');
  else
     kiloInt = 100*(kilo[0]-'0') + 10*(kilo[1]-'0') + (kilo[2]-'0');
  
  yasInt = 10*(yas[0]-'0')+(yas[1]-'0');
  
  kaloriInt = 1000*(kalori[0]-'0') + 100*(kalori[1]-'0') + 10*(kalori[2]-'0') + (kalori[3]-'0');
  
  a = kiloInt;
  b = boyInt*boyInt/10000;
  
  index = a/b;
  
  return index;
}

void boyKilo(void){
    
    if((dummy == 0) && (count2<3)){
      boy[count2] = res;
    } else if((dummy == 1) && (count2<3)){
      kilo[count2] = res;
    }else if((dummy == 2) && (count2<2)){
      yas[count2] = res;
    }else if((dummy == 3) && (count2<4)){
      kalori[count2] = res;
    }
}

void lightSevenSegment(char c){
  if(c == '0'){
    PORTB = 0x3F;
  }else if(c == '1'){
    PORTB = 0x06;
  }else if(c == '2'){
    PORTB = 0x5B;
  }else if(c == '3'){
    PORTB = 0x4F;
  }else if(c == '4'){
    PORTB = 0x66;
  }else if(c == '5'){
    PORTB = 0x6D;
  }else if(c == '6'){
    PORTB = 0x7C;
  }else if(c == '7'){
    PORTB = 0x07;
  }else if(c == '8'){
    PORTB = 0xFF;
  }else if(c == '9'){
    PORTB = 0x67;
  }
}

void enableSevenSegment(int num){
  if(num == 0){
    PTP = 0xF7;
  }else if(num == 1){
    PTP = 0xFB;
  }else if(num == 2){
    PTP = 0xFD;
  }else if(num == 3){
    PTP = 0xFE;
  }
}
