// https://lang-ship.com/blog/work/m5stickc-mic/
// https://nyarurato.hatenablog.com/entry/2020/05/02/144514
// https://github.com/lovyan03/LovyanGFX
#define READ_LEN (2 * 1024)
#define SAMPLING_FREQUENCY 44100

#define RMAX 10

#define BTN_A_PIN 37

#define CLOSE 2000
#define OPEN 5000

#define MAX_BAND 512

//保持しておくfft済みデータの数
#define KEEP_NUM 8

#define SDS_SLAVE_ADDRESS 0x30
#define SDS_ACTVAL_REG 0x04

#include <Wire.h>
#include <M5StickCPlus.h>
#include <RTC.h>
#include <driver/i2s.h>
#include "arduinoFFT.h"

//未ソート
float bandList[KEEP_NUM][MAX_BAND];

//未ソートを圧縮
float zipedList[MAX_BAND];

//ソート済みリスト（ランキング）
int sortedList[RMAX];

// Hzに変換したやつ
int hzList[RMAX];

//サーボ
/*
const int servoPin = 26;
const double PWM_Hz = 50;     // PWM周波数
const uint8_t PWM_level = 16; // PWM 16bit(0～65535)
*/

//文字をバスみたいにするカウント
int scrollCount = 135;

//検知した音が続いているか
int toneCount = 0;

//一定サイクルでtoneCountのスタックをリセット
int delayCount = 0;

//リセットの間隔
int resetInterval = 1500;

//何個スタックしたら通知するか
int stackLength = 5;

//サイレンを検知したら1
bool detectFlag = 0;

// mic record task関連
unsigned int sampling_period_us;
uint8_t BUFFER[READ_LEN] = {0};
uint16_t *adcBuffer = NULL;

//処理時間計測用
unsigned long t1, t2;

//現在のモード
int soundMode = 0;
int maxMode = 5;

//画面切り替え
bool displayMode = 1;

//方向表示（画面表示用）
String d = "";

// fft用オブジェクト関連
const uint16_t FFTsamples = 512; // サンプル数は2のべき乗
double vReal[FFTsamples];        // vReal[]にサンプリングしたデーターを入れる
double vImag[FFTsamples];
arduinoFFT FFT = arduinoFFT(vReal, vImag, FFTsamples, SAMPLING_FREQUENCY); // FFTオブジェクトを作る

//スプライトと三ツ矢サイダーの違い
TFT_eSprite sprite(&M5.Lcd);

// lookBand出身
int ditectStock = 0;

//横向き
// TFT_eSprite sprite2(&M5.Lcd);

//矢印のsprite
TFT_eSprite arrow(&M5.Lcd);

//音方位基板関係
float ActivityValueThreshold = 1.0f;
int actset;
byte writeValArry[4];
float degree;
float activity;

//バイブ
bool viveFlag = 0;

/// @brief レコードタスクの終着点
/// @param arg わかんない
void mic_record_task(void *arg)
{
    while (1)
    {
        directionCheck();

        //処理時間を測る（開始地点）
        t1 = micros();

        shift();
        record();
        fft();
        // compress();
        // sortBand();

        lookBand();

        // detect();

        //処理時間均一化委員会
        // 100000で0.1ms
        // while ((micros() - t1) < 100000);

        //処理時間を測る（終了地点）
        t2 = micros();

        draw();

        vTaskDelay(10 / portTICK_RATE_MS);
    }
}
void setup()
{
    // Serial.begin(115200);
    // while (!Serial);
    // setCpuFrequencyMhz(40);
    M5.begin();

    //画面の向き
    M5.Lcd.setRotation(1);

    //ボタン
    pinMode(BTN_A_PIN, INPUT_PULLUP);

    //バイブ
    pinMode(26, OUTPUT);

    //サーボ
    /*
    pinMode(servoPin, OUTPUT);
    ledcSetup((uint8_t)1, PWM_Hz, PWM_level);
    ledcAttachPin(servoPin, 1);
    ledcWrite(1, CLOSE);
    */

    //音方位
    i2cInit();

    // スプライトの作成
    sprite.createSprite(M5.Lcd.width(), M5.Lcd.height());
    sprite.setTextSize(2);

    arrowInit();

    // M5.Lcd.setRotation(3);
    // sprite2.createSprite(M5.Lcd.width(), M5.Lcd.height());
    // sprite2.setTextSize(2);

    sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));

    i2sInit();
    xTaskCreatePinnedToCore(mic_record_task, "mic_record_task", 2048, NULL, 1, NULL, 1);
}

void loop()
{
    //ボタンを見る
    if (!digitalRead(BTN_A_PIN))
    {
        //文字位置リセット
        // scrollCount = 135;

        displayMode = !displayMode;

        Serial.println(displayMode);

        if (displayMode)
        {
            //通常モード
            M5.Lcd.setRotation(1);

            // 画面の向き
            // M5.Lcd.setRotation(3);
            // sprite2.setCursor(0, 0);
            // sprite2.fillScreen(BLUE);
            // sprite2.print("Where?");
            // sprite2.pushSprite(0,0);
        }
        else
        {
            //デバッグモード
            M5.Lcd.setRotation(0);

            //画面の向き
            // M5.Lcd.setRotation(0);
            // sprite.setCursor(0, 0);
            // sprite.fillScreen(BLACK);
            // sprite.pushSprite(0, 0);
        }

        //切替時に画面を掃除

        /*
        if (soundMode < maxMode)
        {
            soundMode++;
        }
        else
        {
            soundMode = 0;
        }
        */

        while (!digitalRead(BTN_A_PIN))
            delay(1);
    }

    //バイブ

    if (viveFlag)
    {
        digitalWrite(26, HIGH); // LEDをオン
        delay(250);             // 1秒待つ
        digitalWrite(26, LOW);  // LEDをオフ
        delay(500);
        digitalWrite(26, HIGH); // LEDをオン
        delay(250);             // 1秒待つ
        digitalWrite(26, LOW);  // LEDをオフ

        viveFlag = 0;
    }

    delay(1);
}