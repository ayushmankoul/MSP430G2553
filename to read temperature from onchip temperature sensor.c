#include<msp430g2553.h>
void tempInit()
{

   // Configure ADC to Sample Temperature Sensor
   ADC10CTL1 = INCH_10 + ADC10DIV_4; //input channel to Temp Sensor and ADC10CLK/5
   ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON ;
   //VR+ = VREF+=1.5Vand VR- = AVSS *
   //64 x ADC10CLK
   //internal reference on
   //adc interrupt enable
}
int tempOut()
{
        int delay;
        int t=0,x=0;
        for( delay = 240; delay > 0; delay-- );  // delay to allow reference to settle
        ADC10CTL0 |= ENC + ADC10SC;        // Sampling and conversion start
        while(ADC10CTL1 & BUSY);         //continues conversion of input signal as long as operation is active.
        t=ADC10MEM;                       //store value in t
        ADC10CTL0&=~ENC;                    //disables the conversion
        x=(t*27069-18169625)>>16;
        return x;
}
void main(void)
{
    volatile int temp;


    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    temp=0;
    tempInit();


    while(1)
       {
           P1DIR = 0x41;//configure led pins to output
           temp=tempOut();//read temp
           if(temp>25)
           {
               P1OUT =0x01;

           }
           else
           {
               P1OUT =0X40;
           }



       }
   }


