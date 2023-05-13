#ifndef SOUND_MANAGER_H_
#define SOUND_MANAGER_H_

class sound_manager
{
public:
    sound_manager();
    void mic_record_task();

private:
    void show_signal();
    size_t bytesread;
};

#endif