/// Simple 'Hello, world' program
/**
 * This program prints "Hello, world" to the LCD screen
 * @author Chad Nelson
 * @date 06/26/2012
 *
 * updated: phjones 9/3/2019
 * Description: Added timer_init call, and including Timer.h
 */

#include "Timer.h"
#include "lcd.h"


int lcd_rotatingBanner (void) {

	timer_init(); // Initialize Timer, needed before any LCD screen functions can be called 
	              // and enables time functions (e.g. timer_waitMillis)

	lcd_init();   // Initialize the LCD screen.  This also clears the screen. 

	char str[] = "Microcontrollers are lots of fun!";

	while(true){
	    int i = 0;
	    while(i<=20){
	        char temp[20]="";
	        int j=0;
	        while(j<20-i){
	            strncat(temp," ",1);
	            j++;
	        }
	        strncat(temp, str, i);
	        i++;
	        lcd_puts(temp);
	        timer_waitMillis(300);
	        lcd_init();
	    }
	    i=1;
	    while(i<strlen(str)){
	        char temp[20];
	        int j=0;
	        while(j<strlen(temp)&&j<20){
	            temp[j]=str[j+i];
	            j++;
	        }

	        i++;
	        lcd_puts(temp);
	        timer_waitMillis(300);
	        lcd_init();
	    }
	    /*while(i<20){

	        i++;
	    }

	    timer_waitMillis(300);*/
	}
	// Print "Hello, world" on the LCD
	//lcd_puts("Hello, world");

	// lcd_puts("Hello, world"); // Replace lcd_printf with lcd_puts
        // step through in debug mode and explain to TA how it works
    
	// NOTE: It is recommended that you use only lcd_init(), lcd_printf(), lcd_putc, and lcd_puts from lcd.h.
       // NOTE: For time functions, see Timer.h

	return 0;
}
