#ifndef FFT_CALCULATOR_H_
#define FFT_CALCULATOR_H_

#include <arduinoFFT.h>

class fft_calculator
{

public:
    static const int SAMPLES = 512;
    static const int SAMPLING_FREQUENCY = 44100;
    fft_calculator();
    void fft(int16_t *adc_buffer);

private:
    arduinoFFT FFT;
};

#endif