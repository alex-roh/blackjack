#ifndef __PLAYERS__ // "players.h"
#define __PLAYERS__ // ""players.h"

#include "constants.h"

// 플레이어들의 정보가 담긴 구조체 선언
typedef struct Player {

	char name[MINLENGTH];  // 플레이어의 이름
	int dollars;           // 보유 금액
	int is_alive;          // 생존 여부
	int buffer[N_BUFFER];  // 카드를 담을 버퍼
	int sum;               // 한 라운드에서 카드의 합
	int buffer_cursor;     // (버퍼의 마지막 원소가 있는 인덱스 + 1)를 가리키는 커서

} player;

// 플레이어 배열을 전역 변수로 선언
player players[N_MAXPLAYERS]; // 인덱스 0은 언제나 유저 자기 자신

// 딜러의 정보가 담긴 구조체 변수를 전역으로 선언
player dealer;

#endif
