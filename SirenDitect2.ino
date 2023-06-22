#include <M5StickCPlus.h>
#include "task_runner.h"
#include "m5_display.h"

m5_display m;
task_runner t;

void setup()
{
    M5.begin();

    t.task_start();

    m.init();
}

int deg = 0;

void loop()
{
    m.draw(deg);
    deg++;
    if (deg > 360)
        deg = 0;
}