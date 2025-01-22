#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 8000000UL

int main(void) {
    /*DDRB |= 0x01;
    DDRB |= 0x02;
    DDRA = 0x00;
    PORTA = 0x01;*/

    /*DDRB |= (1<<PB0) | (1<<PB1) | (1<<PB2) | (1<<PB3);
    DDRA &= ~(1<<PA0);
    PORTA |= (1<<PA0);*/


    /*uint8_t counter = 0;

    while (1) {

        /*PORTB ^= 0x02;
        _delay_ms(500);

        if ((PINA & 0x01)==0) {
            _delay_ms(20);
            if ((PINA & 0x01) == 0) {
                PORTB |= 0x01;
            }
        }
        else {
            PORTB &= ~0x01;
        }

        if ((PINA & (1<<PA0)) == 0) {
            _delay_ms(20);
            if ((PINA & (1<<PA0)) == 0) {
                counter++;
                if (counter > 15) {
                    counter = 0;
                }
            }
        }
        PORTB = counter;
        _delay_ms(200);

    }*/
    return 0;
}
