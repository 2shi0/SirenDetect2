#include "vive_control.h"

vive_control::vive_control()
{
    pinMode(vive_pin, OUTPUT);
}

void vive_control::vive(int ms)
{
    digitalWrite(vive_pin, HIGH);
    delay(ms);
    digitalWrite(vive_pin, LOW);
    delay(ms);
}