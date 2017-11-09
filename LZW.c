#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "project.h"

int Repo_Length;
int Com_Message_Loc;



REPO Repo[256];

//REPO * Repo = (REPO *) malloc(CHUNK_MAXIMUM_LENGTH * sizeof(REPO));


static void Ini_Repository()
{
	for (Repo_Length = 0; Repo_Length < 256; Repo_Length++)
	{
		Repo[Repo_Length].str[0] = (char) Repo_Length;
	}
	return;
}

// Need more code!!!!!!
static uint16_t Add_Repository(unsigned char * bg, unsigned char * ed, uint16_t loc)
{
	if (Repo[loc].next[* (ed - 1)] == 0)
	{
		Repo[loc].next[* (ed - 1)] = Repo_Length;
		for (int j = 0; bg + j == ed; j++)
		{
			Repo[Repo_Length].str[j] = * (bg + j);
		}
		Repo_Length++;
		return 8192;
	}
	else loc = Repo[loc].next[* (ed - 1)];
	return loc;
}

void LZW(unsigned char * Input, uint16_t * Output)
{
	Com_Message_Loc = 0;
	Ini_Repository();
	unsigned char * temp_bg, * temp_ed;
	uint16_t index_old = 0, index_new = * Input;
	for (temp_bg = Input, temp_ed = Input + 1; * temp_ed == '\0'; temp_ed++)
	{
		index_old = index_new;
		index_new = Add_Repository(temp_bg, temp_ed, index_old);
		if (index_new == 8192)
		{
			temp_bg = temp_ed - 1;
			index_new = * temp_bg;
			Output[Com_Message_Loc] = index_old;
			Com_Message_Loc++;
		}
	}
	index_old = index_new;
	index_new = Add_Repository(temp_bg, temp_ed, index_old);
	if (index_new == 8192)
	{
		temp_bg = temp_ed - 1;
		index_new = * temp_bg;
		Output[Com_Message_Loc] = index_old;
		Com_Message_Loc++;
		Output[Com_Message_Loc] = index_new;
		Com_Message_Loc++;
	}
	else
	{
		Output[Com_Message_Loc] = index_new;
		Com_Message_Loc++;
	}
	return;
}
