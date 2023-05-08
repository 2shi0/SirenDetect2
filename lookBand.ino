int deathCountGX = 10;

bool firstCheck = 1;
void lookBand()
{
    //感度の閾値？
    float GoldenRaspberry = 0;
    for (int band = 10; band < 14; band++)
    {

        float stock = 0;
        for (int i = 0; i < RMAX; i++)
        {
            stock += bandList[i][band];
        }

        /*
        Serial.print(band);
        Serial.print(" : ");
        Serial.print((band * 1.0 * SAMPLING_FREQUENCY) / FFTsamples / 1000);
        Serial.print("kHz : ");
        Serial.println(stock);
        */

        GoldenRaspberry += stock;
    }

    //Serial.println(GoldenRaspberry);

    if (GoldenRaspberry > 2000)
    {
        if (firstCheck)
        {
            viveFlag = 1;
            firstCheck = 0;
            ditectStock = 5;
        }
    }

    if (GoldenRaspberry > 1500 && !firstCheck)
    {
        if (ditectStock < 5)
            ditectStock++;
    }
    else
    {
        if (ditectStock > 0)

            ditectStock--;
    }

    if (ditectStock > 2)
    {
        detectFlag = 1;
    }
    else if (ditectStock == 0)
    {
        detectFlag = 0;
        firstCheck = 1;
    }
}
