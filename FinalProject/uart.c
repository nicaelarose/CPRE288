/*
*   uart.c
*
*   @author
*   @date
*/

#include "uart.h"
#include <stdint.h>


void uart_init(void){
	//TODO
  //enable clock to GPIO port B
  SYSCTL_RCGCGPIO_R |= 0b00010;

  //enable clock to UART1
  SYSCTL_RCGCUART_R |= 0b00000010;

  //wait for GPIOB and UART1 peripherals to be ready
  while ((SYSCTL_PRGPIO_R & 0b00000000 )) {};
  while ((SYSCTL_PRUART_R & 0b00000000 )) {};

  //enable alternate functions on port B pins
  GPIO_PORTB_AFSEL_R = 0x03;//0x0FF;

  //enable digital functionality on port B pins
  GPIO_PORTB_DEN_R = 0x03;//0x0FF;


  //enable UART1 Rx and Tx on port B pins
  GPIO_PORTB_PCTL_R = 0b00000011;

  //calculate baud rate
  uint16_t iBRD = 8; //use equations
  uint16_t fBRD = 44; //use equations

  //turn off UART1 while setting it up
  UART1_CTL_R &= 0xFFFFFFFE;

  //set baud rate
  //note: to take effect, there must be a write to LCRH after these assignments
  UART1_IBRD_R = iBRD;
  UART1_FBRD_R = fBRD;

  //set frame, 8 data bits, 1 stop bit, no parity, no FIFO
  //note: this write to LCRH must be after the BRD assignments
  UART1_LCRH_R = 0b01100000;

  //use system clock as source
  //note from the datasheet UARTCCC register description:
  //field is 0 (system clock) by default on reset
  //Good to be explicit in your code
  UART1_CC_R = 0x0;

  //re-enable UART1 and also enable RX, TX (three bits)
  //note from the datasheet UARTCTL register description:
  //RX and TX are enabled by default on reset
  //Good to be explicit in your code
  UART1_CTL_R |= 0b1100000001;
  SYSCTL_RCGCGPIO_R |= 0b00010;
      while ((SYSCTL_PRGPIO_R & 0b00010) == 0) {};
          GPIO_PORTB_DEN_R |= 0x0FF;
          GPIO_PORTB_AFSEL_R |= 0x0FF;//p672
      GPIO_PORTB_PCTL_R &= 0x00000011;     // Force 0's in the desired locations p688
      GPIO_PORTB_PCTL_R |= 0x00000011;     // Force 1's in the desired locations
          // Or see the notes for a coding alternative to assign a value to the PCTL field

     // (Uncomment ME for UART init part of lab)
     //cyBot_uart_init_last_half();  // Complete the UART device configuration


}
/*
// Send a byte over UART1 from CyBot to PuTTY
void uart_sendChar(char data){
	//TODO
    while((UART1_FR_R & 0x20) != 0);
    UART1_DR_R = data;
}

// CyBot waits (i.e. blocks) to receive a byte from PuTTY
// returns byte that was received by UART1
char uart_receive(void){
	//TODO
    uint32_t temp;
    char data;

    while((UART1_FR_R & 0x10) != 0){};
    temp=UART1_DR_R;
    if(temp & 0xF00){
        GPIO_PORTB_DATA_R = 0xF;
    }
    else{
        data = (char)(UART1_DR_R & 0xFF);
    }
    return data;
}

// Send a string over UART1
// Sends each char in the string one at a time

void uart_sendStr(const char *data){
	//TODO for reference see lcd_puts from lcd.c file
    while(*data != '\0')
    {
        if(*data)
        uart_sendChar(*data);
        data++;
    }
}*/
