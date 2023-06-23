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

    // オフセット計測（平均値算出）
    double offset = 0;
    for (int i = 0; i < 512; i++)
    {
        offset += fft_result[i];
    }
    offset = offset / 512;

    // グラフ
    if (fft_result != NULL)
        for (int i = 0; i < M5.Lcd.width(); i++)
        {
            int tmp = offset / 10000.0 + 120 - int(fft_result[i] / 10000.0);
            if (tmp < 120)
                mainSprite.drawLine(i, 120, i, tmp, LIGHTGREY);
            // Serial.println(tmp);
        }

    /*
    mainSprite.setTextColor(GREEN);
    mainSprite.setCursor(180, 0);
    mainSprite.println("770Hz:"+String(amb_array));
    mainSprite.setCursor(180, 10);
    mainSprite.println("960Hz:"+String(amb_array[1]));
    */

    // くるくる
    arrowSprite.createSprite(M5.Lcd.height() * 0.5, M5.Lcd.height() * 0.5);
    arrowSprite.drawRect(0, 0, M5.Lcd.height() * 0.5, M5.Lcd.height() * 0.5, GREEN);

    // 救急車の周波数（数字）
    if (c.check(fft_result, offset))
    {
        v.vive(200);
    }

    // くるくるをmainに転写
    arrowSprite.pushRotated(&mainSprite, deg, BLACK);

    deg++;
    if (deg > 360)
        deg = 0;

    // LCDに転写
    mainSprite.pushSprite(0, 0);
}