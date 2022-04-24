/**
 * @file lab8_template.c
 * @author
 * Template file for CprE 288 Lab 8
 */

#include "Timer.h"
#include "lcd.h"
#include "ping_template.h"
#include "resetSimulation.h"

// Uncomment or add any include directives that are needed

//#warning "Possible unimplemented functions"
#define REPLACEME 0

void interruptHandler(void);

int main(void) {

    resetSimulationBoard();
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	ping_init();
	float r = 0;

	// YOUR CODE HERE

	while(1)
	{
	    //ping_trigger();
	    r = ping_getDistance();
	    lcd_printf("%lf", r);

      // YOUR CODE HERE


	}

}
