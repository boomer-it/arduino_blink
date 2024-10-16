#define F_CPU 16000000UL  // Define CPU clock speed as 16 MHz
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    // Set TX (PD1) and RX (PD0) as output by setting the corresponding bits in DDRD
    DDRD |= (1 << PD1);  // TX (Pin 1) as output
    DDRD |= (1 << PD0);  // RX (Pin 0) as output

    while (1) {
        // Blink TX LED (Pin 1)
        PORTD |= (1 << PD1);   // Set PD1 high (TX LED on)
        _delay_ms(500);        // Delay 500ms
        PORTD &= ~(1 << PD1);  // Set PD1 low (TX LED off)
        
        // Blink RX LED (Pin 0)
        PORTD |= (1 << PD0);   // Set PD0 high (RX LED on)
        _delay_ms(500);        // Delay 500ms
        PORTD &= ~(1 << PD0);  // Set PD0 low (RX LED off)
    }

    return 0;
}

