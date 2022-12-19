float dmax = 10000.0;

/// @brief i2sから取った音をfftにかける
void fft()
{
    for (int i = 0; i < FFTsamples; i++)
    {
        unsigned long t = micros();
        vReal[i] = adcBuffer[i];
        vImag[i] = 0;
        while ((micros() - t) < sampling_period_us)
            ;
    }

    FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD); // 窓関数
    FFT.Compute(FFT_FORWARD);                        // FFT処理(複素数で計算)
    FFT.ComplexToMagnitude();                        // 複素数を実数に変換

    for (int band = 0; band < MAX_BAND; band++)
    {
        bandList[0][band] = vReal[band] / dmax;
        /*
        Serial.print(band);
        Serial.print(" : ");
        Serial.print((band * 1.0 * SAMPLING_FREQUENCY) / FFTsamples / 1000);
        Serial.print("kHz : ");
        Serial.println(bandList[0][band]);
        */
    }
}