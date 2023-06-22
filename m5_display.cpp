#include "m5_display.h"
#include "fft_calculator.h"
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
    mainSprite.setCursor(0, 125);
    mainSprite.println("0.02kHz");

    mainSprite.setCursor(70, 125);
    mainSprite.println("6kHz");

    mainSprite.setCursor(140, 125);
    mainSprite.println("12kHz");

    mainSprite.setCursor(210, 125);
    mainSprite.println("20kHz");

    // くるくる
    arrowSprite.createSprite(M5.Lcd.height() * 0.5, M5.Lcd.height() * 0.5);
    arrowSprite.drawRect(0, 0, M5.Lcd.height() * 0.5, M5.Lcd.height() * 0.5, GREEN);
    arrowSprite.pushRotated(&mainSprite, degree, BLUE);

    // グラフ
    for (int i = 0; i < M5.Lcd.width(); i++)
    {
        //mainSprite.drawLine(i,123,i,(int)fft_calculator::vReal[i] / 10000.0);
    }

    // LCDに転写
    mainSprite.pushSprite(0, 0);
}