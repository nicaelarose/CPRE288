#include "uart.h"

volatile int *uart_event_ptr; //Pointer for the UART1 interrupt event
volatile int *uart_char_ptr;  //Pointer for the character to send/recieve

/*
 * This function will initiate the appropriate UART1 interrupts.
 * It also sets the uart pointers equal to the correct values.
 * @author Nick Battani, Swechha Ghimire
 *
 * @param int *uart_event_addr
 * @param char *uart_char_addr
 *
 * @data 02/26/2019
 */
void uart_interrupts_init(int *uart_event_addr, char *uart_char_addr){

    uart_event_ptr = uart_event_addr;
    uart_char_ptr = uart_char_addr;

    //Turn off UART1 while we set it up
    UART1_CTL_R &= ~(UART_CTL_UARTEN);
    //Clear interrupt flags
    UART1_ICR_R = (UART_ICR_TXIC | UART_ICR_RXIC);
    //Enable send and receive raw interrupts
    UART1_IM_R |= UART_IM_TXIM | UART_IM_RXIM;
    //Set priority of usart1 interrupt to 1. group 1 bits 21-23
    NVIC_PRI1_R |= 0x00200000;
    //Enable interrupt for IRQ 6 set bit 6
    NVIC_EN0_R |= 0x00000040;
    //Tell cpu to use ISR handler for uart1
    IntRegister(INT_UART1, UART1_Handler);
    //Enable global interrupts
    IntMasterEnable();

    //Re-enable enable RX, TX, and uart1
    UART1_CTL_R = (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);

}

/*
 * This function will initiate the appropriate UART1 GPIO pins and registers
 * @author Nick Battani, Swechha Ghimire
 *
 * @data 02/26/2019
 */
void uart_init(void) {

     //Enable clock to GPIO, R1 = port B
     SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
     //Enable clock to UART1, R1 = UART1. ***Must be done before setting Rx and Tx (See DataSheet)
     SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R1;
     //Enable alternate functions on port b pins 0 and 1
     GPIO_PORTB_AFSEL_R |= (BIT0 | BIT1);
     //Enable Rx and Tx on port B on pins 0 and 1
     GPIO_PORTB_PCTL_R |= 0x00000011;
     //Set pin 0 and 1 to digital
     GPIO_PORTB_DEN_R |= (BIT0 | BIT1);
     //Set pin 0 to Rx or input
     GPIO_PORTB_DIR_R &= ~BIT0;
     //Set pin 1 to Tx or output
     GPIO_PORTB_DIR_R |= BIT1;
     //Baud rate for 115,200
     uint16_t iBRD115 = 8;
     uint16_t fBRD115 = 44;
     //Baud rate for 9600
     uint16_t iBRD96 = 104 ;
     uint16_t fBRD96 = 11;
     //Turn off uart1 while we set it up
     UART1_CTL_R &= ~(UART_CTL_UARTEN);
     //Set baud rate
     UART1_IBRD_R = iBRD115;
     UART1_FBRD_R = fBRD115;
     //Set frame, 8 data bits, 1 stop bit, no parity, no FIFO
     UART1_LCRH_R = UART_LCRH_WLEN_8 ;
     //Use system clock as source
     UART1_CC_R = UART_CC_CS_SYSCLK;
     //Re-enable enable RX, TX, and uart1
     UART1_CTL_R = (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);

 }

/*
 * This function will send a character over UART1
 * @author Nick Battani, Swechha Ghimire
 *
 * @param char data
 *
 * @data 02/26/2019
 */
void uart_sendChar(float data){

     //wait until there is room to send data
     while(UART1_FR_R & 0x20)
    {

    }
     //send data
     UART1_DR_R = data;

}


/*
 * This function will receive a character over UART1
 * @author Nick Battani, Swechha Ghimire
 *
 * @param char data
 *
 * @data 02/26/2019
 */
char uart_receive(void){

    char data = 0;
     //wait to receive
     while(UART1_FR_R & UART_FR_RXFE)
    {

    }
    //mask the 4 error bits and grab only 8 data bits
    data = (char)(UART1_DR_R & 0xFF);

    return data;
}

/*
 * This function is the UART1 Handler if the UART1 interrupt is triggered
 * @author Nick Battani, Swechha Ghimire
 *
 * @data 02/26/2019
 */
void UART1_Handler(void){
    //Received a byte
    if(UART1_MIS_R & UART_MIS_RXMIS){
        //Clear interrupt
        UART1_ICR_R |= UART_ICR_RXIC;
        //Set the flag
        *uart_event_ptr = 1;
        //Set the character
        *uart_char_ptr = uart_receive();
    }
    //Needs to send a byte
    else if(UART1_MIS_R & UART_MIS_TXMIS){
        //Clear the interrupt
        UART1_ICR_R |= UART_ICR_TXIC;
    }
}
/*
 * This function will send a string over UART1
 * @author Nick Battani, Swechha Ghimire
 *
 * @param char data[]
 *
 * @data 02/26/2019
 */
void uart_sendStr(const char *data)
{
    //until we reach a null character
    while (*data != '\0')
    {
        //send the current character
        uart_sendChar(*data);
        // increment the pointer.
        data++;
    }

}
