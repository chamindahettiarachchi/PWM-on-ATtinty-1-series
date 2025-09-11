#define F_CPU 3333333UL
#include <avr/io.h>
#include <util/delay.h>


int main(void){
    PORTB.DIRSET = PIN0_bm;                                // PB0 = output (WO0)

    TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc    // single-slope PWM
                      | TCA_SINGLE_CMP0EN_bm;               // enable WO0
    TCA0.SINGLE.PER  = 255;                                 // PWM period  (~203 Hz @ 3.333 MHz, /64)
    TCA0.SINGLE.CMP0 = 128;                                 // ~50% duty
    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV64_gc          // prescaler /64
                      | TCA_SINGLE_ENABLE_bm;               // start

    while(1){ /* change duty by writing TCA0.SINGLE.CMP0 (0..255) */
    
        for(uint8_t x = 0; x < 256; x++){
             TCA0.SINGLE.CMP0 = x; 
             _delay_ms(7);
             
        }
    }
}
