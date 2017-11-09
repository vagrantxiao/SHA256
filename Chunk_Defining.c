#include <stdio.h>
#include <stdlib.h>

#include "project.h"

#define CHUNK_LENGTH 4096

void Chunk_Defining(unsigned char * Input, unsigned char * Output)
{
    for (int i; i < CHUNK_LENGTH; i++)
    {
        Output[i] = Input[i];
    }
    return;
}
