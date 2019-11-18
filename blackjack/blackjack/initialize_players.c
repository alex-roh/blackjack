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
		printf("\n\n\n블랙잭을 플레이할 플레이어의 수를 입력하십시오 (최소 2명, 최대 5명) : ");
		scanf_s("%d", player_number);
	} while (over_under_flow_detection(5, 2, *player_number));

	// 플레이어 구조체 배열에 담긴 플레이어들을 초기화
	for(int i = 0; i < *player_number; i++)
	{
		if (i == 0)
		{
			strcat(players[i].name, "당신");
		}
		else
		{
			sprintf(players[i].name, "플레이어%d", i);
		}

		players[i].dollars = 50;        // 보유 금액을 50 달러로 초기화
		players[i].buffer_cursor = 0;   // 버퍼 커서를 0으로 초기화
		players[i].is_alive = 1;        // 생존 여부를 1으로 초기화
		players[i].sum = 0;             // 카드 합을 0으로 초기화
	}

	// 딜러 초기화
	strcat(dealer.name, "딜러");
	dealer.buffer_cursor = 0;
	dealer.dollars = 50;
	dealer.is_alive = 1;

}