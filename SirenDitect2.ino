#include "FftManager.h"
#include <M5StickCPlus.h>
void setup()
{
    M5.begin();
    M5.Lcd.setRotation(1);
    M5.Lcd.fillScreen(WHITE);
    
    fft_manager fm;
    fm.task_start();
}
void loop()
{
    delay(1);
}