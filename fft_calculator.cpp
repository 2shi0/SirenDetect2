#include "fft_calculator.h"

// https://mono.dendai.ac.jp/techinfo/arduino-fft/

fft_calculator::fft_calculator()
{
    FFT = arduinoFFT();
}

double *fft_calculator::fft(int16_t *adc_buffer)
{

    for (uint16_t i = 0; i < SAMPLES; i++)
    {
        vReal[i] = adc_buffer[i];
        vImag[i] = 0;
    }

    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_RECTANGLE, FFT_FORWARD); // 窓関数演算
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);                   // FFT演算
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);                     // パワー(V)演算

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