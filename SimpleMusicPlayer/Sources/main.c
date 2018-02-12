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

int count = 0;

#define FREQ 16

#define Width 1

void MSDelay(unsigned int);
void play(unsigned int freq, unsigned long int time);
void stop(unsigned long int time);

void main(void) 
{
  /* put your own code here */
  
    int i = 0;
    unsigned char choise = 0;   
    DDRT = DDRT | 0b00100000;    // PTT5 as output 
    TSCR1 = 0x80;
    TSCR2 = 0x00;
    TIOS = 0x20;
    //TCTL1 = 0x04; 
    DDRB= 0xFF;
    DDRH = 0x00;
    DDRP = 0xFF;
    
   
   
    
    for (;;) 			
    {
          TCTL1 = 0x00;
          PORTB = 0x01;
          MSDelay(1000);
          MSDelay(1000);
          MSDelay(1000);
          choise = PTH | 0xFC; //get the input
          PORTB = choise;
          
          
          //Serial Communication for test
          /*SCI0BDH=0x0;
          SCI0BDL=26;
          SCI0CR1=0x0;
          SCI0CR2=0x0C;
    
          while(!(SCI0SR1 & SCI0SR1_RDRF_MASK)); 
          choise= SCI0DRL - '0';
          choise = choise | 0xFC ;
          PORTB = choise;
          MSDelay (1000); */
          //end of Serial Communication
          
          
          //while(!choise)
           //choise = PTH;
          
          if(choise == 0xFC){  //play mix
            
            PTP = 0xFE;
            PORTB = 0x3F;
            MSDelay(1000);
            PTP = 0xFF;
            
            //song1
            PTP = 0xFE;
            PORTB = 0x06;
            MSDelay(1000);
            PTP = 0xFF;
            TCTL1 = 0x04;
            
            play(12151, 1000/3);  //B5
            PORTB = 12151;
            play(18206, 1250/3);  //E5
            PORTB = 18206;
            //PORTB = 0x03;
            play(15310, 500/3);  //G5
            PORTB = 18206;
            //PORTB = 0x04;
            play(17184, 1000/3); //F5
            PORTB = 17184;
            //PORTB = 0x01;
            play(18206, 2000/3); //E5
            PORTB = 18206;
            //PORTB = 0x02;
            play(12151, 1000/3); //B5
            PORTB = 12151;
            //PORTB = 0x03;
            play(13639, 2500/3);  //A5
            PORTB = 13639;
            //PORTB = 0x04;
            play(17184, 2500/3);   //F5
            PORTB = 17184;
            
            play(18206, 1250/3);  //E5
            PORTB = 18206;
            //PORTB = 0x03;
            play(15310, 500/3);  //G5
            PORTB = 15310;
            //PORTB = 0x04;
            play(17184, 1000/3); //F5
            PORTB = 17184;
            //PORTB = 0x01;
            play(10218, 2000/3); //D6
            PORTB = 10218;
            //PORTB = 0x01;
            TCTL1 = 0x00;
            MSDelay(1000);
            //TCTL1 = 0x04;
            
            
            
            //song2
            PTP = 0xFE;
            PORTB = 0x5B;
            MSDelay(1000);
            PTP = 0xFF;
            TCTL1 = 0x04;
            
            play(30619, 62);  //G4
            PORTB = 30619;
            play(24303, 62);  //B4
            PORTB = 24303;
            play(20436, 62);  //D5
            PORTB = 20436;
            play(16220, 62);  //F5S
            PORTB = 16220;
            
            play(15310, 250);  //G5
            PORTB = 15310;
            play(15310, 250);  //G5
            PORTB = 15310;
            play(15310, 62);  //G5
            PORTB = 15310;
            play(15310, 62);  //G5
            PORTB = 15310;
            play(15310, 250);  //G5
            PORTB = 15310;
            play(15310, 250);  //G5
            PORTB = 15310;
            play(15310, 250);  //G5
            PORTB = 15310;
            
            
            play(17184, 43);  //F5
            PORTB = 17184;
            play(17184, 43);  //F5
            PORTB = 17184;
            play(17184, 43);  //F5
            PORTB = 17184;
            play(17184, 43);  //F5
            PORTB = 17184;
            play(17184, 43);  //F5
            PORTB = 17184;
            play(16220, 43);  //F5S
            PORTB = 16220;
            
            play(10218, 375);  //G5
            PORTB = 10218;
            play(12151, 125);  //B5
            PORTB = 12151;
            
            play(10218, 500);  //D6
            PORTB = 10218;
            play(22939, 375);  //C5
            PORTB = 22939;
            play(17184, 375);  //F5
            PORTB = 17184;
            
            
            play(8592, 250);  //F6
            PORTB = 8592;
            play(9103, 62);  //E6
            PORTB = 9103;
            play(9644, 62);  //D6S
            PORTB = 9644;
            play(10218, 375);  //G5
            PORTB = 10218;
            play(12151, 125);  //B5
            PORTB = 12151;
            
            play(10218, 500);  //D6
            PORTB = 10218;
            play(22939, 375);  //C5
            PORTB = 22939;
            play(17184, 375);  //F5
            PORTB = 17184;
            
            
            //stop(5000);
            //TCTL1 = 0x04;
            TCTL1 = 0x00;
            PTP = 0xFE;
            PORTB = 0x4F;
            MSDelay(1000);
            PTP = 0xFF;
            TCTL1 = 0x04;
            
            //song3
            
            play(11469, 500);  //C6
            PORTB = 11469;
            play(12151, 375);  //B5
            PORTB = 12151;
            play(13639, 125);  //A5
            PORTB = 13639;
            play(15310, 750);  //G5
            PORTB = 15310;
            
            play(17184, 250);  //F5
            PORTB = 17184;
            play(18206, 500);  //E5
            PORTB = 18206;
            play(20436, 500);  //D5
            PORTB = 20436;
            play(22939, 750);  //C5
            PORTB = 22939;
            play(13639, 250);  //A5
            PORTB = 13639;
            play(13639, 750);  //A5
            PORTB = 13639;
            play(12151, 250);  //B5
            PORTB = 12151;
            
          } 
          if(choise == 0xFF){ //PLAY HARRY POTTER SONG
            TCTL1 = 0x04;
            PTP = 0xFE;
            PORTB = 0x4F;
            MSDelay(1000);
            PTP = 0xFF;
            play(12151, 1000/3);  //B5
            PORTB = 12151;
            play(18206, 1250/3);  //E5
            PORTB = 18206;
            //PORTB = 0x03;
            play(15310, 500/3);  //G5
            PORTB = 18206;
            //PORTB = 0x04;
            play(17184, 1000/3); //F5
            PORTB = 17184;
            //PORTB = 0x01;
            play(18206, 2000/3); //E5
            PORTB = 18206;
            //PORTB = 0x02;
            play(12151, 1000/3); //B5
            PORTB = 12151;
            //PORTB = 0x03;
            play(13639, 2500/3);  //A5
            PORTB = 13639;
            //PORTB = 0x04;
            play(17184, 2500/3);   //F5
            PORTB = 17184;
            
            play(18206, 1250/3);  //E5
            PORTB = 18206;
            //PORTB = 0x03;
            play(15310, 500/3);  //G5
            PORTB = 15310;
            //PORTB = 0x04;
            play(17184, 1000/3); //F5
            PORTB = 17184;
            //PORTB = 0x01;
            play(10218, 2000/3); //D6
            PORTB = 10218;
            //PORTB = 0x01;
            play(17184, 1000/3); //F5
            PORTB = 17184;
            //PORTB = 0x01;
            play(12151, 3000/3);  //B5
            PORTB = 12151;
            play(12151, 1000/3);  //B5
            PORTB = 12151;
            
            play(18206, 1250/3);  //E5
            PORTB = 18206;
            //PORTB = 0x03;
            play(15310, 500/3);  //G5
            PORTB = 15310;
            //PORTB = 0x04;
            play(17184, 1000/3); //F5
            PORTB = 17184;
            
            //repeat
            
            play(18206, 1250/3);  //E5
            PORTB = 18206;
            //PORTB = 0x03;
            play(15310, 500/3);  //G5
            PORTB = 15310;
            //PORTB = 0x04;
            play(17184, 1000/3); //F5
            PORTB = 17184;
            //PORTB = 0x01;
            play(10218, 2000/3); //D6
            PORTB = 10218;
            //PORTB = 0x01;
            play(17184, 1000/3); //F5
            PORTB = 17184;
            //PORTB = 0x01;
            play(12151, 3000/3);  //B5
            PORTB = 12151;
            play(12151, 1000/3);  //B5
            PORTB = 12151;
            
            play(18206, 1250/3);  //E5
            PORTB = 18206;
            //PORTB = 0x03;
            play(15310, 500/3);  //G5
            PORTB = 15310;
            //PORTB = 0x04;
            play(17184, 1000/3); //F5
            PORTB = 17184;
            
            
            
            
            play(18206, 1250/3);  //E5
            PORTB = 18206;
            //PORTB = 0x03;
            play(15310, 500/3);  //G5
            PORTB = 15310;
            //PORTB = 0x04;
            play(17184, 1000/3); //F5
            PORTB = 17184;
            //PORTB = 0x01;
            play(10218, 2000/3); //D6
            PORTB = 10218;
            //PORTB = 0x01;
            play(17184, 1000/3); //F5
            PORTB = 17184;
            //PORTB = 0x01;
            play(12151, 3000/3);  //B5
            PORTB = 12151;
            play(12151, 1000/3);  //B5
            PORTB = 12151;
            
            play(18206, 1250/3);  //E5
            PORTB = 18206;
            //PORTB = 0x03;
            play(15310, 500/3);  //G5
            PORTB = 15310;
            //PORTB = 0x04;
            play(17184, 1000/3); //F5
            PORTB = 17184;
            //PORTB = 0x01;
          } else if(choise == 0xFE){ //POKEMON
            TCTL1 = 0x04;
            PTP = 0xFE;
            PORTB = 0x5B;
            MSDelay(1000);
            PTP = 0xFF;
            
            play(30619, 62);  //G4
            PORTB = 30619;
            play(24303, 62);  //B4
            PORTB = 24303;
            play(20436, 62);  //D5
            PORTB = 20436;
            play(16220, 62);  //F5S
            PORTB = 16220;
            
            play(15310, 250);  //G5
            PORTB = 15310;
            play(15310, 250);  //G5
            PORTB = 15310;
            play(15310, 62);  //G5
            PORTB = 15310;
            play(15310, 62);  //G5
            PORTB = 15310;
            play(15310, 250);  //G5
            PORTB = 15310;
            play(15310, 250);  //G5
            PORTB = 15310;
            play(15310, 250);  //G5
            PORTB = 15310;
            
            
            play(17184, 43);  //F5
            PORTB = 17184;
            play(17184, 43);  //F5
            PORTB = 17184;
            play(17184, 43);  //F5
            PORTB = 17184;
            play(17184, 43);  //F5
            PORTB = 17184;
            play(17184, 43);  //F5
            PORTB = 17184;
            play(16220, 43);  //F5S
            PORTB = 16220;
            
            play(10218, 375);  //G5
            PORTB = 10218;
            play(12151, 125);  //B5
            PORTB = 12151;
            
            play(10218, 500);  //D6
            PORTB = 10218;
            play(22939, 375);  //C5
            PORTB = 22939;
            play(17184, 375);  //F5
            PORTB = 17184;
            
            
            play(8592, 250);  //F6
            PORTB = 8592;
            play(9103, 62);  //E6
            PORTB = 9103;
            play(9644, 62);  //D6S
            PORTB = 9644;
            
            //repeat
            play(15310, 250);  //G5
            PORTB = 15310;
            play(15310, 250);  //G5
            PORTB = 15310;
            play(15310, 62);  //G5
            PORTB = 15310;
            play(15310, 62);  //G5
            PORTB = 15310;
            play(15310, 250);  //G5
            PORTB = 15310;
            play(15310, 250);  //G5
            PORTB = 15310;
            play(15310, 250);  //G5
            PORTB = 15310;
            
            
            play(17184, 43);  //F5
            PORTB = 17184;
            play(17184, 43);  //F5
            PORTB = 17184;
            play(17184, 43);  //F5
            PORTB = 17184;
            play(17184, 43);  //F5
            PORTB = 17184;
            play(17184, 43);  //F5
            PORTB = 17184;
            play(16220, 43);  //F5S
            PORTB = 16220;
            
            play(10218, 375);  //G5
            PORTB = 10218;
            play(12151, 125);  //B5
            PORTB = 12151;
            
            play(10218, 500);  //D6
            PORTB = 10218;
            play(22939, 375);  //C5
            PORTB = 22939;
            play(17184, 375);  //F5
            PORTB = 17184;
            
            
            play(8592, 250);  //F6
            PORTB = 8592;
            play(9103, 62);  //E6
            PORTB = 9103;
            play(9644, 62);  //D6S
            PORTB = 9644;
            
            play(17184, 43);  //F5
            PORTB = 17184;
            play(17184, 43);  //F5
            PORTB = 17184;
            play(17184, 43);  //F5
            PORTB = 17184;
            play(17184, 43);  //F5
            PORTB = 17184;
            play(17184, 43);  //F5
            PORTB = 17184;
            play(16220, 43);  //F5S
            PORTB = 16220;
            
            play(10218, 375);  //G5
            PORTB = 10218;
            play(12151, 125);  //B5
            PORTB = 12151;
            
            play(10218, 500);  //D6
            PORTB = 10218;
            play(22939, 375);  //C5
            PORTB = 22939;
            play(17184, 375);  //F5
            PORTB = 17184;
            
            
            play(8592, 250);  //F6
            PORTB = 8592;
            play(9103, 62);  //E6
            PORTB = 9103;
            play(9644, 62);  //D6S
            PORTB = 9644;
            
            play(10218, 375);  //G5
            PORTB = 10218;
            play(12151, 125);  //B5
            PORTB = 12151;
            
            play(10218, 500);  //D6
            PORTB = 10218;
            play(22939, 375);  //C5
            PORTB = 22939;
            play(17184, 375);  //F5
            PORTB = 17184;
            
            
            play(8592, 250);  //F6
            PORTB = 8592;
            play(9103, 62);  //E6
            PORTB = 9103;
            play(9644, 62);  //D6S
            PORTB = 9644;
            
            play(8592, 250);  //F6
            PORTB = 8592;
            play(9103, 62);  //E6
            PORTB = 9103;
            play(9644, 62);  //D6S
            PORTB = 9644;
            
            play(10218, 375);  //G5
            PORTB = 10218;
            play(12151, 125);  //B5
            PORTB = 12151;
            
            play(10218, 500);  //D6
            PORTB = 10218;
            play(22939, 375);  //C5
            PORTB = 22939;
            play(17184, 375);  //F5
            PORTB = 17184;
            
            
            play(8592, 250);  //F6
            PORTB = 8592;
            play(9103, 62);  //E6
            PORTB = 9103;
            play(9644, 62);  //D6S
            PORTB = 9644;
            
            
          }
          else if(choise == 0xFD){  //JOY TO THE WORLD
            PTP = 0xFE;
            PORTB = 0x06;
            TCTL1 = 0x04;
            MSDelay(1000);
            PTP = 0xFF;
            
            play(11469, 500);  //C6
            PORTB = 11469;
            play(12151, 375);  //B5
            PORTB = 12151;
            play(13639, 125);  //A5
            PORTB = 13639;
            play(15310, 750);  //G5
            PORTB = 15310;
            
            play(17184, 250);  //F5
            PORTB = 17184;
            play(18206, 500);  //E5
            PORTB = 18206;
            play(20436, 500);  //D5
            PORTB = 20436;
            play(22939, 750);  //C5
            PORTB = 22939;
            play(13639, 250);  //A5
            PORTB = 13639;
            play(13639, 750);  //A5
            PORTB = 13639;
            play(12151, 250);  //B5
            PORTB = 12151;
            play(12151, 750);  //B5
            PORTB = 12151;
            
            play(11469, 250);  //C6
            PORTB = 11469;
            play(11469, 1000);  //C6
            PORTB = 11469;
            play(11469, 750);  //C6
            PORTB = 11469;
            
            play(11469, 250);  //C6
            PORTB = 11469;
            play(12151, 250);  //B5
            PORTB = 12151;
            play(13639, 250);  //A5
            PORTB = 13639;
            play(15310, 250);  //G5
            PORTB = 15310;
            play(15310, 250);  //G5
            PORTB = 15310;
            play(17184, 375);  //F5
            PORTB = 17184;
            
            play(18206, 125);  //E5
            PORTB = 18206;
            play(11469, 250);  //C6
            PORTB = 11469;
            play(11469, 250);  //C6
            PORTB = 11469;
            play(12151, 250);  //B5
            PORTB = 12151;
            play(13639, 250);  //A5
            PORTB = 13639;
            
            play(15310, 250);  //G5
            PORTB = 15310;
            play(15310, 250);  //G5
            PORTB = 15310;
            play(17184, 375);  //F5
            PORTB = 17184;
            play(18206, 125);  //E5
            PORTB = 18206;
            play(18206, 250);  //E5
            PORTB = 18206;
            play(18206, 250);  //E5
            PORTB = 18206;
            play(18206, 250);  //E5
            PORTB = 18206;
            play(18206, 250);  //E5
            PORTB = 18206;
            play(18206, 250);  //E5
            PORTB = 18206;
            
            play(17184, 125);  //F5
            PORTB = 17184;
            play(15310, 125);  //G5
            PORTB = 15310;
            play(17184, 750);  //F5
            PORTB = 17184;
            play(18206, 125);  //E5
            PORTB = 18206;
            play(20436, 125);  //D5
            PORTB = 20436;
            play(20436, 250);  //D5
            PORTB = 20436;
            play(20436, 250);  //D5
            PORTB = 20436;
            play(20436, 250);  //D5
            PORTB = 20436;
            
            play(18206, 125);  //E5
            PORTB = 18206;
            play(17184, 125);  //F5
            PORTB = 17184;
            //CONTROL
            play(18206, 750);  //E5
            PORTB = 18206;
            play(20436, 125);  //D5
            PORTB = 20436;
            
            play(22939, 125);  //C5
            PORTB = 22939;
            play(11469, 250);  //C6
            PORTB = 11469;
            play(13639, 500);  //A5
            PORTB = 13639;
            play(15310, 250);  //G5
            PORTB = 15310;
            
            play(17184, 750);  //F5
            PORTB = 17184;
            play(18206, 125);  //E5
            PORTB = 18206;
            play(17184, 250);  //F5
            PORTB = 17184;
            play(18206, 250);  //E5
            PORTB = 18206;
            
            play(20436, 500);  //D5
            PORTB = 20436;
            play(22939, 500);  //C5
            PORTB = 22939;


            
          }
     TCTL1 = 0x00;     
    }
    //TFLG1 = 0x00;
    
}


void MSDelay(unsigned int itime)  //msec delay
  {
    unsigned int i; unsigned int j;
    for(i=0;i<itime;i++)
      for(j=0;j<4000;j++);
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