#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Header.h"
#include "Constants.h"

int main()
{
	set_players(&player_number);
	initialize_cards(cards_tray);
	game_logic_per_round();

	return 0;
}

void print_array(int* arr, int size) 
{
	int i;

	for (i = 0; i < size; i++)
	{
		printf("%d ", *(arr + i));
	}
	printf("\n");
}