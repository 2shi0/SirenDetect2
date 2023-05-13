#ifndef FFT_CALCULATOR_H_
#define FFT_CALCULATOR_H_

#include <arduinoFFT.h>

class fft_calculator
{
public:
    fft_calculator();
    void fft(int16_t *adc_buffer);

private:
    arduinoFFT FFT;
};

#endif