#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "sat_os.h"

typedef void (*TaskFunction_t)(void);

typedef struct
{
    TaskFunction_t task;

    uint32_t period_ms;

    uint32_t last_run;
}Task_t;

void Scheduler_Init(void);
void Scheduler_Addtask(Task_t *task);
void Scheduler_Run(void);

#endif