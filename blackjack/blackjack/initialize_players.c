#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "Constants.h"
#include "Players.h"

int over_under_flow_detection(int max_num, int min_num, int current_num);

void set_players(int* player_number)
{
	do {
		printf("\n\n\n������ �÷����� �÷��̾��� ���� �Է��Ͻʽÿ� (�ּ� 2��, �ִ� 5��) : ");
		scanf_s("%d", player_number);
	} while (over_under_flow_detection(5, 2, *player_number));

	// �÷��̾� ����ü �迭�� ��� �÷��̾���� �ʱ�ȭ
	for(int i = 0; i < *player_number; i++)
	{
		if (i == 0)
		{
			strcat(players[i].name, "���");
		}
		else
		{
			sprintf(players[i].name, "�÷��̾�%d", i);
		}

		players[i].dollars = 50;        // ���� �ݾ��� 50 �޷��� �ʱ�ȭ
		players[i].buffer_cursor = 0;   // ���� Ŀ���� 0���� �ʱ�ȭ
		players[i].is_alive = 1;        // ���� ���θ� 1���� �ʱ�ȭ
		players[i].sum = 0;             // ī�� ���� 0���� �ʱ�ȭ
	}

	// ���� �ʱ�ȭ
	strcat(dealer.name, "����");
	dealer.buffer_cursor = 0;
	dealer.dollars = 50;
	dealer.is_alive = 1;

}