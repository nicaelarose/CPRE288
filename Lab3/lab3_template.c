/**
 * lab3_template.c
 * 
 * Template file for CprE 288 lab 3
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 */

#include "button.h"
#include "Timer.h"
#include "lcd.h"
#include "cyBot_uart.h" // Functions for communicating between CyBot and Putty (via UART)
                         // PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity,  COM1
#include "open_interface.h"

//#warning "Possible unimplemented functions"
#define REPLACEME 0



int main(void) {
	button_init();
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	            // Don't forget to initialize the cyBot UART before trying to use it
	oi_t *sensor_data = oi_alloc(); //do this only once at the start of main()
	oi_init(sensor_data); //do this only once at the start of main()

	cyBot_uart_init();
	
	int button;
	int putty;
	bool flag = 1;

	while (true)
	{
	    button = button_getButton();
	    //putty = (char)cyBot_getByte();

	    if (button == 1 && flag)
	    {
	        cyBot_sendByte('1');
	        flag = 0;
	    }
	    else if (button == 2 && flag)
	    {
	        cyBot_sendByte('2');
	        flag = 0;
	    }
        else if (button == 3 && flag)
        {
            cyBot_sendByte('3');
            flag = 0;
        }
        else if (button == 4 && flag)
        {
            cyBot_sendByte('4');
            flag = 0;
        }
	    if (button == 0)
	    {
	        flag = 1;
	    }
	    lcd_printf("%d", button);
	}
	return 0;

	// YOUR CODE HERE
	
	//Part 1
//	while(1)
//	{
//	    uint8_t button = button_getButton();
//	    lcd_printf("Button %d was pressed", button);
//	}
	
}
