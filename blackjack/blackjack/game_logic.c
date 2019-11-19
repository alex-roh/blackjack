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
	printf("---------���� %d---------\n", round);
	printf("--------------------------\n");
	printf("\n");
	printf("---------�ʱ� ����--------\n");

	// �÷��̾��� ����
	do {
		printf("\n  -> �̹� ���忡 ���� �󸶳� �����Ͻðڽ��ϱ�? (���� �ݾ�: %d$): ", players[0].dollars);
		scanf_s("%d", &players_bet[USER]);
	} while (over_under_flow_detection(players[USER].dollars, 1, players_bet[USER]));

	// ������ �÷��̾���� ����
	set_players_bet(players_bet);

	// ���� ī�� �й�
	printf("\n---------ī�� �й�--------\n\n");
	card_offering();

	// ������ �� �� �ٸ� �÷��̾���� ��
	int result = 0;
	printf("\n---------���� ����--------\n");
	
	for (int i = 0; i < player_number; i++)
	{
		select_go_stop(i, &result);

		// ������ ���� ���
		if (result == BLACKJACK)
		{
			break; // ���� Ż��
		}
	}

	// �� �߿� ������ ������ ���� ���
	if (result != BLACKJACK)
	{
		select_go_stop(DEALER, &result); // ������ ��
	}
		
	// �̹� ���� ��� ����
	printf("\n--------------------------\n");
	printf("-------���� %d ���------\n", round);
	printf("--------------------------\n");

	end_round(result, players_bet);

	for (int i = 0; i < player_number; i++)
	{
		printf("  --> %s�� ��� : ", players[i].name);
		if (players[i].is_alive == 1)
		{
			printf("�¸� ");
		}
		else {
			printf("�й� ");
		}
		printf("(����: %d)  -> ���� �ݾ�: %d\n", players[i].sum, players[i].dollars);
	}
	
	round++;
}

// �÷��̾���� go/stop ���� �ø��� ������ �Ǵ��ϴ� �Լ�
void select_go_stop(int i, int* result)
{
	if (i == USER) // ������ ���
	{
		*result = selection(&players[USER], USER);
	}
	else if (i == DEALER) // ������ ���
	{
		*result = selection(&dealer, 1); // ���� ù ��° ī�带 ������ �ʾƵ� �ǹǷ�
											  // ���ڸ� 'DEALER'�� �ƴ� 'PLAYER'�� ����
	}
	else // �ٸ� �÷��̾���� ���
	{
		*result = selection(&players[i], i);
	}
}

// �÷��̾���� ��ü���� go/stop ������ ������ �Լ�
int selection(player* player_ptr, int i)
{
	int stop_flag = 0;

	printf("\n  -> %s�� ���Դϴ�.\n", player_ptr->name);

	while (stop_flag == 0)
	{
		// ���� ī�� ���¸� ����ϰ�, ������ ������Ʈ
		char temp[MAXLENGTH] = "";
		cards_to_string(player_ptr->buffer, temp, player_ptr->buffer_cursor, i);
		update_sum(player_ptr);
		printf("  --> %s�� ī��: %s (����: %d)\n", player_ptr->name, temp, player_ptr->sum);

		// ���� Ȥ�� �й� ���θ� �Ǵ�
		int is_blackjack = check_blackjack(player_ptr);
		if (is_blackjack == DEAD)
		{
			printf("   -> ������ 21�� �Ѿ����Ƿ� �����ϴ�.\n");
			player_ptr->is_alive = 0; // ���� ���θ� 0���� ����
			stop_flag = 1;
			break;
		}
		else if (is_blackjack == BLACKJACK)
		{
			printf("   -> �����Դϴ�! �̹� ���忡�� �¸��մϴ�.\n");
			printf("\n--------------------------\n");
			return BLACKJACK;
		}

		// ���� ���� ������ ���
		if (i == USER)
		{
			// ������ ������ ����
			printf("\n  :: ��� �Ͻðڽ��ϱ�? (0 - ���ο� ī�带 �޴´�, �� �� - ���� �ѱ��)\n");
			scanf_s("%d", &stop_flag);

			if (stop_flag == 0)
			{
				// Ʈ���̷κ��� ���� ī�� �� ���� �޾ƿ�
				distribute_cards(USER, USER);
			}
		}
		else // ���� ���� ���� �̿��� �ٸ� �÷��̾��� ���
		{
			// ������ 17 �̻��̸� stop
			if (player_ptr->sum >= 17)
			{
				// stop
				stop_flag = 1;
				printf("  --> ���� ��Ĩ�ϴ�.\n");
			}
			// ������ 17 �̸��̸� go
			else
			{
				// Ʈ���̷κ��� ���� ī�� �� ���� �޾ƿ�
				if (player_ptr == &dealer) // ������ ���
				{
					distribute_cards(DEALER, DEALER);
				}
				else 
				{
					distribute_cards(PLAYER, i);
				}
				printf("  --> Ʈ���̷κ��� ���ο� ī�带 �޾ƿɴϴ�.\n");
			}
		}
	}

	printf("\n--------------------------\n");

	return 0;
}

// ���� ī�� �й�
void card_offering()
{
	// �������� �й�
	distribute_cards(DEALER, DEALER); // (dealer_flag, index)
	distribute_cards(DEALER, DEALER);

	// �ٸ� �÷��̾�鿡�� �й�
	for (int i = 0; i < player_number; i++)
	{
		// ī�� �� ���� �й�
		distribute_cards(0, i);
		distribute_cards(0, i);
	}

	// ������ ī�� ���
	print_cards(DEALER, DEALER); // (dealer_flag, index)

	// �ٸ� �÷��̾���� ī�� ���
	for (int i = 0; i < player_number; i++)
	{
		print_cards(0, i);
	}
}

// ���� ������ �ִ� ī���� ������ ���ڿ��� ���
void print_cards(int dealer_first_turn_flag, int i)
{
	// ��¿� ����� ���� �迭
	char temp[MINLENGTH] = "";

	// ������ ���, ù��° ī�带 X�� ���
	if (dealer_first_turn_flag == DEALER)
	{
		cards_to_string(dealer.buffer, temp, dealer.buffer_cursor, DEALER);
		printf("  --> ������ ī��: \t%s\n", temp);
		return;
	}
	else
	{
		// �ٸ� �÷��̾���� ���, �״�� ���
		cards_to_string(players[i].buffer, temp, players[i].buffer_cursor, PLAYER);
		if (i == USER)
		{
			printf("  --> %s�� ī��: \t%s\n", players[i].name, temp); // ������ ��� indenting
		}
		else
		{
			printf("  --> %s�� ī��: %s\n", players[i].name, temp);
		}
	}
}

// ���� Ȥ�� �÷��̾� 1���� ī�带 �й�
void distribute_cards(int dealer_turn_flag, int i)
{
	// ������ ���� ���
	if (dealer_turn_flag == DEALER)
	{
		// ������ ���ۿ� Ʈ���̿��� ī�� �ϳ��� ���� �ְ�, Ŀ���� ������Ŵ
		*(dealer.buffer + dealer.buffer_cursor++) = *(cards_tray + distribution_cursor++);
		return;
	}

	// �ٸ� �÷��̾�� ī�� 1���� �й�
	*(players[i].buffer + players[i].buffer_cursor++) = *(cards_tray + distribution_cursor++);

}

// �ٸ� �÷��̾���� ����
void set_players_bet(int* players_bet)
{
	srand(time(NULL));

	// ������ �Է��� �÷��̾��� ����ŭ �ݺ�
	for (int i = 0; i < player_number; i++)
	{
		// ������ ������ ��� �ݺ����� skip
		if (i == USER)
		{
			printf("\n  --> %s�� ���� �ݾ�:      %d (���� �ݾ�: %d)\n",
				players[i].name, *(players_bet + i), players[i].dollars - *(players_bet + i));
			continue;
		}

		// �ٸ� �÷��̾��� ������ ���
		*(players_bet + i) = (rand() % (N_MAXBET - N_MINBET + 1)) + N_MINBET;
		
		// ������ �÷��̾ �����ϴ� �ݾ��� ���� ���� �ݾ��� �ʰ��� ���
		if (players[i].dollars < *(players_bet + i)) {
			// ���� �ݾ� ��ü�� ���þ����� ���
			*(players_bet + i) = players[i].dollars;
		}

		printf("  --> %s�� ���� �ݾ�: %d (���� �ݾ�: %d)\n",
			players[i].name, *(players_bet + i), players[i].dollars - *(players_bet + i));
	}
}

// ���带 ������ ����� ������
void end_round(int is_blackjack, int* players_bet)
{
	// �÷��̾� �� �� ���� ������ �� ���
	if (is_blackjack == BLACKJACK)
	{
		// ���� �������� Ȯ��
		int winner_num = who_is_blackjack();

		if (winner_num == DEALER)  // ������ ������ ���
		{
			printf("\n --> ������ �����Դϴ�!\n");
			// ��� �÷��̾���� �й��ϰ�, �ڽ��� ������ �ݾ׸�ŭ�� ����
			for (int i = 0; i < player_number; i++)
			{
				players[i].dollars -= *(players_bet + i);
				players[i].is_alive = 0;
			}
		}
		else { // �÷��̾�� �� �� ���� ������ ���

			int bet_total = 0;

			printf("\n --> ������ ���Խ��ϴ�! ������ %s�Դϴ�.\n\n", players[winner_num].name);

			// ���õ� �ݾ��� ���� ���
			for (int i = 0; i < player_number; i++)
			{
				bet_total += *(players_bet + i);
				if (i != winner_num)
				{
					// �¸��� �̿��� ��� ������� �ڽ��� ������ �ݾ׸�ŭ�� ����
					players[i].dollars -= *(players_bet + i);
					players[i].is_alive = 0;
				}
			}
			
			// ���õ� �ݾ� ��θ� �¸��ڿ��� ����
			players[winner_num].dollars += bet_total;
		}

	}
	// �Ϲ����� ���� ��Ȳ�� ���
	else {

		printf("\n  -> ������ ����: %d\n\n", dealer.sum);

		for (int i = 0; i < player_number; i++)
		{
			// ������ 21�� �Ѿ ��� ������ �й�
			if (players[i].is_alive == 0)
			{
				// ������ �ݾ��� ����
				players[i].dollars -= *(players_bet + i);
			}
			// ������ 21�� ���� �����鼭 �������� ������ ���ų� ū ��� �¸�
			else if (players[i].is_alive == 1 && players[i].sum >= dealer.sum)
			{
				// ������ �ݾ��� ����
				players[i].dollars += *(players_bet + i);
			}
			// ������ 21�� ���� �����鼭 ������ 21�� ���� ��� �¸�
			else if (players[i].is_alive == 1 && dealer.sum > 21)
			{
				// ������ �ݾ��� ����
				players[i].dollars += *(players_bet + i);
			}
		}
	}
}

int who_is_blackjack()
{
	// ������ ������ ���
	if (dealer.sum == BLACKJACK)
	{
		return DEALER;
	}

	// �÷��̾� �߿��� ������ Ȯ��
	for (int i = 0; i < player_number; i++)
	{
		if (players[i].sum == BLACKJACK)
		{
			return i; // �÷��̾� ��ȣ�� ����
		}
	}
}

// ���ۿ� ��� ī���� ������ ����Ͽ� ������Ʈ
void update_sum(player* player_ptr)
{
	int sum = 0;
	int	size = player_ptr->buffer_cursor;

	for (int j = 0; j < size; j++)
	{
		// ī�� ��ȣ�� mod 100�� ���� ī�尪���� ����
		int current_card = *(player_ptr->buffer + j) % 100;

		if (current_card > 10) // 10�� �Ѿ ���, J, Q, K �� �ϳ���� ���̹Ƿ� 10���� ����
		{
			current_card = 10;
		}

		sum += current_card;
	}

	player_ptr->sum = sum;
}

// ���� ���θ� üũ
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

// �����÷ο�� ����÷ο� ����
int over_under_flow_detection(int max_num, int min_num, int current_num)
{
	// �����÷ο�
	if (current_num > max_num)
	{
		return 1;
	}
	// ����÷ο�
	if (current_num < min_num)
	{
		return -1;
	}
	else {
		return 0;
	}
}