
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "play_wave.h"

#define DEVICE_FORMAT       ma_format_u8
#define DEVICE_CHANNELS     1
#define DEVICE_SAMPLE_RATE  22050//48000

int g_play_finished=0;
int g_played_len = 0;

int write_to_wav(char *file_name)
{
    return 0;
}



void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    ///对于单通道的8bit数据，一帧就是8bit
    /// frame_byte = one_sample_byte * channel_num
    ma_waveform* pSineWave;

    MA_ASSERT(pDevice->playback.channels == DEVICE_CHANNELS);

    pSineWave = (ma_waveform*)pDevice->pUserData;
    MA_ASSERT(pSineWave != NULL);

    ma_waveform_read_pcm_frames(pSineWave, pOutput, frameCount, NULL);

    g_played_len += frameCount;
    //set g_play_finished if finished
    if(g_played_len-frameCount>22050){
        g_play_finished = 1;
    }

    (void)pInput;   /* Unused. */
}

int play_snd()
{

    ma_waveform sineWave;
    ma_waveform_config sineWaveConfig;
    sineWaveConfig = ma_waveform_config_init(DEVICE_FORMAT, DEVICE_CHANNELS, DEVICE_SAMPLE_RATE, ma_waveform_type_sine, 0.2, 220);
    ma_waveform_init(&sineWaveConfig, &sineWave);



    ma_device device;
    ma_device_config deviceConfig;

       deviceConfig = ma_device_config_init(ma_device_type_playback);
       deviceConfig.playback.format   = DEVICE_FORMAT;
       deviceConfig.playback.channels = DEVICE_CHANNELS;
       deviceConfig.sampleRate        = DEVICE_SAMPLE_RATE;
       deviceConfig.dataCallback      = data_callback;
       deviceConfig.pUserData         = &sineWave;

       if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS)
       {
           printf("Failed to open playback device.\n");
           return -4;
       }

       printf("Device Name: %s\n", device.playback.name);

       if (ma_device_start(&device) != MA_SUCCESS)
       {
           printf("Failed to start playback device.\n");
           ma_device_uninit(&device);
           return -5;
       }

   #ifdef __EMSCRIPTEN__
       emscripten_set_main_loop(main_loop__em, 0, 1);
   #else
       printf("Press Enter to quit...\n");
       while(!g_play_finished)
       {
           ma_sleep(100);
       }
       //if(!ma_sound_at_end())sleep(100);

   #endif

       ma_device_uninit(&device);

    return 0;
}
