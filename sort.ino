/// @brief バンドの太さごとにソート（上から10個ぐらい）
void sortBand()
{
    int temp = 0;
    for (int i = 0; i < RMAX; i++)
    {
        for (int j = 0; j < MAX_BAND; j++)
        {
            if (zipedList[temp] < zipedList[j])
            {
                temp = j;
            }
        }
        sortedList[i] = temp;
        //Hzに変換
        hzList[i] = (int)(temp * 1.0 * SAMPLING_FREQUENCY) / FFTsamples;
        zipedList[temp] = 0;
        temp = 0;
    }
}