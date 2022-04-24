/**
 * Driver for ping sensor
 * @file ping.c
 * @author Nicaela Bungubung and Grace Rasmussen
 */

#include "ping_template.h"
#include "Timer.h"
#include "driverlib/interrupt.h"

volatile unsigned long START_TIME = 0;
volatile unsigned long END_TIME = 0;
volatile enum{LOW, HIGH, DONE} STATE = LOW; // State of ping echo pulse

uint8_t overflow = 0;

////Global variables to store values from the IBR_R register
//extern volatile long rising;
//extern volatile long falling;



/**
 * Initializes the timer
 */
void ping_init (void){

  // YOUR CODE HERE

    //initialize clocks for GPIO and GPTM
    //enable clock to PGIO Port B
    SYSCTL_RCGCGPIO_R |= 0X2; //0b00000010
    //enable clock to Timer 3
    SYSCTL_RCGCTIMER_R |= 0X8; //0b00001000
    //wait for GPIOB and TIMER3 peripherals to be ready
    while ((SYSCTL_PRGPIO_R & 0x2) == 0) {};
    while ((SYSCTL_PRTIMER_R & 0x8) == 0) {};
    //initialize GPIO port pin for Timer3B
    //enable digital functionality on Port B pin 3, PB3
    GPIO_PORTB_DEN_R |= 0X8; //0b00001000
    //enable alternate function on PB3
    GPIO_PORTB_AFSEL_R |= 0x8; //0b00001000
    //select Timer3B input for PB3, PMC# code is 0x7 for T3CCP1
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xFFFF0FFF) | 0x00007000;
    //initialize Tmer3B in input edge time mode, follow steps in Tiva datasheet (11.4.4)
    //step 1, ensure timer is disabled, clear TBEN bit (bit 8)
    TIMER3_CTL_R &= ~0x100; //0b1 0000 0000
    //step 2, write GPTMCFG with value of 0x4 (16-bit timer configuration)
    TIMER3_CFG_R = 0x4;
    //step 3, write GPTMTBMR bits, TBCMR=0x1, TBMR=0x3, TBCDIR = down
    //(edge-time mode, capture mode, count down)
    //CMR, bit 2 = 1; MR bits 1:0 = 0x3 = 0b11; CDIR, bit 4 = 0
    TIMER3_TBMR_R |= 0x7; //0b00000111, set bits 0-2
    TIMER3_TBMR_R &= ~0x10; //0b00010000, clear bit 4 (also 0 on reset)
    //step 4, write GPTMCTL TBEVENT field to configure both edges (bits 11:10 = 0x3)
    TIMER3_CTL_R |= 0xC00; //0b1100 0000 0000
    //step 5, write prescale value to GPTMTBPR (24-bit timer extension)
    TIMER3_TBPR_R = 0xFF;
    //step 6, load the start value in GPTMTBPR
    TIMER3_TBILR_R = 0xFFFF;
    //step 7, enable capture interrupt, set CBEIM bit in GPTMIMR (bit 10)
    TIMER3_IMR_R |= 0x400; //0b100 0000 0000
    TIMER3_ICR_R |= 0x400; //not listed as a step but good to clear flag initially
    //step 8, set TBEN bit in GPTMCTL to enable timer and start counting (bit 8)
    TIMER3_CTL_R |= 0x100; //0b1 0000 0000
    //step 9, not polling, interrupt will be generated (if enabled)
    //in ISR, clear status flag by writing a 1 to CBECINT bit in GPTMICR
    //in ISR, time when event happened is read from GPTMTBR
    //initialize NVIC as shown in slides
    //enable Timer3B interrupts at NVIC, IRQ Number = 36, so bit 4 of EN1
    NVIC_EN1_R |= 0x10; //0b0...10000
    //assign priority level, e.g., 1 (optional)
    //for Timer3B and IRQ 36, use PRI9, assign bit field 7:5 = 0b001
    //bit field 7:5 is in hex digit position 2 (7:4) and bit 4 is unused
    //7:5 = 0b001, 7:4 = 0b0010 = 0x2
    NVIC_PRI9_R = (NVIC_PRI9_R & 0xFFFFFF0F) | 0x00000020;
    NVIC_EN1_R |= 0x10;
    IntRegister(INT_TIMER3B, TIMER3B_Handler);

    IntMasterEnable();
    TIMER3_CTL_R |= 0x100;
    // Configure and enable the timer (steps 4 and 8_
}

/**
 * Activates the PING sensor
 */
void ping_trigger (void){
    STATE = LOW;
    // Disable timer and disable timer interrupt
    TIMER3_CTL_R &= ~0x100;
    TIMER3_IMR_R &= ~0x400;
    // Disable alternate function (disconnect timer from port pin)
    GPIO_PORTB_AFSEL_R &= ~0x8;

    // YOUR CODE HERE FOR PING TRIGGER/START PULSE
    // set PB3 to output (DIR=1), start low (DATA=0), assert high (DATA=1), hold 5 us, assert low
    GPIO_PORTB_DIR_R |= 0x08; //0b00001000
    GPIO_PORTB_DATA_R &= ~0x08; //low
    GPIO_PORTB_DATA_R |= 0x08; //high
    timer_waitMicros(5); //high start pulse for 5 microseconds
    GPIO_PORTB_DATA_R &= ~0x08; //low

    // Clear an interrupt that may have been erroneously triggered
    TIMER3_ICR_R |= 0x400;
    // Re-enable alternate function, timer interrupt, and timer
    GPIO_PORTB_AFSEL_R |= 0x8;
    TIMER3_IMR_R |= 0x400;
    TIMER3_CTL_R |= 0x100;
}

/**
 * Reads the timer values when rising and falling edges occur on the PING echo time pulse
 */
void TIMER3B_Handler(void)
{
    if (TIMER3_MIS_R & 0x400) // Checks if capture event interrupt occurred
    {
        TIMER3_ICR_R |= 0x400; // Clear capture event interrupt
        if (STATE == LOW) // Check if waiting for rising edge event
        {
            START_TIME = TIMER3_TBV_R; // Record time of rising edge event
            STATE = HIGH; // Update state after rising edge
        }
        else if (STATE == HIGH) // Check if waiting for falling edge event
        {
            END_TIME = TIMER3_TBV_R; // Record time of falling edge event
            STATE = DONE; // Update state after falling edge
        }
    }
}

/**
 * Calculates distance
 */
float ping_getDistance (void)
{
    unsigned long time_diff = 0;
    uint8_t overflow = 0; //overflow condition
    float dist = 0; //in centimeters
    unsigned long overflow_count = 0;
    ping_trigger();

    while (STATE != DONE)
    {
        // Wait for echo pulse to be received from ping sensor
    }
    overflow = END_TIME > START_TIME; //single overflow in count-down mode
    if (overflow)
    {
        overflow_count += 1;
    }
    //time difference from rising to falling edge (START to END)
    time_diff = (START_TIME - END_TIME) + ((unsigned long) overflow_count);
    dist = time_diff * 6.25e-8 * 343 * 100 / 2;

    return dist;

}
