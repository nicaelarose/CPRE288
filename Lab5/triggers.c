#include "triggers.h"
/*
 * This function will return 1 if the left bump switch has been hit
 * @author Nick Battani, Swechha Ghimire
 *
 * @param oi_t *sensor_data
 *
 * @data 02/11/2019
 */
int bump_left(oi_t *sensor_data){
    if(sensor_data->bumpLeft == 1){
        return 1;
    } else {
        return 0;
    }
}
/*
 * This function will return 1 if the right bump switch has been hit
 * @author Nick Battani, Swechha Ghimire
 *
 * @param oi_t *sensor_data
 *
 * @data 02/11/2019
 */
int bump_right(oi_t *sensor_data){
    if(sensor_data->bumpRight == 1){
        return 1;
    } else {
        return 0;
    }
}
