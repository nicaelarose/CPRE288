/**
 * lab6_template.c
 *
 * Template file for CprE 288 Lab 6
 *
 * @author Diane Rover, 2/15/2020
 *
 */

#include "Timer.h"
#include "lcd.h"
#include "cyBot_Scan.h"  // For scan sensors
#include "uart.h"
#include "cyBot_uart.h""
// Uncomment or add any include directives that are needed
#include "open_interface.h"
//#include "movement.h"
// #include "button.h"
#include "resetSimulation.h"


//#warning "Possible unimplemented functions"
#define REPLACEME 0

int main(void) {

    timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	//cyBot_uart_init();
	uart_init();
    cyBOT_init_Scan();
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
    cyBOT_Scan_t scanData;

    //Help from TA
//    int degrees;
//       int i;
//       //char tempAngle[10];
//       //char tempDist[10];
//       //char IR[10];
//       //int i = 0;
//       //cyBOT_Scan(-45, &scanData);
//       while(1)
//       {
//           char title[] = "Angle PING Distance IR raw value\n";
//           char data;
//           char dist[] = "";
//           data = cyBot_getByte_blocking();
//           cyBot_sendByte(data);
//           //temp = uart_receive(); //receives char from PuTTY
//           if (data == 'g')
//           {
//           for (i=0; i<strlen(title); i++)
//                 cyBot_sendByte(title[i]);
//
//                 cyBot_sendByte('\n\r'); // start a new line
//
//                 for(degrees = 0; degrees <= 180; degrees +=5)
//                 {
//                    cyBOT_Scan(degrees, &scanData); //scan every 5 degrees
//                    sprintf(dist, "%d \t %f \t %i \n\r", degrees, scanData.sound_dist, scanData.IR_raw_val); //take scan and make char array
//
//                    for (i=0; i<strlen(dist); i++){
//                        cyBot_sendByte(dist[i]); // print char array to putty
//                    }
//                 }
//           }
//       }
//   }


    char string[] = "Angle PING Distance IR raw value\n";
    char temp;
    char tempAngle[10];
    char tempDist[10];
    char IR[10];
    int i = 0;
    //cyBOT_Scan(-45, &scanData);

	while(1)
	{
	    temp = uart_receive(); //receives char from PuTTY
	    if (temp == 'g')
	    {
	        uart_sendStr(string); //header
	        for (i = 0; i < 181; i += 5) //increments of 5
	        {
	            cyBOT_Scan(i, &scanData);
	            sprintf(tempAngle,"%d", i); //current angle
	            uart_sendStr(tempAngle);
	            uart_sendChar('\t');
	            sprintf(tempDist, "%.2lf", scanData.sound_dist);
	            uart_sendStr(tempDist);
	            uart_sendChar('\t');
	            uart_sendChar('\t');
	            sprintf(IR, "%d", scanData.IR_raw_val);
	            uart_sendStr(IR);
	            uart_sendChar('\n');
	        }

	    }

	}
	//oi_free(sensor_data);
}
