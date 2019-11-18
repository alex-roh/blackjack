#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Header.h"
#include "Constants.h"

int player_number = 0;
int cards_tray[N_TOTAL_CARDS];

int main()
{
	initialize_cards(cards_tray);
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