#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "Header.h"
#include "Constants.h"

void cards_to_string(int* player_cards, char* player_cards_string, int size)
{
	int value = 0;

	for (int i = 0; i < size; i++)
	{
		char temp[MINLENGTH] = "";
		value = *(player_cards + i);
		define_card_type(temp, value);
		strcat(player_cards_string, temp);
	}
}

void define_card_type(char* card_name, int value)
{
	// ��Ʈ
	if (value < 200)
	{
		strcat(card_name, "��Ʈ");
	}
	// ���̾Ƹ��
	else if (value < 300)
	{
		strcat(card_name, "���̾Ƹ��");
	}
	// �����̵�
	else if (value < 400)
	{
		strcat(card_name, "�����̵�");
	}
	// Ŭ�ι�
	else if (value < 500)
	{
		strcat(card_name, "Ŭ�ι�");
	}

	// 1, ... , 10, J, Q, K ����
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
	else // 10���� ���� ���
	{
		// 1���� 10���� ������ ���� ���ڿ��� ����
		char temp[4];
		sprintf(temp, "%d ", num);
		strcat(card_name, temp);
	}
}