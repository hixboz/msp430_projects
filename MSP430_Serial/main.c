//#include <msp430.h>

///* UCAxIE UART Control Bits */
//#define UCTXCPTIE              (0x0008)       /* UART Transmit Complete Interrupt Enable */
//#define UCSTTIE                (0x0004)       /* UART Start Bit Interrupt Enalble */
//#define UCTXIE                 (0x0002)       /* UART Transmit Interrupt Enable */
//#define UCRXIE                 (0x0001)       /* UART Receive Interrupt Enable */
///* UCAxIFG UART Control Bits */
//#define UCTXCPTIFG             (0x0008)       /* UART Transmit Complete Interrupt Flag */
//#define UCSTTIFG               (0x0004)       /* UART Start Bit Interrupt Flag */
//#define UCTXIFG                (0x0002)       /* UART Transmit Interrupt Flag */
//#define UCRXIFG                (0x0001)       /* UART Receive Interrupt Flag */
///* USCI Interrupt Vector UART Definitions */
//#define USCI_NONE              (0x0000)       /* No Interrupt pending */
//#define USCI_UART_UCRXIFG      (0x0002)       /* Interrupt Vector: UCRXIFG */
//#define USCI_UART_UCTXIFG      (0x0004)       /* Interrupt Vector: UCTXIFG */
//#define USCI_UART_UCSTTIFG     (0x0006)       /* Interrupt Vector: UCSTTIFG */
//#define USCI_UART_UCTXCPTIFG   (0x0008)       /* Interrupt Vector: UCTXCPTIFG */
//// UCAxCTLW0 UART-Mode Control Bits
//#define UCPEN                  (0x8000)       /* Async. Mode: Parity enable */
//#define UCPAR                  (0x4000)       /* Async. Mode: Parity     0:odd / 1:even */
//#define UCMSB                  (0x2000)       /* Async. Mode: MSB first  0:LSB / 1:MSB */
//#define UC7BIT                 (0x1000)       /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */
//#define UCSPB                  (0x0800)       /* Async. Mode: Stop Bits  0:one / 1: two */
//#define UCMODE1                (0x0400)       /* Async. Mode: USCI Mode 1 */
//#define UCMODE0                (0x0200)       /* Async. Mode: USCI Mode 0 */
//#define UCSYNC                 (0x0100)       /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */
//#define UCSSEL1                (0x0080)       /* USCI 0 Clock Source Select 1 */
//#define UCSSEL0                (0x0040)       /* USCI 0 Clock Source Select 0 */
//#define UCRXEIE                (0x0020)       /* RX Error interrupt enable */
//#define UCBRKIE                (0x0010)       /* Break interrupt enable */
//#define UCDORM                 (0x0008)       /* Dormant (Sleep) Mode */
//#define UCTXADDR               (0x0004)       /* Send next Data as Address */
//#define UCTXBRK                (0x0002)       /* Send next Data as Break */
//#define UCSWRST                (0x0001)       /* USCI Software Reset */
//
//// UCAxCTLW0 UART-Mode Control Bits
//#define UCSSEL1_L              (0x0080)       /* USCI 0 Clock Source Select 1 */
//#define UCSSEL0_L              (0x0040)       /* USCI 0 Clock Source Select 0 */
//#define UCRXEIE_L              (0x0020)       /* RX Error interrupt enable */
//#define UCBRKIE_L              (0x0010)       /* Break interrupt enable */
//#define UCDORM_L               (0x0008)       /* Dormant (Sleep) Mode */
//#define UCTXADDR_L             (0x0004)       /* Send next Data as Address */
//#define UCTXBRK_L              (0x0002)       /* Send next Data as Break */
//#define UCSWRST_L              (0x0001)       /* USCI Software Reset */
//
//// UCAxCTLW0 UART-Mode Control Bits
//#define UCPEN_H                (0x0080)       /* Async. Mode: Parity enable */
//#define UCPAR_H                (0x0040)       /* Async. Mode: Parity     0:odd / 1:even */
//#define UCMSB_H                (0x0020)       /* Async. Mode: MSB first  0:LSB / 1:MSB */
//#define UC7BIT_H               (0x0010)       /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */
//#define UCSPB_H                (0x0008)       /* Async. Mode: Stop Bits  0:one / 1: two */
//#define UCMODE1_H              (0x0004)       /* Async. Mode: USCI Mode 1 */
//#define UCMODE0_H              (0x0002)       /* Async. Mode: USCI Mode 0 */
//#define UCSYNC_H               (0x0001)       /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */
//// UCAxCTLW1 UART-Mode Control Bits
//#define UCGLIT1                (0x0002)       /* USCI Deglitch Time Bit 1 */
//#define UCGLIT0                (0x0001)       /* USCI Deglitch Time Bit 0 */
//
//// UCAxCTLW1 UART-Mode Control Bits
//#define UCGLIT1_L              (0x0002)       /* USCI Deglitch Time Bit 1 */
//#define UCGLIT0_L              (0x0001)       /* USCI Deglitch Time Bit 0 */
#include <msp430fr6989.h>
#define redLED BIT0 // Red at P1.0
#define greenLED BIT7 // Green at P9.7


#define FLAGS UCA1IFG // Contains the transmit & receive flags
#define RXFLAG UCRXIFG // Receive flag
#define TXFLAG UCTXIFG // Transmit flag
#define TXBUFFER UCA1TXBUF // Transmit buffer
#define RXBUFFER UCA1RXBUF // Receive buffer

void Initialize_UART(void);
void uart_write_char(unsigned char ch);
unsigned char uart_read_char(void);

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // Stop WDT
    PM5CTL0 &= ~LOCKLPM5; // Enable GPIO pins

    P1DIR |= redLED;
    P1OUT &= ~redLED;
    P9DIR |= greenLED;
    P9OUT &= ~greenLED;

    int i;
   // char ch;
    char text[] = "FAYDALI FELSEFE\r\n";
    char newLine = '\n';
    char carriage = '\r';

    // eUSCI Module Configuration
    Initialize_UART();

    while (1)
    {
        // Transmit character 0 - 9
//        for (ch = '0'; ch <= '9'; ch++)
//        {
//            for (i = 0; i < 30000; i++){}
//            P1OUT |= redLED;
//            uart_write_char(ch);
//            uart_write_char(newLine);
//            uart_write_char(carriage);
//            for (i = 0; i < 30000; i++){}
//            P1OUT &= ~redLED;
//        }
        int i=0;
        for (i=0; i < sizeof(text); i++)
        {
            for (i = 0; i < 30000; i++){}
            P1OUT |= redLED;
            uart_write_char(text[i]);
            uart_write_char(newLine);
            uart_write_char(carriage);
            for (i = 0; i < 30000; i++){}
            P1OUT &= ~redLED;
        }

        if (uart_read_char() == '1')
        {
            P9OUT |= greenLED;
        }

        if (uart_read_char() == '2')
        {
            P9OUT &= ~greenLED;
        }

    }

}


// Configure UART to the popular configuration
// 9600 baud, 8-bit data, LSB first, no parity bits, 1 stop bit
// no flow control
// Initial clock: SMCLK @ 1.048 MHz with oversampling
void Initialize_UART(void){
    // Divert pins to UART functionality
    P3SEL1 &= ~(BIT4|BIT5);
    P3SEL0 |= (BIT4|BIT5);

    // Use SMCLK clock; leave other settings default
    UCA1CTLW0 |= UCSSEL_2;

    // Configure the clock dividers and modulators
    // UCBR=6, UCBRF=13, UCBRS=0x22, UCOS16=1 (oversampling)
    UCA1BRW = 6;
    UCA1MCTLW = UCBRS5|UCBRS1|UCBRF3|UCBRF2|UCBRF0|UCOS16;

    // Exit the reset state (so transmission/reception can begin)
    UCA1CTLW0 &= ~UCSWRST;
}

// Transmit a byte over UART
// When byte is copied to trasmit buffer, transmit flag = 0 automatically
// When transmission finishes, the transmit flag goes back to one
void uart_write_char(unsigned char ch){

    // Wait for any ongoing transmission to complete
    while ( (FLAGS & TXFLAG)==0 ) {}

    // Write the byte to the transmit buffer
    TXBUFFER = ch;
}

// Receives a byte over UART
// Returns the byte; if none received, returns NULL
// Byte is received, the receive flag becomes 1
// When copy the byte from receive buffer, the receive flag = 0 automatically
unsigned char uart_read_char(void){

    unsigned char temp;

    // Return NULL if no byte received
    if( (FLAGS & RXFLAG) == 0)
        return '\0';

    // Otherwise, copy the received byte (clears the flag) and return it
    temp = RXBUFFER;

    return temp;
}
