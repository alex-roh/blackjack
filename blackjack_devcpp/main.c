
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "header.h"
#include "constants.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {

	set_players();
	initialize_cards(cards_tray);

	// ���� �ݺ� ����
	while (1)
	{
		// ������ ���� ����
		game_logic_per_round();
		initialize_players_after_round();

		// ������ �������ǿ� �����ϰ� �� ���
		if (check_if_game_end() == GAMEEND)
		{
			return 0;
		}
	}

	return 0;
	
}

// �� ���尡 ������ �� �������ǿ� �����ϴ����� �˻�
int check_if_game_end()
{
	// 1. Ʈ���̿� ī�尡 ������ ����
	if (distribution_cursor == N_TOTAL_CARDS)
	{
		printf("\n--------------------------\n"); 
		printf("   -> Ʈ���̿� ī�尡 �� �̻� �����Ƿ� ������ �����մϴ�.\n");
		printf("   --> ���ڴ� %s�Դϴ�.", players[get_winner()].name);
		return GAMEEND;
	}

	// 2. �÷��̾� �� ���� �ݾ��� 0�� �� ����� ������ ����
	int i;
	for (i = 0; i < player_number; i++)
	{
		if (players[i].dollars <= 0)
		{
			printf("\n--------------------------\n\n");
			printf("   -> %s���� �Ļ��Ͽ����Ƿ� ������ �����մϴ�.\n", players[i].name);
			printf("   --> ���ڴ� %s�Դϴ�.\n\n", players[get_winner()].name); 
			return GAMEEND;
		}
	}

	return 0;
}

// ������ ���ڸ� �˻��ϰ� �� ��ȣ�� ����
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
