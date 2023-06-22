#include "m5_display.h"
#include <M5StickCPlus.h>

m5_display::m5_display()
{
}

void m5_display::init()
{
    M5.Lcd.setRotation(1);
}

void m5_display::draw(int degree)
{
    // 背景のスプライト
    mainSprite.createSprite(M5.Lcd.width(), M5.Lcd.height());

    // sprite.fillScreenは縦向きの場合のみ機能
    mainSprite.fillRect(0, 0, M5.Lcd.width(), M5.Lcd.height(), BLACK);

    mainSprite.setTextColor(WHITE);
    mainSprite.setCursor(0,125);
    mainSprite.println("0Hz");

    mainSprite.setCursor(210,125);
    mainSprite.println("41kHz");

    // 矢印のスプライト
    arrowSprite.createSprite(M5.Lcd.width(), M5.Lcd.height());
    //arrowSprite.drawCircle(M5.Lcd.width() * 0.5, M5.Lcd.height() * 0.5, M5.Lcd.height() * 0.45, GREEN);
    arrowSprite.drawRect(M5.Lcd.width() / 2, M5.Lcd.height() / 2, 50, 50, GREEN);

    arrowSprite.pushRotated(&mainSprite, degree, BLUE);

    // LCDに転写
    mainSprite.pushSprite(0, 0);
}