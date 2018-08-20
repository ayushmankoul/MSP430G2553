#include<msp430g2553.h>

unsigned int i;
unsigned int j;
void delay(unsigned int k)
{
    for(j=0;j<=k;j++)
    {
    for(i=0;i<1000;i++);
    }
}
void data_write(void)
{
    P2OUT |=BIT2; //ENABLE HIGH
    delay(2);
    P2OUT &=~BIT2; //ENABLE LOW
}

void data_read(void)
{
    P2OUT &=~BIT2; //ENABLE LOW
    delay(2);
    P2OUT |=BIT2; //ENABLE HIGH
}
void check_busy(void)
{
    P1DIR &= ~(BIT7); // make P1.7 as input
    while((P1IN&BIT7)==1)
    {
        data_read();
    }
    P1DIR |= BIT7; // make P1.7 as output
}

void send_command(unsigned char cmd)
{
    check_busy();
    P2OUT = P2OUT & (~BIT1); //define rw low
    P2OUT = P2OUT & (~BIT0); // define RS low
    P1OUT = (P1OUT & 0x00)|(cmd);
    data_write(); // give enable trigger
}
void send_data(unsigned char data)
{
    check_busy();
    P2OUT = P2OUT & (~BIT1); //define rw low
    P2OUT = P2OUT | BIT0; // define RS high
    P1OUT = (P1OUT & 0x00)|(data);
    data_write(); // give enable trigger
}
void send_string(char *s)
{
    while(*s)
    {
        send_data(*s);
        s++;
    }
}
void lcd_init(void)
{
    P2DIR |= 0xFF;
    P1DIR |= 0xFF;
    P2OUT &= 0x00;
    P1OUT &= 0x00;
    send_command(0x38); //8 bit mode
    send_command(0x0E);//clear display
    send_command(0x01);//display on cursor on cursor blink
    send_command(0x06);//increment cursor
    send_command(0x80);//cursor position
}
void tempInit()
{
    ADC10CTL0=SREF_1 + REFON + ADC10ON + ADC10SHT_3 ; //1.5V ref,Ref on,64 clocks for sample
    ADC10CTL1=INCH_10+ ADC10DIV_3; //temp sensor is at 10 and clock/4
}
int tempOut()
{
    int t=0;
    __delay_cycles(1000);              //wait 4 ref to settle
    ADC10CTL0 |= ENC + ADC10SC;      //enable conversion and start conversion
    while(ADC10CTL1 & BUSY);         //wait..i am converting..pum..pum..
    t=ADC10MEM;                       //store val in t
    ADC10CTL0&=~ENC;                     //disable adc conv
    return(int) ((t * 27069L - 18169625L) >> 16); //convert and pass
}

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;//stop watchdog timer
    //initialize lcd
    lcd_init();


    volatile int temp;
    unsigned int m;

    temp=0;
    tempInit();
    temp=tempOut();
    if(temp>25){
        send_string("temp is above 25");
    }
    send_command(0xC0);  
    int result[2];
    //conversion to ascii values
    result[0]=temp%10;
    temp=temp/10;
    result[1]=temp%10;
    result[0]|=0x30;
    result[1]|=0x30;
    for(m=0;m<3;m++)
    {
        send_data(result[2-m]);
    }
}

