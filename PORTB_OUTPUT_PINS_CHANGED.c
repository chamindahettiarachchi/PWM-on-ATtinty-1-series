#define F_CPU 3333333UL
#include <avr/io.h>


int main(void){
    // 1) Remap WO0..2 to alternate PORTB pins (PB3..PB5)
    PORTMUX.CTRLC |= PORTMUX_TCA00_bm | PORTMUX_TCA01_bm | PORTMUX_TCA02_bm;

    // 2) Make PB3..PB5 outputs
    PORTB.DIRSET = PIN3_bm | PIN4_bm | PIN5_bm;

    // 3) Configure TCA0 single-slope PWM, one frequency, 3 independent duties
    TCA0.SINGLE.CTRLA = 0;    // stop while configuring
    TCA0.SINGLE.CTRLD = 0;    // ensure SINGLE mode

    TCA0.SINGLE.PER  = 255;   // PWM freq = F_CPU/(prescale*(PER+1))
    TCA0.SINGLE.CMP0 = 64;    // WO0 -> PB3  (~25%)
    TCA0.SINGLE.CMP1 = 128;   // WO1 -> PB4  (~50%)
    TCA0.SINGLE.CMP2 = 192;   // WO2 -> PB5  (~75%)

    TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc
                      | TCA_SINGLE_CMP0EN_bm
                      | TCA_SINGLE_CMP1EN_bm
                      | TCA_SINGLE_CMP2EN_bm;

    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc | TCA_SINGLE_ENABLE_bm; // start

    while(1){ }
}
