#include <M5StickCPlus.h>
#include "task_runner.h"

task_runner::task_runner()
{
}

// https://stackoverflow.com/questions/45831114/c-freertos-task-invalid-use-of-non-static-member-function
void task_runner::task()
{
    while (1)
    {
        this->s.mic_record_task();
    }
}

void task_runner::startTaskImpl(void *_this)
{
    static_cast<task_runner *>(_this)->task();
}

void task_runner::task_start()
{
    xTaskCreate(this->startTaskImpl, "Task", 2048, this, 5, NULL);
}