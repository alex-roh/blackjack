#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "header.h"
#include "constants.h"

// ���޹��� int ī�� �迭���κ��� ī�� Ÿ���� �ؼ��ؼ� ���ڿ��� ��ȯ�ϴ� �Լ� 
void cards_to_string(int* player_cards, char* player_cards_string, int size, int dealer_hide_flag)
{
	int value = 0;
	int i;
	for (i = 0; i < size; i++) // ���޹��� int ī�� �迭�� ������ŭ �ݺ� 
	{
		char temp[MINLENGTH] = ""; // �ӽ� �迭 

		if (i == 0 && dealer_hide_flag == DEALER)
		{
			strcat(player_cards_string, "(�˼�����) "); // ������ ù ī��� '�˼�����'���� ���� 
			continue;
		}

		value = *(player_cards + i); // ī�� Ÿ���� �� �� �ִ� ī�� ��ȣ�� ��ȯ���� 
		define_card_type(temp, value); // ī�� ��ȣ�� �ٸ� �Լ��� �ѱ� 
		strcat(player_cards_string, temp);
	}
}

// ī�� Ÿ���� �˾Ƴ��� �Լ� 
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

	// A, ... , 10, J, Q, K ����
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
	else // 10���� ���� ���
	{
		// 2���� 10���� ������ ���� ���ڿ��� ����
		char temp[4];
		sprintf(temp, "%d ", num);
		strcat(card_name, temp);
	}
}
