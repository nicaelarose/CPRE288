/*
 * movement.h
 *
 *  Created on: Feb 11, 2021
 *      Author: nicaelab
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_
#include "open_interface.h"


double move_forward(oi_t*sensor_data, double distance_mm);

double move_backward(oi_t*sensor_data, double distance_mm);

double turn_right(oi_t*sensor_data, double degrees);

double turn_left(oi_t*sensor_data, double degrees);

void collision(oi_t*sensor_data, double turn);

#endif /* MOVEMENT_H_ */
