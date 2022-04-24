/*
 * movement.h
 *
 *  Created on: Feb 11, 2021
 *      Author: nicaelab
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_
#include "open_interface.h"


//double move_forward(oi_t*sensor_data, double distance_mm);
//
//double move_backward(oi_t*sensor_data, double distance_mm);
//
//double turn_right(oi_t*sensor_data, double degrees);
//
//double turn_left(oi_t*sensor_data, double degrees);
//
//void collision(oi_t*sensor_data, double turn);

/**
 * Function to move forward a number of mm and if the bump
 * sensors are triggered it will back up and turn to avaoid the object
 */
double move_forward(oi_t *sensor_data, double distance_mm);



/**
 * Function to move forward an amount of mm
 */
double turn_right(oi_t *sensor_data, double degrees);



/**
 * Function to turn right some amount of degrees
 */
double turn_left(oi_t *sensor_data, double degrees);


/**
 * Function to turn left some amount of degrees
 */
double move_forward_with_bump(oi_t *sensor_data, double distance_mm);

/**
 * Function to move backwards a certain number of mm
 */
double move_backwards(oi_t *sensor_data, double distance_mm);

/**
 * Function to move in a square turning right at the corners
 */
int right_square(oi_t *sensor_data, double size);

/**
 * Function to move in a square turning left at the corners
 */
int left_square(oi_t *sensor_data, double size);

#endif /* MOVEMENT_H_ */
