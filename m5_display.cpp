#include "m5_display.h"
#include "fft_calculator.h"
#include <M5StickCPlus.h>

m5_display::m5_display()
{
    deg = 0;
}

void m5_display::init()
{
    M5.Lcd.setRotation(1);
}

void m5_display::draw(double *fft_result)
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

    // グラフ
    if (fft_result != NULL)
        for (int i = 0; i < M5.Lcd.width(); i++)
        {
            int tmp = 120 - int(fft_result[i] * 0.0001);
            if (tmp > 0)
                mainSprite.drawLine(i, 120, i, tmp, LIGHTGREY);
            else
                mainSprite.drawLine(i, 120, i, 0, LIGHTGREY);
            // Serial.println(tmp);
        }

    // くるくる
    arrowSprite.createSprite(M5.Lcd.height() * 0.5, M5.Lcd.height() * 0.5);
    arrowSprite.drawRect(0, 0, M5.Lcd.height() * 0.5, M5.Lcd.height() * 0.5, GREEN);
    arrowSprite.pushRotated(&mainSprite, deg, BLACK);

    deg++;
    if (deg > 360)
        deg = 0;

    // LCDに転写
    mainSprite.pushSprite(0, 0);
}