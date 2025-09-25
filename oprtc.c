#define F_CPU 3333333UL
#include <avr/io.h>
#include <util/delay.h>


int main(void){
    // 1) Remap WO0..2 to alternate PORTB pins (PB3..PB5)
   PORTC.DIRSET = PIN3_bm;                  // PC3 output
PORTMUX.CTRLC |= (1<<3);                 // TCA03 bit -> WO3 on PC3

TCA0.SPLIT.CTRLD = TCA_SPLIT_SPLITM_bm;  // enable Split mode
TCA0.SPLIT.HPER  = 255;                  // high-byte timer period
TCA0.SPLIT.HCMP0 = 128;                  // ~50% duty on WO3
TCA0.SPLIT.CTRLB = TCA_SPLIT_HCMP0EN_bm; // enable WO3 output
TCA0.SPLIT.CTRLA = TCA_SPLIT_CLKSEL_DIV64_gc | TCA_SPLIT_ENABLE_bm;

    while(1){_delay_ms(1000);TCA0.SPLIT.HCMP0 = 255;_delay_ms(1000);TCA0.SPLIT.HCMP0 = 75;   }
