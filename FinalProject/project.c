#include "Timer.h"
#include "lcd.h"
#include "open_interface.h"
#include "servo.h"
#include "ping_template.h"
#include "resetSimulation.h"
#include "movement.h"

//the angle that the servo starts at when scanning
int SCAN_START_ANGLE = 45;
//the angle that the servo ends at when scanning
int SCAN_END_ANGLE = 135;
//ignores scan values greater than this value (in cm)
int MAX_SCAN_DISTANCE = 80;

int PING_SENSOR_DELAY = 1;

int CAR_SPEED = 200;

int CAR_VELOCITY = 20;

int SPEEDLIMIT = 200;

/*
 * scans from SCAN_START_ANGLE to SCAN_END_ANGLE and gathers
 * distance and angle values for each item
 *
 * TODO add width calculation
 */

void scanObjects(float distance[], float angle[])
{
    int j = 0;
    int i = SCAN_START_ANGLE;
    while (i < SCAN_END_ANGLE)
    {
        servo_move(i);
        timer_waitMillis(PING_SENSOR_DELAY);
        float temp = ping_getDistance();
        if (temp < MAX_SCAN_DISTANCE)
        {
            distance[j] = temp;
            lcd_printf("%i %f", j, distance[j]);
            j++;
        }
        i += 2;

    }
    i = 0;

    //return float[][] test;
}

int main(void)
{
    //--initializations--//

    resetSimulationBoard();
    timer_init(); // Must be called before lcd_init(), which uses timer functions
    lcd_init();
    servo_init();
    ping_init();
    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
    oi_init(sensor_data);

    //oi_free(sensor_data);

    //--local variables--//
    bool destination = false;
    float distance;
    float startAngle;
    float endAngle;

    int i = 0;
    int j = 0;

    oi_setWheels(0, 0);

    while (1)
    {
        /*
         if (CAR_SPEED < SPEEDLIMIT)
         {
         CAR_SPEED += CAR_VELOCITY;
         }
         else
         {
         CAR_SPEED = SPEEDLIMIT;
         }
         lcd_printf("i: %i \nj: %j",i,j);
         */
         move_stopandscan(sensor_data, 200, CAR_SPEED, &startAngle, &endAngle, &distance, &i);

    }

    oi_free(sensor_data); //necessary
}

