/*
 * @file movement.c
 * @brief This file contains all of the functions needed for the iRobot to move
 *
 * @author Nick Battani, Swechha Ghimire
 *
 * @date 02/07/2019
 */
#include "movement.h"

/*
 * This function will move the robot forward a given amount of millimeters
 * @author Nick Battani, Swechha Ghimire
 *
 * @param oi_t *sensor_data
 * @param int millimeters
 * @param int left_wheel
 * @param int right_wheel
 * @param int triggers
 *
 * @data 02/11/2019
 */
void move_forward(oi_t *sensor_data, int millimeters, int left_wheel, int right_wheel, int triggers)
{

    // initialize sum to 0
    int sum = 0;

    if (triggers == 1)
    {
        // set the wheel speed, probably needs adjustment depending on robot due to drifting with the roomba's encoders
        oi_setWheels(right_wheel, left_wheel);

        // while the integer value sum is less than degrees
        while (sum < millimeters)
        {

            // update the iRobot sensor data
            oi_update(sensor_data);

            if(bump_left(sensor_data)){
                left_bump_avoidance(sensor_data, left_wheel, right_wheel, millimeters - sum);
            } else if (bump_right(sensor_data)){
                right_bump_avoidance(sensor_data, left_wheel, right_wheel, millimeters - sum);
            }else{

            // update the integer value sum with the iRobot sensor value for distance traveled
            sum += sensor_data->distance;
            }
        }

    }
    else
    {
        // set the wheel speed, probably needs adjustment depending on robot due to drifting with the roomba's encoders
        oi_setWheels(right_wheel, left_wheel);

        // while the integer value sum is less than degrees
        while (sum < millimeters)
        {

            // update the iRobot sensor data
            oi_update(sensor_data);

            // update the integer value sum with the iRobot sensor value for distance traveled
            sum += sensor_data->distance;
        }
    }
    // stop the wheels
    oi_setWheels(0, 0);

}
/*
 * This function will move the robot backwards a given amount of millimeters
 * @author Nick Battani, Swechha Ghimire
 *
 * @param oi_t *sensor_data
 * @param int millimeters
 * @param left_wheel
 * @param right_wheel
 * @param int triggers
 *
 * @data 02/11/2019
 */
void move_backwards(oi_t *sensor_data, int millimeters, int left_wheel, int right_wheel, int triggers)
{

    // initialize sum to 0
    int sum = 0;

    // set the wheel speed(negative so it goes backwards), probably needs adjustment depending on robot due to drifting with the roomba's encoders
    oi_setWheels(-right_wheel, -left_wheel);

    // while the integer value sum is less than degrees
    while (sum < millimeters)
    {

        // update the iRobot sensor data
        oi_update(sensor_data);

        // update the integer value sum with the iRobot sensor value for distance traveled
        sum -= sensor_data->distance;
    }
    // stop the wheels
    oi_setWheels(0, 0);

}
/*
 * This function will turn the robot clockwise for a given amount of degrees
 * @author Nick Battani, Swechha Ghimire
 *
 * @param oi_t *sensor_data
 * @param int degrees
 *
 * @data 02/07/2019
 */
void move_turn_clockwise(oi_t *sensor_data, int degrees)
{
    // initialize sum to 0
    int sum = 0;

    // set the wheel speed to oppose each-other
    oi_setWheels(-250, 250);

    // while the integer value sum is less than degrees
    while (sum < degrees)
    {

        // update the iRobot sensor data
        oi_update(sensor_data);

        // update the integer value sum with the iRobot sensor value for angle
        // multiple by 1.08 to correct the data for angle given by the iRobot
        sum -= (int) sensor_data->angle * 1.08;

    }

    // stop the wheels
    oi_setWheels(0, 0);
}

/*
 * This function will turn the robot counter-clockwise for a given amount of degrees
 * @author Nick Battani, Swechha Ghimire
 *
 * @param oi_t *sensor_data
 * @param int degrees
 *
 * @data 02/07/2019
 */
void move_turn_counter_clockwise(oi_t *sensor_data, int degrees)
{
    // initialize sum to 0
    int sum = 0;

    // set the wheel speed to oppose each-other
    oi_setWheels(250, -250);

    // while the integer value sum is less than degrees
    while (sum < degrees)
    {
        // update the iRobot sensor data
        oi_update(sensor_data);

        // update the integer value sum with the iRobot sensor value for angle
        // multiple by 1.08 to correct the data for angle given by the iRobot
        sum += (int) sensor_data->angle * 1.08;

    }

    // stop the wheels
    oi_setWheels(0, 0);
}
/*
 * This function will perform a left-bump switch triggered avoidance
 * @author Nick Battani, Swechha Ghimire
 *
 * @param oi_t *sensor_data
 * @param int left_wheel
 * @param int right_wheel
 * @param int remaining_distance
 *
 * @data 02/11/2019
 */
void left_bump_avoidance(oi_t *sensor_data, int left_wheel, int right_wheel, int remaining_distance){
    // go back 15 cm
    move_backwards(sensor_data, 150, left_wheel, right_wheel, 0);
    // turn away from object
    move_turn_clockwise(sensor_data, 90);
    // go forward 25 cm
    move_forward(sensor_data, 250, left_wheel, right_wheel, 1);
    // turn back towards end destination
    move_turn_counter_clockwise(sensor_data, 91);
    // go forward the remaining distance + the 15cm you went backwards
    move_forward(sensor_data, remaining_distance + 150, left_wheel, right_wheel, 1);
}
/*
 * This function will perform a right-bump switch triggered avoidance
 * @author Nick Battani, Swechha Ghimire
 *
 * @param oi_t *sensor_data
 * @param int left_wheel
 * @param int right_wheel
 * @param int remaining_distance
 *
 * @data 02/11/2019
 */
void right_bump_avoidance(oi_t *sensor_data, int left_wheel, int right_wheel, int remaining_distance){
    // go back 15 cm
    move_backwards(sensor_data,150, left_wheel, right_wheel, 0);
    // turn away from object
    move_turn_counter_clockwise(sensor_data, 91);
    // go forward 25 cm
    move_forward(sensor_data, 250, left_wheel, right_wheel, 1);
    // turn back towards end destination
    move_turn_clockwise(sensor_data, 90);
    // go forward the remaining distance + the 15cm you went backwards
    move_forward(sensor_data, remaining_distance + 150, left_wheel, right_wheel, 1);
}



