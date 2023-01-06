#include <stdio.h>
#include "prints.h"

int g_debug;

void PrintUsage()
{
    printf("usage: non-sam [options] Word1 Word2 ....\n");
    printf("options\n");
    printf("	-m 		enters phonetic mode. (see below)\n");
    printf("	-p		enter chinese pinyin mode.\n");
    printf("	-t number		set pitch value (default=64)\n");
    printf("	-s number		set speed value (default=72)\n");
    printf("	-g number		set throat value (f1 value. default=128)\n");
    printf("	-f number		set mouth value (f0 value. default=128)\n");
    printf("	-w filename		output to wav instead of libsdl\n");
    printf("	-i  			special treatment of pitch(sing mode)\n");
    printf("	-d  			print additional debug messages\n");
    printf("\n");

}
