#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "header.h"

#define N_CARDS 52
#define N_TYPE 4
#define N_CARDS_PER_TYPE 13

int player_number = 0;

int main() 
{
	//int cards[52];
	//initialize_cards(cards);
	//swap_cards(cards, N_CARDS);
	//print_array(cards, N_CARDS);

	char* temp = malloc(sizeof(char));
	char* type_as_charptr;
	char* specified_type = "하트";

	check_card_num_check(10, temp, type_as_charptr, specified_type);

	return 0;
}

void get_player_number(int* player_number) 
{
	printf("블랙잭을 플레이할 플레이어의 수를 입력하십시오: ");
	scanf_s("%d", player_number);
}

void initialize_cards(int* cards)
{
	int i, j, index = 0, determine_type;
	
	// 100-112 : 하트
	// 200-212 : 다이아몬드
	// 300-312 : 스페이드
	// 400-412 : 클로버
	for (i = 1; i <= N_TYPE; i++) 
	{

		determine_type = i * 100;

		for (j = 0; j < N_CARDS_PER_TYPE; j++) 
		{
			*(cards + index) = determine_type + j;
			index++;
		}
	}
}

void swap_cards(int* cards, int size) 
{
	
	int i;
	srand(time(NULL));
	
	for (i = 0; i < N_CARDS; i++) 
	{
		int rand_index = rand() % (N_CARDS - i) + i;
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
		printf("%d\n", *(arr + i));
	}
}

char* check_type(int value, int size)
{
	int num = value % 100;
	char* temp = malloc(sizeof(char));
	char* type_as_charptr;

	// 하트
	if (value < 200)
	{
		char* specified_type = "하트";
		free(temp); // 동적 메모리 해제

	}
	// 다이아몬드
	else if (value < 300)
	{

	}
	// 스페이드
	else if (value < 400)
	{
		if (num > 10)
		{

		}
	}
	// 클로버
	else if (value < 500)
	{
		if (num > 10)
		{

		}
	}
}

char* check_card_num_check(int num, char* temp, char* type_as_charptr, char* specified_type)
{
	if (num > 10)
	{
		if (num == 11) {
			temp = 'J';
		}
		else if (num == 12) {
			temp = 'Q';
		}
		else if (num == 13) {
			temp = 'K';
		}
	}

	sprintf(temp, "%d", num);       // 정수를 문자열으로 변환
	char* ptr = strcat_s(specified_type, temp);  // type_as_char에 temp를 이어붙임

	printf_s("%s\n", type_as_charptr);

	return type_as_charptr;
}