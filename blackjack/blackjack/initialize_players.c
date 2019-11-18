#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Constants.h"

typedef struct Player {

	int dollars;
	int buffer[N_BUFFER];
	char cards_string[MAXLENGTH];

} player;

player players[N_MAXPLAYERS];

struct Server {

	int dollars;
	int buffer[N_BUFFER];
	char cards_string[MAXLENGTH];

} server;

void get_player_number(int* player_number)
{
	printf("������ �÷����� �÷��̾��� ���� �Է��Ͻʽÿ�: ");
	scanf_s("%d", player_number);
}

void set_players(int player_number)
{
	for(int i = 0; i < player_number; i++)
	{
		players[i].dollars = 50;
	}

	server.dollars = 50;

}