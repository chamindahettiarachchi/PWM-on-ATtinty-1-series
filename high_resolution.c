#define F_CPU 3333333UL
#include <avr/io.h>
#include <util/delay.h>


int main(void){
    PORTB.DIRSET = PIN0_bm;                                 // PB0 = WO0

    TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc     // single-slope PWM
                      | TCA_SINGLE_CMP0EN_bm;                // enable WO0 (PB0)
    TCA0.SINGLE.PER  = 3332;                                 // ~1 kHz @ 3.333 MHz, presc=1
    TCA0.SINGLE.CMP0 = 1666;                                 // ~50% duty (0..3332)
    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc            // prescaler = 1  (max resolution)
                      | TCA_SINGLE_ENABLE_bm;

    while(1){ /* set TCA0.SINGLE.CMP0 = 0..3332 */
   for(uint32_t x = 0; x < 3332; x++){
             TCA0.SINGLE.CMP0 = x; 
             _delay_ms(1);
             
        }
    
    }
}
