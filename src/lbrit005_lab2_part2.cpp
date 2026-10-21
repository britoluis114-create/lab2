/*         Luis & lbrit005@ucr.edu:

            Discussion: 023

 *         Assignment: Lab #2  Exercise # 2

 *         Exercise Description: In this we will be counting with buttons. 
            Button 0 will increment the count and button 1 will decrement the count. 
 *        

 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.

 *

 *         Demo Link: <https://youtu.be/pMv-laTA5q0>

 */

#include <avr/io.h>
#include <util/delay.h>

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
   return (b ?  (x | (0x01 << k))  :  (x & ~(0x01 << k)) );
              //   Set bit to 1           Set bit to 0
}

unsigned char GetBit(unsigned char x, unsigned char k) {
   return ((x & (0x01 << k)) != 0);
}

// TODO: complete nums
// the index is also the digit it represents
// eg: nums[0]="0", nums[9]="9", nums[15]="f"
// bits layout:   gfedcba   (REVERSE ORDER!)
int nums[16] = {0b0111111, // 0
                0b0000110, // 1
                0b1011011, // 2
                0b1001111, // 3 
                0b1100110, // 4
                0b1101101, // 5
                0b1111101, // 6
                0b0000111, // 7
                0b1111111, // 8
                0b1101111, // 9
                0b1110111, // a
                0b1111100, // b
                0b0111001, // c 
                0b1011110, // d
                0b1111011, // e
                0b1110001  // f 
                }; 

//TODO: complete outNum()
// void outNum(int num){
// 	PORTB = 0x1F; // depends on your wiring. Assign bits (e-a), which are bits (4-0) from nums[] to register PORTB
//   PORTD = 0xC0; // Assign bits (g & f) which are bits 6 & 5 of nums[] to register PORTD
// }

 enum states {start, stop, s0,s0_stop,s1,s1_stop} state; //TODO: finish the enum for the SM

  void Tick() {
   // Declare any static variables here
  static unsigned char position = 0x03; // position of the LED, 0-3 for PD2-PD5 respectively
     static unsigned char count = 0;
   // State Transistions
   //TODO: complete transitions 
   switch(state) {
   case start:
       state = stop;
       break;
     case stop:
     if (GetBit(PINC, 0) == 1){ //button 0  is on
           	state = s0;
            
       		break;
     
    }
       else if(GetBit(PINC, 1) == 1){ // button 1 is on
           	state = s1;
            
         }
     else{
     	state = stop;
     }
       break;
     case s0:
           state = s0_stop;
             break;
     case s0_stop:        
         if(GetBit(PINC,0) == 0){
             state = stop; 
         }
         else{
             state = s0_stop;
         }
         break;
     case s1:
           state = s1_stop;
           break;
     case s1_stop:
         if(GetBit(PINC,1) == 0){ 
             state = stop; 
         }
         else{ 
             state = s1_stop;
         }
       break;
     default:
       state = stop;
  }

   // State Actions
   //TODO: complete transitions
   switch(state) {
     case start:
       count = 0;
       break;
     case stop:
       break;
     case s0:
       ; // increment count and wrap around to 0 after 15
         count++;
       if(count > 15) {
             count = 0;
         }
       break;
     case s1:
       ; // decrement count and wrap around to 15 after 0
        
       if(count == 0) {
             count = 15;
         }
       else {
             count--;
        }
    
       break;
    default:
      break;
   }
   PORTD = (PORTD & 0x03) | (count << 2); // set the LED position on PORTD
}

int main(void)
{
  //TODO: initialize all outputs and inputs
  DDRB     = 0;
  PORTB    = 0;
  
  DDRC    = 0x03;
  PORTC   = 0x00; // buttons as inputs, initialize to 0

  DDRD   = 0x3C; // PD2-PD5 as outputs
  PORTD  = 0x00; //PORTD outputs to 0
  

  // //TODO: initialize your state
   state = start;
  
   while (1) {
     Tick();
     _delay_ms(100); // adjust the delay as needed for your application
   }
   return 0;
}

