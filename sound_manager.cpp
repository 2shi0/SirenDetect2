#include <M5StickCPlus.h>
#include <driver/i2s.h>
#include "sound_manager.h"

uint8_t BUFFER[sound_manager::READ_LEN];
uint16_t *adc_buffer;

// https://lang-ship.com/blog/work/m5stickc-mic/
sound_manager::sound_manager()
{
     i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM),
        .sample_rate = 44100,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT, // is fixed at 12bit, stereo, MSB
        .channel_format = I2S_CHANNEL_FMT_ALL_RIGHT,
        .communication_format = I2S_COMM_FORMAT_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 2,
        .dma_buf_len = 512,
    };

    i2s_pin_config_t pin_config;
    pin_config.bck_io_num = I2S_PIN_NO_CHANGE;
    pin_config.ws_io_num = PIN_CLK;
    pin_config.data_out_num = I2S_PIN_NO_CHANGE;
    pin_config.data_in_num = PIN_DATA;

    i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_NUM_0, &pin_config);
    i2s_set_clk(I2S_NUM_0, 44100, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO);
}

uint16_t *sound_manager::mic_record_task()
{
    i2s_read_bytes(I2S_NUM_0, (char *)BUFFER, READ_LEN, (20 / portTICK_RATE_MS));
    adc_buffer = (uint16_t *)BUFFER;
    return adc_buffer;
    // vTaskDelay(100 / portTICK_RATE_MS);
}
