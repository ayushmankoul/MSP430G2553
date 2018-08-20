#include<msp430g2553.h>
void main(void)
{
    volatile int i;
    //======== WATCH DOG TIMER INITIALIAZE=====
    WDTCTL = WDTPW | WDTHOLD;

    //=====INITIALIZE TIMER=======
    TACTL |= 0x02f4; //Used SMCLK with divider(8) and timer module up/down mode control and clearing the previous timer value as well as divider and mode.
    TACCR0 = 0xf43f;//this holds the data for comparison to timer value in register.
    // set the timer into compare mode and set mode and enabled the interrupt when comparison occurs interrupt is generated.
    P1DIR = 0x41;
    while(1)
    {

        if ((TACTL & 0x0001)==1)
        {
  //CHECK whether the interrupt bit is set then you toggle your led
        P1OUT ^= 0x41;
        TACTL &= 0Xffffe;

        }

   ///  reset the interrupt flag
    }
}
