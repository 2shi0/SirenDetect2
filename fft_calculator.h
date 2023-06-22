#ifndef FFT_CALCULATOR_H_
#define FFT_CALCULATOR_H_

#include <arduinoFFT.h>

class fft_calculator
{

public:
    static const int SAMPLES = 512;
    static const int SAMPLING_FREQUENCY = 44100;
    fft_calculator();
    double *fft(int16_t *adc_buffer);
    double vReal[SAMPLES]; // 複素データreal領域（時間軸データ領域）
    double vImag[SAMPLES]; // 複素データmag領域

private:
    arduinoFFT FFT;
};

#endif