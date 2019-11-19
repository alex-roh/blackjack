#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "Header.h"
#include "Constants.h"

void initialize_cards(int* cards)
{
	// 카드 분배에 필요한 커서를 0으로 초기화
	distribution_cursor = 0;

	int i, j, index = 0, determine_type;

	// (11 = 'J', 12 = 'Q', 13 = 'K' -> 모두 10으로 해석)
	// 101-113 : 하트
	// 201-213 : 다이아몬드
	// 301-313 : 스페이드
	// 401-413 : 클로버

	int count = N_SET;

	while (count > 0) {
		for (i = 1; i <= N_TYPE; i++)
		{
			determine_type = i * 100;

			for (j = 1; j <= N_CARDS_PER_TYPE; j++)
			{
				*(cards + index) = determine_type + j;
				index++;
			}
		}
		count--;
	}

	randomize_cards(cards);
	printf("\n----> %d개 카드 세트를 섞어서 트레이에 넣었습니다.\n", N_SET);
}

void randomize_cards(int* cards)
{
	srand(time(NULL));
	int i;

	for (i = 0; i < N_TOTAL_CARDS; i++)
	{
		int rand_index = rand() % (N_TOTAL_CARDS - i) + i;
		swap(cards + i, cards + rand_index);
	}
}

void swap(int* x_ptr, int* y_ptr)
{
	int temp = *(x_ptr);
	*(x_ptr) = *(y_ptr);
	*(y_ptr) = temp;
}
