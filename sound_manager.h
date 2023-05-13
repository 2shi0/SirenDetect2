#ifndef SOUND_MANAGER_H_
#define SOUND_MANAGER_H_

#include "fft_calculator.h"

class sound_manager
{
public:
    sound_manager();
    void mic_record_task();

private:
    void show_signal();
    size_t bytesread;
    fft_calculator f;
};

#endif