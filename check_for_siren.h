#ifndef CHECK_FOR_SIREN_H_
#define CHECK_FOR_SIREN_H_
#include "Arduino.h"

class check_for_siren
{
public:
    check_for_siren();
    bool check(double *fft_result, double offset);

private:
    int width_to_get;
    double vol_770 = 0;
    double vol_960 = 0;
    static const int stock_length = 8;
    double stock_array[2][stock_length];
};

#endif