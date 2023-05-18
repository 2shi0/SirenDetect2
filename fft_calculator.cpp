#include "fft_calculator.h"

// https://mono.dendai.ac.jp/techinfo/arduino-fft/
double vReal[fft_calculator::SAMPLES]; // 複素データreal領域（時間軸データ領域）
double vImag[fft_calculator::SAMPLES]; // 複素データmag領域

fft_calculator::fft_calculator()
{
    FFT = arduinoFFT();
}

void fft_calculator::fft(int16_t *adc_buffer)
{
    for (uint16_t i = 0; i < SAMPLES; i++)
    {
        vReal[i] = adc_buffer[i];
        vImag[i] = 0;
    }

    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_RECTANGLE, FFT_FORWARD); // 窓関数演算
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);                   // FFT演算
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);                     // パワー(V)演算

    for (uint16_t band = 0; band < SAMPLES; band++)
    {
#if 0
        Serial.print(band);
        Serial.print(" : ");
        Serial.print((band * 1.0 * SAMPLING_FREQUENCY) / SAMPLES / 1000);
        Serial.print("kHz : ");
        Serial.println(vReal[band] / 10000.0);
#endif
    }
}