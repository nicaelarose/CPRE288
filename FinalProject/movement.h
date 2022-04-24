/*
 * movement.h
 *
 *  Created on: Feb 11, 2021
 *      Author: cgpinta
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_
#include "open_interface.h"
double move_forward(oi_t *sensor_data, double distance_mm, int speed);
double turn_right(oi_t *sensor,double degrees, int speed);
double turn_left(oi_t *sensor,double degrees, int speed);
double move_backward(oi_t *sensor_data, double distance_mm, int speed);
double passive_forward(oi_t *sensor_data, double distance_mm, int speed, float distance[]);
double move_stopandscan(oi_t *sensor_data, double distance_mm, int speed, float *distance, float *startangle, float *endangle, int *i);


#endif /* MOVEMENT_H_ */
