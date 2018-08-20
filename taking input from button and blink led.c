#include <msp430.h>

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; //Stop watchdog timer 
    P1DIR &= ~BIT3 ; //explicitly making P1.3 as Input - even though by default its Input
    P1REN = BIT3; //Enable Pullup/down
    P1OUT = BIT3; //Select Pullup

    P1DIR |= BIT6; //Configuring P1.6(LED2) as Output
    P1OUT &= ~BIT6; //Turn off LED2 initially

    while(1)
    {
        if( !(P1IN & BIT3) )
        {
            P1OUT |= BIT6; //Input LOW - turn led ON
        }
        else
        {
            P1OUT &= ~BIT6; //Input HIGH - turn led OFF
        }
    }

    //return 0; //normally this won't execute
}
