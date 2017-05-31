#include "main.h"

extern void tick_handler(void);

interrupt_handler(void)
{
    //clear flag

    tick_handler();    
}

void system_clock_init(uint32_t freq)
{

}

void timer_init(uint32_t tick)
{

}

void timer_start(void)
{

}

void timer_interrupt_enable(void)
{

}

void int_enable(void)
{

}

void int_disable(void)
{

}

void sleep(void)
{

}

void mcu_init(void)
{
    //init system clock
    system_clock_init(16000000);
    
    int_enable();    
}

void tasks_init(void)
{
    // Set up WDT 
    // Timeout is WDT count value: approx 32 per millisecond
    // => a count of 64 gives a timeout of approx 2 ms
    // NOTE: WDT driven by RC oscillator - timing varies with temperature 
    WATCHDOG_Init(60);

    // Prepare for switch task
    SWITCH_BUTTON1_Init();

    // Prepare for heartbeat-switch task
    HEARTBEAT_SW_U_Init();

    // Prepare for UART1 task (set baud rate)
    UART2_BUF_O_Init(115200);

    // Report mode (via buffer)          
    UART2_BUF_O_Write_String_To_Buffer("\nNormal mode\n");  

    // Add tasks to schedule.
    // Parameters are:
    // A. Task name
    // B. Initial delay / offset (in Ticks)
    // C. Task period (in Ticks): Must be > 0
    //           A                       B  C
    SCH_Add_Task(WATCHDOG_Update,        0, 1);     // Feed iWDT
    SCH_Add_Task(SWITCH_BUTTON1_Update,  0, 1);     // Switch interface 
    SCH_Add_Task(HEARTBEAT_SW_U_Update1, 0, 1000);  // Heartbeat LED
    SCH_Add_Task(UART2_BUF_O_Update,     0, 1);     // UART-USB reports  
    SCH_Add_Task(protocol_update,        0, 10);    // protocol task      
}
