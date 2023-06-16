#ifndef M5_DISPLAY_H__
#define M5_DISPLAY_H__

class m5_display
{
public:
    m5_display();
    void init();
    void draw();

private:
    TFT_eSprite sprite = TFT_eSprite(&M5.Lcd);
    ushort color;
};

#endif