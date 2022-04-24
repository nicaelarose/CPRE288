/*
 * main.c
 *
 *  Created on: Feb 11, 2021
 *      Author: Nicaela Bungubung and Grace Rasmussen
 */

#include "open_interface.h"
#include "lcd.h"
#include "button.h"
#include "cyBot_uart.h"
#include "movement.h"
#include "cyBot_FindObjects.h"

int main(void)
{
    cyBot_uart_init();

    cyBot_Object_t objects[4];
    int k;
    for(k = 0; k < (sizeof(objects) / sizeof(cyBot_Object_t)); k++){
        cyBot_Object_t clear;
        clear.angle = 0;
        clear.distance = 0;
        clear.width = 0;
        objects[k] = clear;
    }
    cyBot_FindObjects(objects, 4);

    char* initial = "Object#\tAngle\tDistance\tWidth\n";
    int j;
    for(j = 0; j < strlen(initial); j++){
        cyBot_sendByte(initial[j]);
    }

    int i;
    for(i = 0; i < (sizeof(objects) / sizeof(cyBot_Object_t)); i++){
        if(objects[i].distance == 0){
            continue;
        }
        char data[50];

        sprintf(data, "%d\t\t%d\t%f\t%f\n", i, objects[i].angle, objects[i].distance, objects[i].width);
        for(j = 0; j < strlen(data); j++){
            cyBot_sendByte(data[j]);
        }//move_forward(sensor_data, (double) objects[j].distance * 10);
    }
    int min = objects[0].width;
    int smallIdx = 0;
    for(i = 0; i < (sizeof(objects) / sizeof(cyBot_Object_t)); i++){
        if(objects[i].distance == 0){
            continue;
        }
        min = min - objects[i].width < 0 ? min : objects[i].width;
        smallIdx = min - objects[i].width < 0 ? smallIdx : i;
    }
    for(i = 0; i < (sizeof(objects) / sizeof(cyBot_Object_t)); i++)
    {
        if (objects[i].width < min)
        {
            min = objects[i].width;
            smallIdx = i;
        }
    }
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
    if(objects[smallIdx].angle < 90){
        turn_left(sensor_data, 90 - objects[smallIdx].angle);
    }
    else{
        turn_right(sensor_data, objects[smallIdx].angle - 90);
    }
    move_forward(sensor_data, (double) objects[j].distance * 10);
    oi_free(sensor_data);
    return 0;

}


