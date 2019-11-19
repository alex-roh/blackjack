
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "header.h"
#include "constants.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {

	set_players();
	initialize_cards(cards_tray);

	// 라운드 반복 루프
	while (1)
	{
		// 게임의 메인 로직
		game_logic_per_round();
		initialize_players_after_round();

		// 게임이 종료조건에 부합하게 된 경우
		if (check_if_game_end() == GAMEEND)
		{
			return 0;
		}
	}

	return 0;
	
}

// 매 라운드가 끝났을 때 종료조건에 부합하는지를 검사
int check_if_game_end()
{
	// 1. 트레이에 카드가 없으면 종료
	if (distribution_cursor == N_TOTAL_CARDS)
	{
		printf("\n--------------------------\n"); 
		printf("   -> 트레이에 카드가 더 이상 없으므로 게임을 종료합니다.\n");
		printf("   --> 승자는 %s입니다.", players[get_winner()].name);
		return GAMEEND;
	}

	// 2. 플레이어 중 보유 금액이 0이 된 사람이 있으면 종료
	int i;
	for (i = 0; i < player_number; i++)
	{
		if (players[i].dollars <= 0)
		{
			printf("\n--------------------------\n\n");
			printf("   -> %s께서 파산하였으므로 게임을 종료합니다.\n", players[i].name);
			printf("   --> 승자는 %s입니다.\n\n", players[get_winner()].name); 
			return GAMEEND;
		}
	}

	return 0;
}

// 게임의 승자를 검사하고 그 번호를 리턴
int get_winner()
{
	int largest = 0;
	int winner = 0;

	int i;
	for (i = 0; i < player_number; i++)
	{
		if (largest < players[i].dollars)
		{
			largest = players[i].dollars;
			winner = i;
		}
	}

	return winner;
}
