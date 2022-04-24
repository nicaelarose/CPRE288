#include "open_interface.h"

#ifndef TRIGGERS_H_
#define TRIGGERS_H_
/*
 * This function will return 1 if the left bump switch has been hit
 * @author Nick Battani, Swechha Ghimire
 *
 * @param oi_t *sensor_data
 *
 * @data 02/11/2019
 */
int bump_left(oi_t *sensor_data);
/*
 * This function will return 1 if the right bump switch has been hit
 * @author Nick Battani, Swechha Ghimire
 *
 * @param oi_t *sensor_data
 *
 * @data 02/11/2019
 */
int bump_right(oi_t *sensor_data);



#endif /* TRIGGERS_H_ */
