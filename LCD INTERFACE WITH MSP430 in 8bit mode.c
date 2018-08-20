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
    P2DIR |= 0xFF;//set p2 as output
    P1DIR |= 0xFF;//set p1 as output
    P2OUT &= 0x00;//initialize as 0
    P1OUT &= 0x00;//initialize as 0
//command instructions to set lcd
    send_command(0x38); //8 bit mode
    send_command(0x0E);//clear display
    send_command(0x01);//display on cursor on cursor blink
    send_command(0x06);//increment cursor
    send_command(0x80);//cursor position
}
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;//stop watchdog timer
    //initialize lcd
    lcd_init();

    send_string("Ayushman koul");
    send_command(0xC0);
    send_string("Engineer");

    while(1){}
}

