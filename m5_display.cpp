#include <M5StickCPlus.h>
#include "m5_display.h"

m5_display::m5_display()
{
    
}

void m5_display::init()
{
    color = 0x0000;
    
    sprite.createSprite(M5.Lcd.width(), M5.Lcd.height());
    sprite.fillScreen(color);
    sprite.pushSprite(0, 0);
}

void m5_display::draw()
{
    sprite.fillScreen(color);
    sprite.pushSprite(0, 0);

    if (color < 0xFFFF)
        color++;

    else
        color = 0x0000;
}