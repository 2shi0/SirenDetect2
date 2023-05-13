#ifndef FTT_MANAGER_H_
#define FTT_MANAGER_H_

class fft_manager
{
public:
    fft_manager();
    void task_start();

private:
    void mic_record_task();
    void task();
    static void startTaskImpl(void *_this);

    void i2s_init();
    void show_signal();
    size_t bytesread;
};

#endif