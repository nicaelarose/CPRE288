/*
*
*   uart.c
*
*
*
*   @author
*   @date
*/

#include <inc/tm4c123gh6pm.h>
#include <stdint.h>
#include "uart.h"
#include <stdbool.h>
#include "cyBot_uart.h"
#include <inc/tm4c123gh6pm.h>
#include "lcd.h"

void uart_init(void){
	//TODO
  //enable clock to GPIO port B
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1; //0x02

  //enable clock to UART1
  SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R1; //0x02

  //wait for GPIOB and UART1 peripherals to be ready
  while ((SYSCTL_PRGPIO_R & 0b0000010) == 0) {};
  while ((SYSCTL_PRUART_R & 0b0000010) == 0) {};

  //enable alternate functions on port B pins
  GPIO_PORTB_AFSEL_R |= 0x03;

  //enable digital functionality on port B pins
  GPIO_PORTB_DEN_R |= 0x03;
  GPIO_PORTB_PCTL_R &= ~0x00000011;
  //enable UART1 Rx and Tx on port B pins
  GPIO_PORTB_PCTL_R |= 0x00000011;

  //calculate baud rate
  uint16_t iBRD = 0x8; //use equations
  uint16_t fBRD = 0x2C; //use equations

  //turn off UART1 while setting it up
  UART1_CTL_R &= ~0x301; //0x01

  //set baud rate
  //note: to take effect, there must be a write to LCRH after these assignments
  UART1_IBRD_R = iBRD;
  UART1_FBRD_R = fBRD;

  //set frame, 8 data bits, 1 stop bit, no parity, no FIFO
  //note: this write to LCRH must be after the BRD assignments
  UART1_LCRH_R = 0x60;

  //use system clock as source
  //note from the datasheet UARTCCC register description:
  //field is 0 (system clock) by default on reset
  //Good to be explicit in your code
  UART1_CC_R = 0x0;

  //re-enable UART1 and also enable RX, TX (three bits)
  //note from the datasheet UARTCTL register description:
  //RX and TX are enabled by default on reset
  //Good to be explicit in your code
  //Be careful to not clear RX and TX enable bits
  //(either preserve if already set or set them)
  UART1_CTL_R |= 0x301; //0x0

}

void uart_sendChar(char data){
    //cyBot_senByte(data);
	while ((UART1_FR_R & 0X20) != 0) {};
	UART1_DR_R = data;
}

char uart_receive(void){
	//TODO
    uint32_t ret;
    char rdata;

    while((UART1_FR_R & 0X10) != 0) {};
    ret = UART1_DR_R;
    rdata = (char)(ret & 0xFF);

    return rdata;
}

void uart_sendStr(const char *data){
	//TODO for reference see lcd_puts from lcd.c file
    int i;
    lcd_clear();
    for (i = 0; i < strlen(data); i++)
    {
        lcd_putc(data[i]);
        uart_sendChar(data[i]);
    }
}
