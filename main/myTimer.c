#include <driver/timer.h>
#include "myTimer.h"
#include "myGpio.h"
 
static volatile uint8_t _millis = 0; 

/* Timer interrupt service routine */
static void IRAM_ATTR timer0Isr(void *ptr)
{
    timer_group_clr_intr_status_in_isr(TIMER_GROUP_0, TIMER_0);
    timer_group_enable_alarm_in_isr(TIMER_GROUP_0, TIMER_0);
    _millis++;

    // TODO
    // Add logic for state machine that plays back the note array,
    // inserting silence between notes, if needed, update Timer1 alarm value
}

/* Timer interrupt service routine */
static void IRAM_ATTR timer1Isr(void *ptr)
{
    timer_group_clr_intr_status_in_isr(TIMER_GROUP_0, TIMER_1);
    timer_group_enable_alarm_in_isr(TIMER_GROUP_0, TIMER_1);
    
    // Toggle GPIO with myGpio functions
}

/* Timer group0 TIMER_0 initialization */
static void timer0Init(void)
{
    // TODO Use only Low level register to configure a 1ms tick

    /* Register an ISR handler */
    timer_isr_register(TIMER_GROUP_0, TIMER_0, timer0Isr, NULL, 0, NULL);
}

void timer1Play(const struct note song[], uint16_t len)
{
    /* Save song pointer and restart playback state machine */
    timer_isr_register(TIMER_GROUP_0, TIMER_1, timer1Isr, NULL, 0, NULL);
}

/* Timer group0 TIMER_1 configuration */
void IRAM_ATTR timer1FreqGen(uint16_t freq)
{
    // Use only Low level register to configure Timer 1
    /* Register an ISR handler */
}
