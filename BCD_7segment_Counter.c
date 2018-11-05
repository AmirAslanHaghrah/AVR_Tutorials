/*
 * Author : AmirAslan Haghrah
 */

// In this tutorial we use EXT INTERRUPTS to control 0 to 9 counting procedure.
// EXT_INT0 used to pause counting and EXT_INT1 used to continue the counting.


#include<io.h>
#include<delay.h>

int ON = 1;
int i=0;
int a =0;

void main() {
  DDRA=0b11111111;

  MCUCR=0b00001111;
  GIFR=0b11000000;
  GICR=0b11000000;

  #asm("sei");
  while(1){
      for(i=a;ON == 1 & i<10;i++){
          PORTA=i;
          delay_ms(500);
      }
  }
}

interrupt[EXT_INT0] void EXT_INT0_ISR(void){
    ON = 0;
    a = i;
}

interrupt[EXT_INT1] void EXT_INT1_ISR(void){
    ON = 1;     
}
