// scaning... 文字
String s = "Scaning";
int c = 0;

// 角度
int arr = 0;

void draw()
{
    sprite.setTextSize(2);

    if (displayMode)
    {
        // 通常モード
        nomalDisplay();

        // スプライトを表示画面に転送する（描画）
        sprite.pushSprite(0, 0);
    }
    else
    {
        // スプライトを黒く塗りつぶす
        sprite.fillScreen(BLACK);
        sprite.setCursor(0, 0);

        // デバッグモード
        debugDisplay();

        // スプライトを表示画面に転送する（描画）
        sprite.pushSprite(0, 0);
    }
}

void nomalDisplay()
{
    sprite.setCursor(10, 10);
    sprite.setTextSize(3);

    if (detectFlag)
    {
        sprite.setTextColor(WHITE, RED);

        // スプライトを塗りつぶす
        sprite.fillRect(0, 0, M5.Lcd.width(), M5.Lcd.height(), RED);

        sprite.println("DETECTED");

    }
    else
    {
        // スプライトを塗りつぶす
        sprite.fillRect(0, 0, M5.Lcd.width(), M5.Lcd.height(), BLUE);

        sprite.setTextColor(WHITE, BLUE);

        c++;
        if (c < 10)
        {
            sprite.println("Scaning");
        }
        else if (c < 20)
        {
            sprite.println("Scaning.");
        }
        else if (c < 30)
        {
            sprite.println("Scaning..");
        }
        else if (c < 40)
        {
            sprite.println("Scaning...");
        }
        else if (c < 50)
        {
            sprite.println("Scaning....");
        }
        else
        {
            sprite.println("Scaning....");
            c = 0;
        }

        sprite.setCursor(10, 100);
        sprite.setTextColor(BLACK, BLUE);
        sprite.println("TH:"+(String)detectSoundLevel);

        
        sprite.setTextColor(BLACK, BLUE);
        sprite.setCursor(170, 100);
        unsigned int b = (M5.Axp.GetBatVoltage() - 3) * 100 / 1.2;
        sprite.print(b);
        sprite.print("%");
    }
}
void debugDisplay()
{
    sprite.setTextSize(2);

    for (int i = 0; i < RMAX; i++)
    {
        // 人気バンドランキング
        int hz = hzList[i];
        sprite.setTextColor(WHITE);
        if (i < 9)
            sprite.print(" ");
        sprite.print(i + 1);
        sprite.print(":");
        for (int j = 0; j < 5 - get_digit(hz); j++)
        {
            sprite.print(" ");
        }
        sprite.print(hz);
        sprite.println(" Hz");
    }

    // 処理時間
    sprite.setTextColor(DARKGREY);
    sprite.print("    ");
    sprite.print((float)(t2 - t1) / 1000000);
    sprite.println(" ms");

    // 現在のモード
    sprite.setTextColor(YELLOW);

    String modeText = "";
    modeText += "1000Hz";
    modeText += " Mode";
    sprite.drawString(modeText, scrollCount, sprite.cursor_y);
    sprite.println("");

    // 文字スクロールのカウント
    if (scrollCount > -(int(modeText.length()) * 12))
    {
        scrollCount -= 4;
    }
    else
    {
        scrollCount = 135;
    }
    // バッテリー残量
    sprite.setTextColor(BLUE);
    unsigned int b = (M5.Axp.GetBatVoltage() - 3) * 100 / 1.2;
    sprite.print(b);
    sprite.print("%");
    sprite.print("(");
    sprite.print(M5.Axp.GetBatVoltage());
    sprite.print("V");
    sprite.println(")");

    if (M5.Axp.GetBatCurrent() > -1)
    {
        sprite.println("CHARGING");
    }
}

// 桁数を求める
unsigned int get_digit(unsigned int n)
{
    unsigned int digit = 1;

    while (n /= 10)
    {
        ++digit;
    };

    return digit;
}

// 矢印画像　初期設定
void arrowInit()
{
    arrow.createSprite(M5.Lcd.height(), M5.Lcd.height());

    // 矢印BB
    arrow.fillScreen(BLUE);
    arrow.fillTriangle(M5.Lcd.height() / 2, 5,
                       M5.Lcd.height() / 4, 50,
                       M5.Lcd.height() * 3 / 4, 50,
                       WHITE);
    arrow.fillRect(M5.Lcd.height() * 2 / 5, 50, M5.Lcd.height() / 5, 80, WHITE);
}
