#include <M5StickCPlus.h>
#include "task_runner.h"
#include "m5_display.h"

m5_display m;

void setup()
{
    M5.begin();
    //M5.Lcd.fillScreen(WHITE);

    task_runner t;
    t.task_start();

    m.init();

}
void loop()
{
    m.draw();
    delay(1);
}