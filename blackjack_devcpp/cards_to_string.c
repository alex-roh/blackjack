#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "header.h"
#include "constants.h"

// 전달받은 int 카드 배열으로부터 카드 타입을 해석해서 문자열을 반환하는 함수 
void cards_to_string(int* player_cards, char* player_cards_string, int size, int dealer_hide_flag)
{
	int value = 0;
	int i;
	for (i = 0; i < size; i++) // 전달받은 int 카드 배열의 개수만큼 반복 
	{
		char temp[MINLENGTH] = ""; // 임시 배열 

		if (i == 0 && dealer_hide_flag == DEALER)
		{
			strcat(player_cards_string, "(알수없음) "); // 딜러의 첫 카드는 '알수없음'으로 세팅 
			continue;
		}

		value = *(player_cards + i); // 카드 타입을 알 수 있는 카드 번호를 반환받음 
		define_card_type(temp, value); // 카드 번호를 다른 함수로 넘김 
		strcat(player_cards_string, temp);
	}
}

// 카드 타입을 알아내는 함수 
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

	// A, ... , 10, J, Q, K 결정
	int num = value % 100;
	
	if(num == 1)
	{
		char temp[] = "A ";
		strcat(card_name, temp);
	}	
	else if (num > 10)
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
		// 2부터 10까지 임의의 값을 문자열로 만듦
		char temp[4];
		sprintf(temp, "%d ", num);
		strcat(card_name, temp);
	}
}
