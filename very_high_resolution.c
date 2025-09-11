


#define F_CPU 3333333UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/io.h>

int main(void){
    PORTB.DIRSET = PIN0_bm;                                 // PB0 = WO0

    TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc
                      | TCA_SINGLE_CMP0EN_bm;
    TCA0.SINGLE.PER  = 33332;                                // ~100 Hz, presc=1
    TCA0.SINGLE.CMP0 = 16666;                                // ~50% duty (0..33332)
    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc
                      | TCA_SINGLE_ENABLE_bm;

    while(1){ /* set TCA0.SINGLE.CMP0 = 0..33332 */ 
         for(uint32_t x = 0; x < 33332; x++){
             TCA0.SINGLE.CMP0 = x; 
             _delay_ms(1);
             
        }
        
        
        
    }
}
