/*
 * main.c
 *
 *  Created on: Feb 11, 2021
 *      Author: Nicaela Bungubung and Grace Rasmussen
 */

#include "lcd.h"
#include "button.h"
#include "uart.h"
#include "open_interface.h"
#include "movement.h"
#include "lab5_scan_data.h"
volatile int uart_event = 0;
volatile char uart_char = "";

void main(void)
{
    uart_init();

    //Struct that will hold our readings
    struct reading readings[181];
    //String that we use to print to putty
    char sendstr[181]="";
    //Calling get reading and storing the values in our struct
    get_reading("dataset1.csv", readings);

    //Print the header
    sprintf(sendstr, "%-20s%-20s%-20s\r\n", "Degrees", "IR Distance (cm)", "Sonar Distance(cm)");
    //Send it to UART and PUTTY
    uart_sendStr(sendstr);

    int i = 0;
    for(i=0; i<181; i++){
        //Add all the data
        sprintf(sendstr, "%-20d%-20f%-20f\r\n",i,readings[i].ir_distance,readings[i].sonar_distance);
        //Send the string over UART and PUTTY
        uart_sendStr(sendstr);
    }
}
