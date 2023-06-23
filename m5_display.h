#ifndef M5_DISPLAY_H__
#define M5_DISPLAY_H__

#include <M5StickCPlus.h>
#include "fft_calculator.h"
#include "check_for_siren.h"
#include "vive_control.h"

class m5_display
{
public:
    m5_display();
    void init();
    void draw(double *fft_result);

private:
    check_for_siren c;
    vive_control v;
    TFT_eSprite mainSprite = TFT_eSprite(&M5.Lcd);
    TFT_eSprite arrowSprite = TFT_eSprite(&M5.Lcd);
    int deg;
};

#endif