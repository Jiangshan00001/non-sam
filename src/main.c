#include <string.h>
#include <stdio.h>
#include "main.h"
#include "phoneme_to_wave.h"
#include "phoneme_adjust.h"
#include "prints.h"
#include "play_wave.h"
#include "text_to_phoneme.h"
#include "text_to_text.h"

///
/// @mainpage
/// phsource--> data for construct phoneme
/// dictsource-->text to phoneme translation
/// espeak-ng-data/voices --> language specific attribute
///
/// this is a totally reimplemention of formant voice synthesis software.
/// it is highly inspaired by sam & espeak.
/// it's phoneme data is from espeak-ng.
/// it support chinese and english by default.
/// the code size is limited to <64kbytes.
/// the programming language is limited to c.
///
///
/// translation steps:
/// 1. text-to-text: 100$ -> hundred dollars, June 1->first of June
/// 2. text-to-phoneme:
/// 3. phoneme-adjust: tone settings, vowel-const adjust by rule.
/// 4. phoneme-to-wave.
///
/// implemention:
/// 1. phoneme->code  TODO
/// 2. phoneme->wave  TODO
/// 3. rule->phoneme TODO
/// 4. pinyin->phoneme->wave  TODO
/// 5. english->phoneme->wave  TODO
///
///
///
///
///
/// \brief main
/// \param argc
/// \param argv
/// \return
///
///


char * g_wavfilename=0;
int g_is_phonetic = 0;
int g_is_pinyin = 0;
char g_input[INPUT_BUFFER_SIZE];
char g_phoneme[INPUT_BUFFER_SIZE*4];
int g_is_raw = 0;

char *g_buffer=0;
int g_buffer_len=0;



typedef struct FRAME_ONE_TAG
{
int m_pad;

}FRAME_ONE;



int parse_args(int argc, char *argv[])
{
    int i;


    i = 1;
    while(i < argc)
    {
        if (argv[i][0] != '-')
        {
            //strcpy_s(g_input,INPUT_BUFFER_SIZE, argv[i]);
            strncpy(g_input,argv[i], strlen(argv[i])>INPUT_BUFFER_SIZE?INPUT_BUFFER_SIZE:strlen(argv[i]));
        } else
        {
            if (argv[i][1]=='w')
            {
                g_wavfilename = argv[i+1];
                i++;
            } else
            if (argv[i][1]=='i')
            {
                //EnableSingmode();
            } else
            if (argv[i][1]=='m')
            {
                g_is_phonetic = 1;
            } else
            if (argv[i][1]=='p')
            {
                g_is_pinyin = 1;
            } else
            if (argv[i][1]=='d')
            {
                g_debug = 1;
            } else
            if (argv[i][1]=='t')
            {
                //SetPitch((unsigned char)atoi(argv[i+1]));
                i++;
            } else
            if (argv[i][1]=='s')
            {
                //SetSpeed((unsigned char)atoi(argv[i+1]));
                i++;
            } else
            if (argv[i][1]=='f')
            {
                //SetMouth((unsigned char)atoi(argv[i+1]));
                i++;
            } else
            if (argv[i][1]=='g')
            {
                //SetThroat((unsigned char)atoi(argv[i+1]));
                i++;
            }
            else if(argv[i][1]=='r')
            {
                g_is_raw  = 1;
            }
            else
            {
                PrintUsage();
                return 1;
            }
        }

        i++;
    } //while


    return 0;

}

int main(int argc, char *argv[])
{

    if (argc <= 1)
    {
        PrintUsage();
        return 1;
    }
    if(parse_args(argc, argv)!=0) return 1;



    if(g_is_pinyin)
    {
        pinyin_to_phoneme(g_input);
    }
    else if(!g_is_phonetic)
    {
        text_to_text(g_input,g_input);
        text_to_phoneme(g_input);
    }
    else
    {
        //already phoneme. skip
    }

    if(!g_is_raw)
    {
        phoneme_adjust();
    }

    phoneme_to_wave();

    if(g_wavfilename!=0)
    {
        ///write to wav
        write_to_wav(g_wavfilename);
    }
    else
    {
        play_snd();
    }



	
	return 0;
}


