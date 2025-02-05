#include <msp430fr6989.h>


/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= BIT0;              // BIT0 output
	P1DIR &= ~BIT1;             // BIT1 input
   // PM5CTL0 &= ~LOCKLPM5;       //We set the LOCKLPM5 bit to 0 in the PM5CTL0 register while leaving other bits unchanged.

	P1OUT &= ~BIT0;             // BIT1 0
	P1REN |= BIT1;              // Pullup pulldown enable
	P1OUT |= BIT1;              // Pull UP

	PM5CTL0 &= ~LOCKLPM5;       //We set the LOCKLPM5 bit to 0 in the PM5CTL0 register while leaving other bits unchanged.
	while(1){

	    if(P1IN & BIT1){
	        P1OUT &= ~BIT0;     // Led is not active when the button not pressed
	    }
	    else{
	        P1OUT |= BIT0;
	    }
	}





