#include <msp430fr6989.h>

#define redLED BIT0 // Red at P1.0
#define greenLED BIT7 // Green at P9.7


#define FLAGS UCA1IFG // Contains the transmit & receive flags
#define RXFLAG UCRXIFG // Receive flag
#define TXFLAG UCTXIFG // Transmit flag
#define TXBUFFER UCA1TXBUF // Transmit buffer
#define RXBUFFER UCA1RXBUF // Receive buffer

#define ACLK 0x0100 // Timer ACLK source
#define UP 0x0010 // Timer UP mode
#define ENABLE_PINS 0xFFFE // Required to use inputs and outputs
#define ENABLE_PINS   0xFFFE // Enables inputs and outputs

void ADC_SETUP(void); // Used to setup ADC12 peripheral
void Initialize_UART(void);
void uart_write_char(unsigned char ch);
unsigned char uart_read_char(void);

const int x1=1;
const int x2=1;
volatile int multiplied_value,duty;

int main()
{
    WDTCTL = WDTPW | WDTHOLD; // Stop WDT
    PM5CTL0 &= ~LOCKLPM5; // Enable GPIO pins

    //PM5CTL0 = ENABLE_PINS; // Enable inputs and outputs
    P1DIR = BIT0; // Set RED LED to output
    P9DIR = BIT7; // Set GREEN LED to output

    int i;
    char ch;
    //char text[] = "HELLO!!!\r\n";
    char newLine = '\n';
    char carriage = '\r';
    char buffer_adc[10]={0};
    int adc_value = 0 ;
    int counter_uart =0;
    long veri = 0x12345678;
    // eUSCI Module Configuration
    Initialize_UART();



    ADC_SETUP(); // Sets up ADC peripheral
    while(1)
    {
//        while(counter_uart<5)
//        {
//            //for (i = 0; i < 30000; i++){}
//            P1OUT |= redLED;
//            uart_write_char(text[0]);
//            uart_write_char(text[1]);
//            uart_write_char(text[2]);
//            uart_write_char(text[3]);
//            uart_write_char(text[4]);
//            uart_write_char(newLine);
//            uart_write_char(carriage);
//            counter_uart++;
//
//            //for (i = 0; i < 30000; i++){}
//            //P1OUT &= ~redLED;
//        }

        ADC12CTL0 = ADC12CTL0 | ADC12ENC; // Enable conversion
        ADC12CTL0 = ADC12CTL0 | ADC12SC; // Start conversion

        while (ADC12CTL0 & ADC12BUSY);
        //while( ADC12BUSY == 1)
//        while( ADC12BUSY == 1)
//        {

        multiplied_value = (ADC12MEM0);

        if (multiplied_value > 0x800) // If input > 1.65V
        {
           P1OUT = BIT0; // Turn on red LED
           P9OUT = 0x00; // Turn off green LED
        }
        else // Else input <= 1.65V
        {
           P1OUT = 0x00; // Turn off red LED
           P9OUT = BIT7; // Turn on green LED
        }

/*
            unsigned int my_integer = 123;
            char ascii_buffer[3]; // Assuming 3 characters for max 3-digit integer + null terminator

            void transmit_integer(unsigned int value) {
              // Convert integer to ASCII string (custom function or library)
              // This example assumes a separate conversion function `itoa` that populates the ascii_buffer
              itoa(value, ascii_buffer);

              // Loop to transmit each character
              int i = 0;
              while (ascii_buffer[i] != '\0') {
                // Wait for transmitter to be ready
                while (UCA1STAT & UCA1TXBUSY);

                // Transmit the ASCII character
                UCA1TXBUF = ascii_buffer[i];
                i++;
              }
            }
*/
            unsigned char buff={0x01};
            //UCA1TXBUF = buff;



            for(i=0; i<2;i++) {

                UCA1TXBUF  =(unsigned char) (multiplied_value >> (i * 8)) & 0xFF;//sends LSB first (0x0942) _ comes as 42 09 on terminal
                _delay_cycles(50000000);
            }

             int a=1;
            ////////////////////////////
            // Veriyi UART �zerinden g�nder

//            while ( (FLAGS & TXFLAG)==0 ) {}
//            UCA1TXBUF = multiplied_value & 0xFF;
//            _delay_cycles(30000);
//            UCA1TXBUF = (multiplied_value >> 8) & 0xFF;


//            P1DIR |= BIT5;             // P1.5 to output
//            P1SEL1 |= BIT5;             // P1.5 to TA0.1
//
//
//            TA0CCTL1 = OUTMOD_7;          // CCR1 reset/set
//            TA0CCR1 = multiplied_value*65536/3.3 ;
//            adc_value = multiplied_value*65536/3.3 ;
//            duty=TA0CCR1;// CCR1 PWM duty cycle
//            TA0CCR0 =1000;             // PWM Period
//            TA0CTL = TASSEL_2 + MC_1;   // SMCLK, up mode
//
//            _BIS_SR(LPM0_bits);        // Enter LPM0
//        }




//        sprintf(buffer_adc, "%d",  multiplied_value);
//        int j=0;
//        for (j=0; j < sizeof(buffer_adc); j++){
//            uart_write_char(buffer_adc[i]);
            //for (i = 0; i < 30000; i++){}
            //uart_write_char("A");
//        }
       // counter_uart=0;
    }
}

void ADC_SETUP(void)
{
    #define ADC12_SHT_16 0x0200 // 16 clock cycles for sample and hold
    #define ADC12_ON 0x0010 // Used to turn ADC12 peripheral on
    #define ADC12_SHT_SRC_SEL 0x0200 // Selects source for sample & hold
    #define ADC12_12BIT 0x0020 // Selects 12-bits of resolution
    #define ADC12_P92 0x000A // Use input P9.2 for analog input
    //#define ADC12_P43 0x000A
    //#define ADC12_P32 0x000A
    //#define ADC12_P93 0x000A
    //#define ADC12_P14 0x000A
    //#define ADC12_P20 0x000A
    //#define ADC12_P41 0x000A
    ADC12CTL0 = ADC12_SHT_16 | ADC12_ON ; // Turn on, set sample & hold time
    ADC12CTL1 = ADC12_SHT_SRC_SEL; // Specify sample & hold clock source
    ADC12CTL2 = ADC12_12BIT; // 12-bit conversion results
    ADC12MCTL0 = ADC12_P92; // P9.2 is analog input
    //ADC12MCTL1 = ADC12_P43;
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
