
#define F_CPU 3333333UL
#include <avr/io.h>

int main(void)
{
    // Make PA3, PA4, PA5 outputs (WO3, WO4, WO5 in split mode)
    PORTA.DIRSET = PIN3_bm | PIN4_bm | PIN5_bm;

    // Optional: ensure routing is to PORTA, not PORTC (default is 0 = PORTA)
    // If your headers define these, you can uncomment the next line:
    // PORTMUX.CTRLC &= ~(PORTMUX_TCA03_bm | PORTMUX_TCA04_bm | PORTMUX_TCA05_bm);

    // --- Configure TCA0 in Split Mode (two independent 8-bit timers: L and H)
    TCA0.SPLIT.CTRLA = 0;                     // stop while configuring
    TCA0.SPLIT.CTRLD = TCA_SPLIT_SPLITM_bm;   // enable Split mode

    // High half (drives WO3/WO4/WO5 → PA3/PA4/PA5)
    // PWM frequency: f_pwm_H = (F_CPU / prescaler) / (HPER+1)
    // Here: prescaler = /64, HPER = 255 → f ≈ 3333333/64/256 ≈ 204 Hz
    TCA0.SPLIT.HPER  = 255;                   // period (8-bit top)
    TCA0.SPLIT.HCMP0 = 64;                    // ~25% duty on WO3 (PA3)
    TCA0.SPLIT.HCMP1 = 128;                   // ~50% duty on WO4 (PA4)
    TCA0.SPLIT.HCMP2 = 192;                   // ~75% duty on WO5 (PA5)

    // Enable the three H-half compare outputs
    TCA0.SPLIT.CTRLB = TCA_SPLIT_HCMP0EN_bm
                     | TCA_SPLIT_HCMP1EN_bm
                     | TCA_SPLIT_HCMP2EN_bm;

    // Start TCA0 with prescaler /64
    TCA0.SPLIT.CTRLA = TCA_SPLIT_CLKSEL_DIV64_gc | TCA_SPLIT_ENABLE_bm;

    while (1) {
        // Adjust duty live if you want:
        // TCA0.SPLIT.HCMP0 = ...;  // PA3
        // TCA0.SPLIT.HCMP1 = ...;  // PA4
        // TCA0.SPLIT.HCMP2 = ...;  // PA5
    }
}
