#include<msp430g2553.h>
void main(void)
{
    volatile int i;
    //======== WATCH DOG TIMER INITIALIAZE=====
    WDTCTL = WDTPW | WDTHOLD;

    //=====INITIALIZE TIMER=======
    TACTL |= 0x0114; //Used ACLK with divider(1) and timer module up mode control and clearing the previous timer value as well as divider and mode.
    TACCR0 = 0x0401;//this holds the data for comparison to timer value in register.
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
