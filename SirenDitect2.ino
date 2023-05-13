#include <M5StickCPlus.h>
#include "task_runner.h"

void setup()
{
    M5.begin();
    M5.Lcd.setRotation(1);
    M5.Lcd.fillScreen(WHITE);
    
    task_runner t;
    t.task_start();
}
void loop()
{
    delay(1);
}