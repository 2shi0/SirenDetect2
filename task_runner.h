#ifndef TASK_RUNNER_H_
#define TASK_RUNNER_H_

#include "sound_manager.h"
#include "fft_calculator.h"

class task_runner
{
public:
    task_runner();
    void task_start();

private:
    sound_manager s;
    fft_calculator f;
    void task();
    static void startTaskImpl(void *_this);
};

#endif