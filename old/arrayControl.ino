// 2次元配列を1次元配列に
void compress()
{
    for (int i = 0; i < MAX_BAND; i++)
    {
        float temp = 0;
        for (int j = 0; j < KEEP_NUM; j++)
        {
            temp += bandList[j][i];
        }
        zipedList[i] = temp;
    }
}

//配列を右にずらす(list[0]に空きを作る)
void shift()
{
    for (int i = KEEP_NUM - 1; i > 0; i--)
    {
        for (int j = 0; j < MAX_BAND; j++)
        {
            bandList[i][j] = bandList[i - 1][j];
        }
    }
}