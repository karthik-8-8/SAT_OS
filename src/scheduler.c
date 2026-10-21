#include "scheduler.h"
#include "pico/time.h"
#define MAX_TASKS 10

static Task_t *task_list[MAX_TASKS];

static uint8_t task_count = 0;

void Scheduler_Init(void)
{
    task_count=0;
}

void Scheduler_Addtask(Task_t *task)
{
    if(task_count<MAX_TASKS)
    {
        task_list[task_count]= task;

        task_count++;
    }
}
void Scheduler_Run(void)
{
    uint32_t now = to_ms_since_boot(get_absolute_time());

    for(uint8_t i = 0; i < task_count; i++)
    {
        Task_t *task = task_list[i];

        if((now - task->last_run) >= task->period_ms)
        {
            task->task();

            task->last_run = now;
        }
    }
}