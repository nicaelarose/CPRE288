/**
 * lab5_template.c
 *
 * Template file for CprE 288 Lab 5
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 *
 * @author Phillip Jones, updated 6/4/2019
 * @author Diane Rover, updated 2/25/2021
 */

#include "button.h"
#include "timer.h"
#include "lcd.h"

#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART1)
                         // PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity, COM1

#include "cyBot_FindObjects.h"  // Scan the CyBot sensors to find objects



int main_old(void) {
	//button_init();
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	cyBot_uart_init_clean();
  // initialize the cyBot UART1 before trying to use it

  // (Uncomment ME for UART init part of lab)
	// cyBot_uart_init_clean();  // Clean UART initialization, before running your UART GPIO init code

	// Complete this code for configuring the GPIO PORTB part of UART1 initialization (your UART GPIO init code)
     SYSCTL_RCGCGPIO_R |= 0b00010;
	 while ((SYSCTL_PRGPIO_R & 0b00010) == 0) {};
		 GPIO_PORTB_DEN_R |= 0x0FF;
		 GPIO_PORTB_AFSEL_R |= 0x0FF;//p672
     GPIO_PORTB_PCTL_R &= 0x00000011;     // Force 0's in the desired locations p688
     GPIO_PORTB_PCTL_R |= 0x00000011;     // Force 1's in the desired locations
		 // Or see the notes for a coding alternative to assign a value to the PCTL field

    // (Uncomment ME for UART init part of lab)
	cyBot_uart_init_last_half();  // Complete the UART device configuration


	uart_sendStr("this is a sentence");

	while(true)
	{
	    if(uart_receive()=='\r'){
	        uart_sendChar('\n');
	    }
	    else{
	    uart_sendChar(uart_receive());
	    }
	}

}
