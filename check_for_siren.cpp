#include "check_for_siren.h"

check_for_siren::check_for_siren()
{
    // 0で1本、1で3本
    width_to_get = 0;

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < stock_length; j++)
            stock_array[i][j] = 0;
}

bool check_for_siren::check(double *fft_result, double offset)
{
    bool flag = false;
    // 770Hz ( i=89  : 7.67kHz )
    for (int i = 89 - width_to_get; i <= 89 + width_to_get; i++)
    {
        double tmp = fft_result[i] - offset;
        if (tmp > 0)
            vol_770 += tmp;
    }

    // 960Hz ( i=111 : 9.56kHz )
    for (int i = 111 - width_to_get; i <= 111 + width_to_get; i++)
    {
        double tmp = fft_result[i] - offset;
        if (tmp > 0)
            vol_960 += tmp;
    }

    // Serial.println("770Hz" + String(vol_770 / 10000.0));
    // Serial.println("960Hz" + String(vol_960 / 10000.0));

    // ストックを一段シフト
    for (int i = stock_length - 1; i > 0; i--)
    {
        stock_array[0][i] = stock_array[0][i - 1];
        stock_array[1][i] = stock_array[1][i - 1];
    }

    // 現在の値をストック
    stock_array[0][0] = vol_770 / 10000.0;
    stock_array[1][0] = vol_960 / 10000.0;

    // ストックの平均を算出
    double stock_ave[2] = {0, 0};
    for (int i = 0; i < stock_length; i++)
    {
        stock_ave[0] += stock_array[0][i];
        stock_ave[1] += stock_array[1][i];
    }

    stock_ave[0] = stock_ave[0] / stock_length;
    stock_ave[1] = stock_ave[1] / stock_length;

    Serial.println("770Hz" + String(stock_ave[0]));
    Serial.println("960Hz" + String(stock_ave[1]));

    // 閾値を超えていたら検知
    if (stock_ave[0] < 4 && stock_ave[1] < 4)
        flag = true;

    vol_770 = 0;
    vol_960 = 0;

    return flag;
}