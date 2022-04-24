/*
* servo.c for lab 09
*/

#include "servo.h"


void servo_init(void) {

    SYSCTL_RCGCTIMER_R |= 0x02; //Enables timer 1 on bit 1
    SYSCTL_RCGCGPIO_R |= 0x02; //Enables Port B by setting bit 1
    while ((SYSCTL_PRTIMER_R & 0x02) == 0) {}; //Busy-wait for Timer1 enable on bit 1
    while ((SYSCTL_PRGPIO_R & 0x02) == 0) {}; //Busy-wait for PortB enable on bit 1

    GPIO_PORTB_DEN_R |= 0x20; //Enables PB5
    //GPIO_PORTB_DIR_R &= 0xF7; //Sets PB3 as input by clearing bit 3
    GPIO_PORTB_AFSEL_R |= 0x20; //Enables alternate function for PB5

    GPIO_PORTB_PCTL_R |= 0x00700000; //Sets PB5 alternate function to Timer1B
    GPIO_PORTB_PCTL_R &= ~0x00800000;

    TIMER1_CTL_R &= ~0x0100; //disables Timer1B
    //TIMER1_CTL_R |= 0x0100; //set bit 14 for PWM inverted output?
    TIMER1_CFG_R = 0x4; //sets Timer1 to 16 bit
    TIMER1_TBMR_R = 0xA; //sets periodic PWM mode
    TIMER1_CTL_R &= ~0x4000;
    TIMER1_TBILR_R = 0x4E200 & 0xFFFF; //sets value to 320,000
    TIMER1_TBPR_R = 0x4E200 >> 16; //sets prescaler
    TIMER1_TBMATCHR_R = 0x4BED8 & 0xFFFF;
    TIMER1_TBPMR_R = 0x4BED8 >> 16;
    // Configure and enable the timer
    TIMER1_CTL_R |= 0x0100; //enables Timer1B
    //servo_move(0.0);
}

int servo_move(float degrees) {
    //float ms = (degrees / 180) + 1;
    //float s = ms / 1000;
    int match = 320000 - 9000 - ((22000 * degrees)/180);
    TIMER1_TBMATCHR_R = match & 0xFFFF;
    TIMER1_TBPMR_R = match >> 16;
    return 1;
}
