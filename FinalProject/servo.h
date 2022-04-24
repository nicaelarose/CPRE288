/**
 * Driver for ping sensor
 * @file ping.c
 * @author
 */
#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>
#include <stdbool.h>
#include <inc/tm4c123gh6pm.h>

void servo_init(void);

int servo_move (float degrees);

#endif
