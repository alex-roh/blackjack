#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "header.h"

#define N_SET 4
#define N_CARDS_PER_SET 52
#define N_TOTAL_CARDS 208
#define N_TYPE 4
#define N_CARDS_PER_TYPE 13
#define MAXLENGTH 100
#define MINLENGTH 30

int player_number = 0;

int main()
{
	int card_tray[5] = { 112, 203, 401, 311, 110 };
	printf("%s\n", get_player_cards(card_tray, 5));

	return 0;
}

char* get_player_cards(int* player_cards, int size)
{
	char player_cards_string[MAXLENGTH] = "";

	for (int i = 0; i < size; i++)
	{
		strcat(player_cards_string, get_card_type(*(player_cards + i)));
	}

	return player_cards_string;
}

void get_player_number(int* player_number) 
{
	printf("블랙잭을 플레이할 플레이어의 수를 입력하십시오: ");
	scanf_s("%d", player_number);
}

void initialize_cards(int* cards)
{
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

void print_array(int* arr, int size) 
{
	int i;

	for (i = 0; i < size; i++)
	{
		printf("%d ", *(arr + i));
	}
	printf("\n");
}

char* get_card_type(int value)
{
	char card_name[MINLENGTH] = "";
	define_card_type(card_name, value, value % 100);

	return card_name;
}

void define_card_type(char* card_name, int value)
{
	// 하트
	if (value < 200)
	{
		strcat(card_name, "하트");
	}
	// 다이아몬드
	else if (value < 300)
	{
		strcat(card_name, "다이아몬드");
	}
	// 스페이드
	else if (value < 400)
	{
		strcat(card_name, "스페이드");
	}
	// 클로버
	else if (value < 500)
	{
		strcat(card_name, "클로버");
	}

	// 1, ... , 10, J, Q, K 결정
	int num = value % 100;
	if (num > 10)
	{
		if (num == 11) 
		{
			char temp[] = "J ";
			strcat(card_name, temp);
		}
		else if (num == 12) 
		{
			char temp[] = "Q ";
			strcat(card_name, temp);
		}
		else if (num == 13) 
		{
			char temp[] = "K ";
			strcat(card_name, temp);
		}
	}
	else // 10보다 작을 경우
	{
		// 1부터 10까지 임의의 값을 문자열로 만듦
		char temp[4];
		sprintf(temp, "%d ", num);
		strcat(card_name, temp);
	}
}