#ifndef M5_DISPLAY_H__
#define M5_DISPLAY_H__

#include <M5StickCPlus.h>
#include "fft_calculator.h"

class m5_display
{
public:
    m5_display();
    void init();
    void draw(int degree);

private:
    TFT_eSprite mainSprite = TFT_eSprite(&M5.Lcd);
    TFT_eSprite arrowSprite = TFT_eSprite(&M5.Lcd);
};

#endif