#include "fft_calculator.h"

// https://mono.dendai.ac.jp/techinfo/arduino-fft/

fft_calculator::fft_calculator()
{
    sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
    FFT = arduinoFFT(vReal, vImag, SAMPLES, SAMPLING_FREQUENCY);
}

double *fft_calculator::fft(uint16_t *adc_buffer)
{

    for (uint16_t i = 0; i < SAMPLES; i++)
    {
        unsigned long t = micros();

        vReal[i] = adc_buffer[i];
        vImag[i] = 0;
        while ((micros() - t) < sampling_period_us)
            ;
    }

    FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD); // 窓関数
    FFT.Compute(FFT_FORWARD);                        // FFT処理(複素数で計算)
    FFT.ComplexToMagnitude();                        // 複素数を実数に変換

#if 0
        for (uint16_t band = 0; band < SAMPLES; band++)
        {

            Serial.print(band);
            Serial.print(" : ");
            Serial.print((band * 1.0 * SAMPLING_FREQUENCY) / SAMPLES / 1000);
            Serial.print("kHz : ");
            //Serial.println(vReal[band] / 10000.0);
            Serial.println(vReal[band] * 0.0001);
        }
#endif

    return vReal;
}