#ifndef SOUND_MANAGER_H_
#define SOUND_MANAGER_H_

#include "fft_calculator.h"

class sound_manager
{
public:
    static const int PIN_CLK = 0;
    static const int PIN_DATA = 34;
    static const int READ_LEN = (2 * 256);
    sound_manager();
    uint16_t *mic_record_task();

private:
    size_t bytesread;
};

#endif