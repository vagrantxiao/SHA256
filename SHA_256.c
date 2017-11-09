#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "project.h"


static const uint32_t k[] =
{
    0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5,
    0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
    0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3,
    0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
    0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC,
    0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
    0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7,
    0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
    0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13,
    0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
    0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3,
    0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
    0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5,
    0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
    0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208,
    0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2,
};

uint32_t hash_initials[] =
{
    0x6a09e667, 
    0xbb67ae85,
    0x3c6ef372,
    0xa54ff53a,
    0x510e527f,
    0x9b05688c,
    0x1f83d9ab,
    0x5be0cd19,
};

uint32_t hash[8];

static void Appending_Word(unsigned char * Input, int Input_Size, unsigned char * Appending_message,  unsigned char * Output)
{
	int i;
    for (i = 0; i < Input_Size; i++)
    {
        Output[i] = Input[i];
    }
    for (; Appending_message + i == NULL; i++)
    {
        Output[i] = Appending_message[i];
    }
    return;
}


static uint64_t Calculating_Chunk_Length(unsigned char * Input)
{
	uint64_t length;
    for (length = 0; *(Input + length) != '\0'; length++);
    printf("length=%x\n", length);
    return length;
}

static int Initialize_Chunk(unsigned char * Input, unsigned char * Output)
{

    uint64_t Original_Chunk_Length = Calculating_Chunk_Length(Input);
    unsigned char *Length_Data;
    int i;
    for (i = 0; i < Original_Chunk_Length; i++)
    {
        Output[i] = Input[i];
    }
    Output[i]=128;
    i++;
    while(i % 64 != 56){
    	Output[i] = 0;
    	i++;
    }
    Original_Chunk_Length = Original_Chunk_Length << 3;
    for(int j=0; j<8; j++){
    	Output[i] = (Original_Chunk_Length >> (8-j-1) * 8) & 0xff;
    	i++;
    }
    return i >> 6;
}

static void SHA_256_Hash_init(){
	hash[0] = hash_initials[0];
	hash[1] = hash_initials[1];
	hash[2] = hash_initials[2];
	hash[3] = hash_initials[3];
	hash[4] = hash_initials[4];
	hash[5] = hash_initials[5];
	hash[6] = hash_initials[6];
	hash[7] = hash_initials[7];
}


static void SHA_256_Hash(unsigned char * Input, uint32_t * Output)
{
	printf("input[0]=%c\n", Input[0]);
	uint32_t W[64];
	uint32_t a = hash[0];
	uint32_t b = hash[1];
	uint32_t c = hash[2];
	uint32_t d = hash[3];
	uint32_t e = hash[4];
	uint32_t f = hash[5];
	uint32_t g = hash[6];
	uint32_t h = hash[7];
    uint32_t temp1, temp2;
	int i, j;
	for (i = 0, j = 0; i < 16; ++i, j += 4)
	{
		W[i] = ((uint32_t) Input[j] << 24) | ((uint32_t) Input[j + 1] << 16 )| ((uint32_t) Input[j + 2] << 8 )| ((uint32_t) Input[j + 3]);
	}
	for (; i < 64; i++)
	{
		W[i] =  W[i - 16] + SIG0(W[i - 15]) + W[i - 7] + SIG1(W[i - 2]);
	}

	for (i = 0; i < 64; i++)
	{
		temp1 = h + EP1(e) + CH(e, f, g) + k[i] + W[i];
		temp2 = EP0(a) + MAJ(a, b, c);
		h = g;
		g = f;
		f = e;
		e = d + temp1;
		d = c;
		c = b;
		b = a;
		a = temp1 + temp2;
	}
	hash[0] = (hash[0] + a) & 0xFFFFFFFF;
	hash[1] = (hash[1] + b) & 0xFFFFFFFF;
	hash[2] = (hash[2] + c) & 0xFFFFFFFF;
	hash[3] = (hash[3] + d) & 0xFFFFFFFF;
	hash[4] = (hash[4] + e) & 0xFFFFFFFF;
	hash[5] = (hash[5] + f) & 0xFFFFFFFF;
	hash[6] = (hash[6] + g) & 0xFFFFFFFF;
	hash[7] = (hash[7] + h) & 0xFFFFFFFF;
	for (i = 0; i < 8; i++)
	{
		Output[i] = hash[i];
	}
	return;
}

void SHA_256(unsigned char * Input, uint32_t * Output)
{
	unsigned char * Ini_Chunk = (unsigned char *) malloc(CHUNK_MAXIMUM_LENGTH * sizeof(unsigned char));
	int Chunk_Quantity = Initialize_Chunk(Input, Ini_Chunk), i;
	SHA_256_Hash_init();
	for (i = 0; i < Chunk_Quantity; i++)
	{
		SHA_256_Hash(Ini_Chunk + 64 * i, Output);
		for (int j = 0; j < 8; j++)
		{
			//printf("%08x\t", Output[i * 8 + j]);
		}
		printf("\n");
	}
	free(Ini_Chunk);
    return;
}
