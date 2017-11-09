#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "project.h"

int main()
{
	//unsigned char *text1 = "abcdefghabcdefghqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdefabcdefghijklmnopqrstuvwxyzabcdef";
	unsigned char *text1 = "1222222";
	uint16_t * Output =(uint32_t *) malloc(8 * 8 * sizeof(uint32_t));;
	uint32_t * hash1 = (uint32_t *) malloc(8 * 8 * sizeof(uint32_t));
    int i;
    printf(" sizeof(uint32_t)=%x\n",  sizeof(uint32_t));
    SHA_256(text1, hash1);
    printf("the hash1 is:\n");
    for (i = 0; i < 64; i++)
    {
        printf("%08x\t", hash1[i]);
    }
    printf("\nEnd of hash1\n");

    LZW(text1, Output);
    free(hash1);
    return 0;
}
