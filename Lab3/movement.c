/*
 * movement.c
 *
 *  Created on: Feb 11, 2021
 *      Author: Nicaela Bungubung and Grace Rasmussen
 */

#include "open_interface.h"
#include "movement.h"
#include "lcd.h"

double move_forward(oi_t*sensor_data, double distance_mm)
{
    double sum = 0;

    oi_setWheels(500,500);

    while (sum < distance_mm)
    {
        oi_update(sensor_data);

        if (sensor_data->bumpRight)
        {
            oi_setWheels(0,0);
            move_backward(sensor_data, 150);
            turn_left(sensor_data, 90);
            move_forward(sensor_data, 250); //moves laterally 25 cm
            turn_right(sensor_data, 90);
            oi_setWheels(500,500);
        }
        if (sensor_data->bumpLeft)
        {
            oi_setWheels(0,0);
            move_backward(sensor_data, 150);
            turn_right(sensor_data, 90);
            move_forward(sensor_data, 250); //moves laterally 25 cm
            turn_left(sensor_data, 90);
            oi_setWheels(500,500);
        }
        sum += sensor_data->distance;
    }
        oi_setWheels(0,0);
        return sum;
}

double move_backward(oi_t*sensor_data, double distance_mm)
{
    double sum = 0;
    oi_setWheels(-500,-500);
        while (sum > (distance_mm * -1))
        {
            oi_update(sensor_data);
            sum += sensor_data->distance;
        }
        oi_setWheels(0,0);
        return sum;
}

double turn_right(oi_t*sensor_data, double degrees)
{
    double sum = 0;
    oi_setWheels(100, -100);
        while (sum < (degrees))
        {
            oi_update(sensor_data);
            sum += sensor_data->angle;
        }
        oi_setWheels(0,0);
        return sum;
}


double turn_left(oi_t*sensor_data, double degrees)
{
    double sum = 0;
    oi_setWheels(-100, 100);
        while (sum > (degrees * -1))
        {
            oi_update(sensor_data);
            sum += sensor_data->angle;
        }
        oi_setWheels(0,0);
        return sum;
}

void collision(oi_t* sensor_data, double turn)
{
    move_backward(sensor_data, 150);
    if (turn > 0)
    {
        turn_right(sensor_data, 90);
        move_forward(sensor_data,250);
        turn_left(sensor_data, 90);
    }
    else
    {
        turn_left(sensor_data, 90);
        move_forward(sensor_data,250);
        turn_right(sensor_data, 90);
    }
}





