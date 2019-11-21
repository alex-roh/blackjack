
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "players.h"

extern int player_number;
int over_under_flow_detection(int max_num, int min_num, int current_num);

void set_players(int round_or_set)
{
	// ���α׷��� ���� ���۵Ǿ��� ���� 
	if(round_or_set == SET)
	{
		do {
			printf("\n\n������ �÷����� �÷��̾��� ���� �Է��Ͻʽÿ� (�ּ� 2��, �ִ� 5��) : ");
			scanf_s("%d", &player_number);
		} while (over_under_flow_detection(5, 2, player_number));
	}

	// �÷��̾� ����ü �迭�� ��� �÷��̾���� �ʱ�ȭ
	int i;
	for(i = 0; i < player_number; i++)
	{		
		// ���α׷��� ���� ���۵Ǿ��� ���� 
		if(round_or_set == SET)
		{
			if (i == 0)
			{
				strcat(players[i].name, "���");
			}
			else
			{
				sprintf(players[i].name, "�÷��̾�%d", i);
			}
			
			players[i].dollars = 50;  // ���� �ݾ��� 50 �޷��� �ʱ�ȭ
		}
		
		// �÷��̾��� ���� �ʱ�ȭ
		int j;
		for (j = 0; j < BLACKJACK; j++)
		{
			*(players[i].buffer + j) = 0;
		}
		
		players[i].buffer_cursor = 0;   // ���� Ŀ���� 0���� �ʱ�ȭ
		players[i].is_alive = 1;        // ���� ���θ� 1���� �ʱ�ȭ
		players[i].sum = 0;             // ī�� ���� 0���� �ʱ�ȭ
	}

	// ������ ī�� ��, Ŀ��, ����, ���� ���θ� �ʱ�ȭ
	int j;
	for (j = 0; j < BLACKJACK; j++)
	{
		*(dealer.buffer + j) = 0;  // ���� ���� �ʱ�ȭ 
	}
	
	// ���α׷��� ���� ���۵Ǿ��� ���� 
	if(round_or_set == SET)
	{
		strcat(dealer.name, "����");	
		dealer.dollars = 50; 
	}
	dealer.sum = 0; 
	dealer.buffer_cursor = 0;
	dealer.dollars = 50;
	dealer.is_alive = 1;

}
