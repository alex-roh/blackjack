#ifndef __PLAYERS__ // "players.h"
#define __PLAYERS__ // ""players.h"

#include "constants.h"

// �÷��̾���� ������ ��� ����ü ����
typedef struct Player {

	char name[MINLENGTH];  // �÷��̾��� �̸�
	int dollars;           // ���� �ݾ�
	int is_alive;          // ���� ����
	int buffer[N_BUFFER];  // ī�带 ���� ����
	int sum;               // �� ���忡�� ī���� ��
	int buffer_cursor;     // (������ ������ ���Ұ� �ִ� �ε��� + 1)�� ����Ű�� Ŀ��

} player;

// �÷��̾� �迭�� ���� ������ ����
player players[N_MAXPLAYERS]; // �ε��� 0�� ������ ���� �ڱ� �ڽ�

// ������ ������ ��� ����ü ������ �������� ����
player dealer;

#endif
