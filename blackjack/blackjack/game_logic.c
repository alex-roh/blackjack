#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "Header.h"
#include "Constants.h"
#include "Players.h"

void print_array(int* arr, int size);

void game_logic_per_round()
{
	static int round = 1;
	int players_bet[N_MAXPLAYERS] = { 0 };

	printf("\n--------------------------\n");
	printf("---------라운드 %d---------\n", round);
	printf("--------------------------\n");
	printf("\n");
	printf("---------초기 상태--------\n");

	// 플레이어의 베팅
	do {
		printf("\n  -> 이번 라운드에 돈을 얼마나 배팅하시겠습니까? (보유 금액: %d$): ", players[0].dollars);
		scanf_s("%d", &players_bet[USER]);
	} while (over_under_flow_detection(players[USER].dollars, 1, players_bet[USER]));

	// 나머지 플레이어들의 베팅
	set_players_bet(players_bet);

	// 라운드 카드 분배
	printf("\n---------카드 분배--------\n\n");
	card_offering();

	// 유저의 턴 및 다른 플레이어들의 턴
	int result = 0;
	printf("\n---------게임 시작--------\n");
	
	for (int i = 0; i < player_number; i++)
	{
		select_go_stop(i, &result);

		// 블랙잭이 나온 경우
		if (result == BLACKJACK)
		{
			break; // 루프 탈출
		}
	}

	// 턴 중에 블랙잭이 나오지 않은 경우
	if (result != BLACKJACK)
	{
		select_go_stop(DEALER, &result); // 딜러의 턴
	}
		
	// 이번 라운드 결과 정산
	printf("\n--------------------------\n");
	printf("-------라운드 %d 결과------\n", round);
	printf("--------------------------\n");

	end_round(result, players_bet);

	for (int i = 0; i < player_number; i++)
	{
		printf("  --> %s의 결과 : ", players[i].name);
		if (players[i].is_alive == 1)
		{
			printf("승리 ");
		}
		else {
			printf("패배 ");
		}
		printf("(총합: %d)  -> 남은 금액: %d\n", players[i].sum, players[i].dollars);
	}
	
	round++;
}

// 플레이어들의 go/stop 선택 시마다 블랙잭을 판단하는 함수
void select_go_stop(int i, int* result)
{
	if (i == USER) // 유저의 경우
	{
		*result = selection(&players[USER], USER);
	}
	else if (i == DEALER) // 딜러의 경우
	{
		*result = selection(&dealer, 1); // 이제 첫 번째 카드를 숨기지 않아도 되므로
											  // 인자를 'DEALER'가 아닌 'PLAYER'로 넣음
	}
	else // 다른 플레이어들의 경우
	{
		*result = selection(&players[i], i);
	}
}

// 플레이어들의 구체적인 go/stop 선택을 정의한 함수
int selection(player* player_ptr, int i)
{
	int stop_flag = 0;

	printf("\n  -> %s의 턴입니다.\n", player_ptr->name);

	while (stop_flag == 0)
	{
		// 현재 카드 상태를 출력하고, 총합을 업데이트
		char temp[MAXLENGTH] = "";
		cards_to_string(player_ptr->buffer, temp, player_ptr->buffer_cursor, i);
		update_sum(player_ptr);
		printf("  --> %s의 카드: %s (총합: %d)\n", player_ptr->name, temp, player_ptr->sum);

		// 블랙잭 혹은 패배 여부를 판단
		int is_blackjack = check_blackjack(player_ptr);
		if (is_blackjack == DEAD)
		{
			printf("   -> 총합이 21을 넘었으므로 졌습니다.\n");
			player_ptr->is_alive = 0; // 생존 여부를 0으로 세팅
			stop_flag = 1;
			break;
		}
		else if (is_blackjack == BLACKJACK)
		{
			printf("   -> 블랙잭입니다! 이번 라운드에서 승리합니다.\n");
			printf("\n--------------------------\n");
			return BLACKJACK;
		}

		// 현재 턴이 유저일 경우
		if (i == USER)
		{
			// 유저의 선택을 받음
			printf("\n  :: 어떻게 하시겠습니까? (0 - 새로운 카드를 받는다, 그 외 - 턴을 넘긴다)\n");
			scanf_s("%d", &stop_flag);

			if (stop_flag == 0)
			{
				// 트레이로부터 새로 카드 한 장을 받아옴
				distribute_cards(USER, USER);
			}
		}
		else // 현재 턴이 유저 이외의 다른 플레이어일 경우
		{
			// 총합이 17 이상이면 stop
			if (player_ptr->sum >= 17)
			{
				// stop
				stop_flag = 1;
				printf("  --> 턴을 마칩니다.\n");
			}
			// 총합이 17 미만이면 go
			else
			{
				// 트레이로부터 새로 카드 한 장을 받아옴
				if (player_ptr == &dealer) // 딜러의 경우
				{
					distribute_cards(DEALER, DEALER);
				}
				else 
				{
					distribute_cards(PLAYER, i);
				}
				printf("  --> 트레이로부터 새로운 카드를 받아옵니다.\n");
			}
		}
	}

	printf("\n--------------------------\n");

	return 0;
}

// 라운드 카드 분배
void card_offering()
{
	// 딜러에게 분배
	distribute_cards(DEALER, DEALER); // (dealer_flag, index)
	distribute_cards(DEALER, DEALER);

	// 다른 플레이어들에게 분배
	for (int i = 0; i < player_number; i++)
	{
		// 카드 두 장을 분배
		distribute_cards(0, i);
		distribute_cards(0, i);
	}

	// 딜러의 카드 출력
	print_cards(DEALER, DEALER); // (dealer_flag, index)

	// 다른 플레이어들의 카드 출력
	for (int i = 0; i < player_number; i++)
	{
		print_cards(0, i);
	}
}

// 현재 가지고 있는 카드의 정보를 문자열로 출력
void print_cards(int dealer_first_turn_flag, int i)
{
	// 출력에 사용할 문자 배열
	char temp[MINLENGTH] = "";

	// 딜러의 경우, 첫번째 카드를 X로 출력
	if (dealer_first_turn_flag == DEALER)
	{
		cards_to_string(dealer.buffer, temp, dealer.buffer_cursor, DEALER);
		printf("  --> 딜러의 카드: \t%s\n", temp);
		return;
	}
	else
	{
		// 다른 플레이어들의 경우, 그대로 출력
		cards_to_string(players[i].buffer, temp, players[i].buffer_cursor, PLAYER);
		if (i == USER)
		{
			printf("  --> %s의 카드: \t%s\n", players[i].name, temp); // 유저의 경우 indenting
		}
		else
		{
			printf("  --> %s의 카드: %s\n", players[i].name, temp);
		}
	}
}

// 딜러 혹은 플레이어 1명에게 카드를 분배
void distribute_cards(int dealer_turn_flag, int i)
{
	// 딜러의 턴인 경우
	if (dealer_turn_flag == DEALER)
	{
		// 딜러의 버퍼에 트레이에서 카드 하나를 꺼내 넣고, 커서를 증가시킴
		*(dealer.buffer + dealer.buffer_cursor++) = *(cards_tray + distribution_cursor++);
		return;
	}

	// 다른 플레이어에게 카드 1장을 분배
	*(players[i].buffer + players[i].buffer_cursor++) = *(cards_tray + distribution_cursor++);

}

// 다른 플레이어들의 베팅
void set_players_bet(int* players_bet)
{
	srand(time(NULL));

	// 유저가 입력한 플레이어의 수만큼 반복
	for (int i = 0; i < player_number; i++)
	{
		// 유저의 차례인 경우 반복문을 skip
		if (i == USER)
		{
			printf("\n  --> %s의 베팅 금액:      %d (보유 금액: %d)\n",
				players[i].name, *(players_bet + i), players[i].dollars - *(players_bet + i));
			continue;
		}

		// 다른 플레이어의 차례인 경우
		*(players_bet + i) = (rand() % (N_MAXBET - N_MINBET + 1)) + N_MINBET;
		
		// 임의의 플레이어가 베팅하는 금액이 현재 보유 금액을 초과할 경우
		if (players[i].dollars < *(players_bet + i)) {
			// 보유 금액 전체를 베팅액으로 사용
			*(players_bet + i) = players[i].dollars;
		}

		printf("  --> %s의 베팅 금액: %d (보유 금액: %d)\n",
			players[i].name, *(players_bet + i), players[i].dollars - *(players_bet + i));
	}
}

// 라운드를 끝내고 결과를 정산함
void end_round(int is_blackjack, int* players_bet)
{
	// 플레이어 중 한 명이 블랙잭이 된 경우
	if (is_blackjack == BLACKJACK)
	{
		// 누가 블랙잭인지 확인
		int winner_num = who_is_blackjack();

		if (winner_num == DEALER)  // 딜러가 블랙잭인 경우
		{
			printf("\n --> 딜러가 블랙잭입니다!\n");
			// 모든 플레이어들이 패배하고, 자신이 베팅한 금액만큼을 잃음
			for (int i = 0; i < player_number; i++)
			{
				players[i].dollars -= *(players_bet + i);
				players[i].is_alive = 0;
			}
		}
		else { // 플레이어들 중 한 명이 블랙잭인 경우

			int bet_total = 0;

			printf("\n --> 블랙잭이 나왔습니다! 블랙잭은 %s입니다.\n\n", players[winner_num].name);

			// 베팅된 금액의 합을 계산
			for (int i = 0; i < player_number; i++)
			{
				bet_total += *(players_bet + i);
				if (i != winner_num)
				{
					// 승리자 이외의 모든 사람들은 자신이 베팅한 금액만큼을 잃음
					players[i].dollars -= *(players_bet + i);
					players[i].is_alive = 0;
				}
			}
			
			// 베팅된 금액 모두를 승리자에게 전달
			players[winner_num].dollars += bet_total;
		}

	}
	// 일반적인 종료 상황의 경우
	else {

		printf("\n  -> 딜러의 총합: %d\n\n", dealer.sum);

		for (int i = 0; i < player_number; i++)
		{
			// 총합이 21을 넘어간 경우 무조건 패배
			if (players[i].is_alive == 0)
			{
				// 베팅한 금액을 잃음
				players[i].dollars -= *(players_bet + i);
			}
			// 총합이 21을 넘지 않으면서 딜러보다 총합이 같거나 큰 경우 승리
			else if (players[i].is_alive == 1 && players[i].sum >= dealer.sum)
			{
				// 베팅한 금액을 얻음
				players[i].dollars += *(players_bet + i);
			}
			// 총합이 21을 넘지 않으면서 딜러가 21을 넘은 경우 승리
			else if (players[i].is_alive == 1 && dealer.sum > 21)
			{
				// 베팅한 금액을 얻음
				players[i].dollars += *(players_bet + i);
			}
		}
	}
}

int who_is_blackjack()
{
	// 딜러가 블랙잭일 경우
	if (dealer.sum == BLACKJACK)
	{
		return DEALER;
	}

	// 플레이어 중에서 블랙잭을 확인
	for (int i = 0; i < player_number; i++)
	{
		if (players[i].sum == BLACKJACK)
		{
			return i; // 플레이어 번호를 리턴
		}
	}
}

// 버퍼에 담긴 카드의 총합을 계산하여 업데이트
void update_sum(player* player_ptr)
{
	int sum = 0;
	int	size = player_ptr->buffer_cursor;

	for (int j = 0; j < size; j++)
	{
		// 카드 번호에 mod 100한 값을 카드값으로 지정
		int current_card = *(player_ptr->buffer + j) % 100;

		if (current_card > 10) // 10을 넘어간 경우, J, Q, K 중 하나라는 뜻이므로 10으로 세팅
		{
			current_card = 10;
		}

		sum += current_card;
	}

	player_ptr->sum = sum;
}

// 블랙잭 여부를 체크
int check_blackjack(player* player_ptr)
{
	if (player_ptr->sum > BLACKJACK)
	{
		return DEAD;
	}
	else if (player_ptr->sum == BLACKJACK)
	{
		return BLACKJACK;
	}
}

// 오버플로우와 언더플로우 감지
int over_under_flow_detection(int max_num, int min_num, int current_num)
{
	// 오버플로우
	if (current_num > max_num)
	{
		return 1;
	}
	// 언더플로우
	if (current_num < min_num)
	{
		return -1;
	}
	else {
		return 0;
	}
}