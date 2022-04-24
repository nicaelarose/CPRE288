/*
 * @file movement.h
 * @brief This file contains all of the functions needed for the iRobot to move
 *
 * @author Nick Battani, Swechha Ghimire
 *
 * @date 02/07/2019
 */
#include "open_interface.h"
#include "triggers.h"

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

/*
 * This function will move the robot forward a given amount of millimeters
 * @author Nick Battani, Swechha Ghimire
 *
 * @param oi_t *sensor_data
 * @param int millimeters
 * @param triggers
 *
 * @data 02/07/2019
 */
void move_forward(oi_t *sensor_data, int millimeters, int left_wheel, int right_wheel, int triggers);
/*
 * This function will move the robot backwards a given amount of millimeters
 * @author Nick Battani, Swechha Ghimire
 *
 * @param oi_t *sensor_data
 * @param int millimeters
 * @param int triggers
 *
 * @data 02/11/2019
 */
void move_backwards(oi_t *sensor_data, int millimeters, int left_wheel, int right_wheel, int triggers);
/*
 * This function will turn the robot clockwise for a given amount of degrees
 * @author Nick Battani, Swechha Ghimire
 *
 * @param oi_t *sensor_data
 * @param int degrees
 *
 * @data 02/07/2019
 */

void move_turn_clockwise(oi_t *sensor_data, int degrees);
/*
 * This function will turn the robot counter-clockwise for a given amount of degrees
 * @author Nick Battani, Swechha Ghimire
 *
 * @param oi_t *sensor_data
 * @param int degrees
 *
 * @data 02/07/2019
 */
void move_turn_counter_clockwise(oi_t *sensor_data, int degrees);
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
void left_bump_avoidance(oi_t *sensor_data, int left_wheel, int right_wheel, int sum);
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
void right_bump_avoidance(oi_t *sensor_data, int left_wheel, int right_wheel, int sum);

#endif /* MOVEMENT_H_ */
