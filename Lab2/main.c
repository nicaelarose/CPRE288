/*
 * main.c
 *
 *  Created on: Feb 11, 2021
 *      Author: Nicaela Bungubung and Grace Rasmussen
 */

#include "open_interface.h"
#include "movement.h"
#include "lcd.h"
//#include "resetSimulation.h"
int main(void)
{
   // resetSimulationBoard();
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    //Part 1
    //move_forward(sensor_data, 1000);

    //Part 2
//    move_forward(sensor_data, 500);
//    turn_right(sensor_data, 90);
//    move_forward(sensor_data, 500);
//    turn_right(sensor_data, 90);
//    move_forward(sensor_data, 500);
//    turn_right(sensor_data, 90);
//    move_forward(sensor_data, 500);

    //Part 3
      move_forward(sensor_data, 2000);
      oi_free(sensor_data);
      return 0;

}


