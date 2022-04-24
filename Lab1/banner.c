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
//#include "resetSimulation.h"

int main (void) {

   // resetSimulationBoard();

    timer_init(); // Initialize Timer, needed before any LCD screen functions can be called
                  // and enables time functions (e.g. timer_waitMillis)

    lcd_init();   // Initialize the LCD screen.  This also clears the screen.

    lcd_rotatingBanner("Microcontrollers are lots of fun!");

    // Print "Hello, world" on the LCD
    //lcd_printf("Hello, world");

    // lcd_puts("Hello, world"); // Replace lcd_printf with lcd_puts
        // step through in debug mode and explain to TA how it works

    // NOTE: It is recommended that you use only lcd_init(), lcd_printf(), lcd_putc, and lcd_puts from lcd.h.
       // NOTE: For time functions, see Timer.h

    return 0;
}

void lcd_rotatingBanner(char banner[])
{
    lcd_init(); //Initializes the LCD

    int lcd_string = strlen(banner) + 21; //Size of the string displayed including the 21 spaces

    char display[100] = "                    "; //Char array to hold the banner plus the spaces

    int i, j = 0; //Incrementing variables

    char print[100] = ""; //Holds the string that needs to be printed at the moment

    strcat(display, banner); //Copies the banner char array into the display char array

    //Rotates through the size of the text char array including the spaces
    for(i = 0; i < lcd_string; i++)
    {
        for (j = 0; j < 20; j++)  //Sets the print array to 20 characters at once
        {
            print[j] = display[i + j];
        }
        //Prints the array 20 characters at a time
        lcd_printf(print);
        timer_waitMillis(300); //Wait .3 seconds

        //After displayed, restart the for loop
        if (i == lcd_string - 1)
        {
            i = 0;
        }
    }
}





