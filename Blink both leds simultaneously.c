#include<msp430g2553.h>
void main(void)
{
    volatile int i;
    //======== WATCH DOG TIMER INITIALIAZE=====
    WDTCTL = WDTPW | WDTHOLD;



    P1DIR = 0x41;// set the led pins as output by configuring as 1 for output
    while(1)
    {

        // toggle both leds simultaneously
        P1OUT ^= 0x41;
        for(i=0;i<20000;i++); //give delay while blinking

        }

}

