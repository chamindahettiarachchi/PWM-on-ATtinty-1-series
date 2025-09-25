#define F_CPU 3333333UL
#include <avr/io.h>
#include <util/delay.h>


int main(void){
    PORTB.DIRSET = PIN0_bm | PIN1_bm | PIN2_bm;//three pins can be set as output                               

    TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc   
                      | TCA_SINGLE_CMP0EN_bm   | TCA_SINGLE_CMP1EN_bm | TCA_SINGLE_CMP2EN_bm ;  //enable all three outputs as pwm           
    TCA0.SINGLE.PER  = 255;                                 
                                  
    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc     //prescaler     
                      | TCA_SINGLE_ENABLE_bm;               

    while(1){ 
        
             TCA0.SINGLE.CMP1 = 50; // dutycycle can be adjusted seperatly 
              TCA0.SINGLE.CMP2 = 125; 
              TCA0.SINGLE.CMP0 = 255; 
        
    }
}
