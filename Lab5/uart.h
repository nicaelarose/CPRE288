#ifndef UART_H_
#define UART_H_


#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "lcd.h"
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"

/*
 * This function will initiate the appropriate UART1 GPIO pins and registers
 * @author Nick Battani, Swechha Ghimire
 *
 * @data 02/26/2019
 */
void uart_init(void);
/*
 * This function will send a character over UART1
 * @author Nick Battani, Swechha Ghimire
 *
 * @param char data
 *
 * @data 02/26/2019
 */
void uart_sendChar(float data);
/*
 * This function will receive a character over UART1
 * @author Nick Battani, Swechha Ghimire
 *
 * @param char data
 *
 * @data 02/26/2019
 */
char uart_receive(void);
/*
 * This function is the UART1 Handler if the UART1 interrupt is triggered
 * @author Nick Battani, Swechha Ghimire
 *
 * @data 02/26/2019
 */
void UART1_Handler(void);
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
void uart_interrupts_init(int *uart_event_addr, char *uart_char_addr);

/*
 * This function will send a string over UART1
 * @author Nick Battani, Swechha Ghimire
 *
 * @param char data[]
 *
 * @data 02/26/2019
 */
void uart_sendStr(const char *data);

#endif /* UART_H_ */
