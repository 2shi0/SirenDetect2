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
        fft_result=f.fft(s.mic_record_task());
        for(int i=0;i<512;i++)
        Serial.println(fft_result[i]);
        delay(1);
    }
}

void task_runner::startTaskImpl(void *_this)
{
    static_cast<task_runner *>(_this)->task();
}

void task_runner::task_start()
{
    xTaskCreate(this->startTaskImpl, "Task", 4096, this, 5, NULL);
}