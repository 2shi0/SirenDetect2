#ifndef VIVE_CONTROL_H__
#define VIVE_CONTROL_H__

class vive_control
{
public:
    vive_control();
    void vive(int ms);

private:
    const int vive_pin = 26;
};

#endif