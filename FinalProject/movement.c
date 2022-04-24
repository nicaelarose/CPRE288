/*
 * movement.c
 *
 *  Created on: Feb 11, 2021
 *      Author: cgpinta
 */
#include "open_interface.h"
#include "movement.h"
#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART)
#include "cyBot_FindObjects.h"
#include "project.h"
#include "servo.h"
#include "ping_template.h"

//used to correct the angle of the turns of the cyBot
float TURN_ANGLE_CORRECTION = 10;

double move_backward(oi_t *sensor_data, double distance_mm, int speed)
{
    // the following code could be put in function move_forward()
    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(speed * -1, speed * -1); //move forward at full speed
    while (sum > (distance_mm * -1))
    {
        oi_update(sensor_data);

        sum += sensor_data->distance; // use -> notation since pointer
    }
    //lcd_printf("%f", sensor_data->cliffFrontLeftSignal);
    oi_setWheels(0, 0); //stop
    return sum;
}

double move_forward(oi_t *sensor_data, double distance_mm, int speed)
{
    // the following code could be put in function move_forward()
    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(speed, speed); //move forward at full speed
    while (sum <= distance_mm)
    {
        oi_update(sensor_data);
        int cliffFL = sensor_data->cliffFrontLeftSignal;
        int cliffFR = sensor_data->cliffFrontRightSignal;
        int cliffL = sensor_data->cliffLeftSignal;
        int cliffR = sensor_data->cliffRightSignal;
        lcd_printf("%i %i", cliffFL, cliffFR);
        if (sensor_data->bumpLeft || cliffFL != 1000 || cliffL != 1000)
        {
            //lcd_puts("Left");
            turn_right(sensor_data, 90, speed);
            break;
        }
        else if (sensor_data->bumpRight || cliffFR != 1000 || cliffR != 1000)
        {
            //lcd_puts("Right");
            turn_left(sensor_data, 90, speed);
            break;
        }
        sum += sensor_data->distance; // use -> notation since pointer
    }
    oi_setWheels(0, 0); //stop
    return sum;
}

double passive_forward(oi_t *sensor_data, double distance_mm, int speed,
                       float distance[])
{
    int MAX_SCAN_DISTANCE = 150;
    // the following code could be put in function move_forward()
    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(speed, speed); //move forward at full speed
    int i = 45;
    int j = 0;
    while (sum <= distance_mm - 0)
    {
        if (i > 135)
        {
            i = 45;
            j = 0;
        }
        servo_move(i);
        oi_update(sensor_data);
        if (sensor_data->bumpLeft)
        {
            lcd_puts("Left");
            turn_right(sensor_data, 90, speed);
        }
        else if (sensor_data->bumpRight)
        {
            lcd_puts("Right");
            turn_left(sensor_data, 90, speed);
        }
        sum += sensor_data->distance; // use -> notation since pointer

        //SCANS
        float temp = ping_getDistance();
        if (temp < MAX_SCAN_DISTANCE)
        {
            distance[j] = temp;
            //lcd_printf("%i %f", j, distance[j]);
            j++;
        }
        i += 2;
    }
    oi_setWheels(0, 0); //stop
    return sum;
}

/*
 * This function is the main movement function we are using. The car will continuously scan while moving but stop
 * when it sees something
 */
double move_stopandscan(oi_t *sensor_data, double distance_mm, int speed,
                        float *distance, float *startangle, float *endangle,
                        int *i)
{
    int MAX_SCAN_DISTANCE = 80;
    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(speed, speed); //move forward at full speed
    while (sum <= distance_mm - 0)
    {
        lcd_printf("%f", sensor_data->cliffFrontLeft);
        //lcd_printf("4");
        //used as an "inside while loop". resets servo when it gets to a certain angle
        if (*i > 135)
        {
            *i = 45;
        }
        //increments servo by 2 each cycle of the while loop
        servo_move(*i);
        *i += 2;

        //movement code from movement lab
        oi_update(sensor_data);
        int cliffFL = sensor_data->cliffFrontLeftSignal;
        int cliffFR = sensor_data->cliffFrontRightSignal;
        int cliffL = sensor_data->cliffLeftSignal;
        int cliffR = sensor_data->cliffRightSignal;
        if (sensor_data->bumpLeft || cliffFL != 1000)
        {
            turn_right(sensor_data, 90, speed);
            break;
        }
        else if (sensor_data->bumpRight || cliffFR != 1000)
        {
            turn_left(sensor_data, 90, speed);
            break;
        }
        if (cliffL != 1000)
        {
            turn_right(sensor_data, 45, speed);
            break;
        }
        if (cliffR != 1000)
        {
            turn_left(sensor_data, 45, speed);
            break;
        }
        sum += sensor_data->distance; // use -> notation since pointer

        /*
         * the PING sensor takes in distances of objects if the distance is
         * less than MAX_SCAN_DISTANCE
         */

        float temp = ping_getDistance();
        if (temp < MAX_SCAN_DISTANCE)
        {
            oi_setWheels(0, 0);
            *distance = temp;
            //lcd_printf("%f", *distance);
            *startangle = *i;
            /*TODO: it scans but doesnt stop. Need to add function where, when it detects something,
             * the bot stops and allows the servo to scan until it does not detect anything anymore
             * as to get accurate width datta on the object
             */

            while (temp < *distance + 5 && temp > *distance - 5)
            {
                *endangle = *i;
                lcd_printf("%f", temp);
                temp = ping_getDistance();
                timer_waitMillis(600);
                lcd_printf("%f", temp);
                *i += 2;
                servo_move(*i);
            }

            float width = 2 * 3.14159 * (*distance)
                    * ((*endangle - *startangle) / 360);

            break;
        }
    }
    oi_setWheels(0, 0); //stop*/
    return 0;
}

double turn_right(oi_t *sensor_data, double degrees, int speed)
{
    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(speed, speed * -1); //move forward at full speed
    while (sum <= degrees - TURN_ANGLE_CORRECTION)
    {
        lcd_init();
        oi_update(sensor_data);
        sum += sensor_data->angle; // use -> notation since pointer
        //printf("%f degrees\n", sum);
    }
    oi_setWheels(0, 0); //stop
    return sum;
}
double turn_left(oi_t *sensor_data, double degrees, int speed)
{
    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(speed * -1, speed); //move forward at full speed
    while (sum >= -1 * degrees + TURN_ANGLE_CORRECTION)
    {
        lcd_init();
        oi_update(sensor_data);
        sum += sensor_data->angle; // use -> notation since pointer
        //double d =  oi_getDegrees(sensor_data);
        //printf("%f degrees\n", sum);

    }
    oi_setWheels(0, 0); //stop
    return sum;
}

