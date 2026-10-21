/*         Luis & lbrit005@ucr.edu:

            Discussion: 023

 *         Assignment: Lab #2  Exercise # 1

 *         Exercise Description: IN this lab we shfting the led lights with the correseponding button. 
            Button 0 shifts the light to the left and button 1 shifts the light to the right. 
            The light will keep shifting until the button is released. 

 *        

 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.

 *

 *         Demo Link: <https://youtu.be/iUPKDL7vcL8>

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
void outNum(int num){
  PORTD = 0; // depends on your wiring. Assign bits (e-a), which are bits (4-0) from nums[] to register PORTB
  PORTC = 0; // Assign bits (g & f) which are bits 6 & 5 of nums[] to register PORTD
}

enum states {start, stop, s0,s0_stop, s1,s1_stop} state; //TODO: finish the enum for the SM


void Tick() {
  // Declare any static variables here
  static unsigned char position = 0x04; // position of the LED, 0-3 for PD2-PD5 respectively
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
    	break;
	case stop:
    	break;
    case s0: // shift left button 0 by 1
    if(position != 0x20){ // so if the position is not at the leftmost then it can shift left
      position <<= 1;
      break;
    }
      break;
    case s0_stop: // so that it keeps shifting left until button 0 is off
        break;     
         
      
    case s1: // shift right button 1 by 1
    	if(position != 0x04){ // so if the position is not at the rightmost then it can shift right
      
      position >>= 1;
      break;
    }
      case s1_stop: // so that it keeps shifting right until button 1 is off
        break;
    
    default: 
    	break;
  }
  PORTD = (PORTD & 0x03) | position; // so that it keeps the first two bits of PORTD and changes the rest to the position of the LED
}


int main(void)
{
  //TODO: initialize all outputs and inputs
  DDRB     = 0x00;
  PORTB    = 0x00;   //the display is off for now
  
  DDRC    = 0x00; // buttons area off
  PORTC   = 0x03; // outputs

  DDRD   = 0x3C; //outputs LED
  PORTD  = 0x04;

  //TODO: initialize your state
  state = start;
  while (1) {
    Tick();
    _delay_ms(100);
  }
}