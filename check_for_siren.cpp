#include "check_for_siren.h"

check_for_siren::check_for_siren()
{
    // 0で1本、1で3本
    width_to_get = 1;
}

bool check_for_siren::check(double *fft_result)
{

    // 770Hz ( i=89  : 7.67kHz )
    for (int i = 89 - width_to_get; i <= 89 + width_to_get; i++)
    {
        vol_770 += fft_result[i];
    }

    // 960Hz ( i=111 : 9.56kHz )
    for (int i = 111 - width_to_get; i <= 111 + width_to_get; i++)
    {
        vol_960 += fft_result[i];
    }

    Serial.println("770Hz" + String(vol_770 / 10000.0));
    Serial.println("960Hz" + String(vol_960 / 10000.0));

    return false;
}