#ifndef __CONSTANTS__ // "constants.h"
#define __CONSTANTS__ // "constants.h"

#define N_SET 5              // 카드 세트의 개수 
#define N_CARDS_PER_SET 52   // 세트당 카드의 개수 
#define N_TOTAL_CARDS 260    // 사용하는 카드의 총 개수 
#define N_TYPE 4             // 타입 per 카드 (하트, 클로버, 스페이드, 다이아몬드) 
#define N_CARDS_PER_TYPE 13  // 카드 per 타입 (하트1, 하트2...)  
#define N_BUFFER 21          // 플레이어에게 할당된 버퍼(자신이 받은 카드를 여기에 담음)의 크기 
#define N_MAXPLAYERS 5       // 플레이어의 최대 명수 
#define N_MINBET 15          // AI 플레이어가 베팅할 수 있는 최소 금액 
#define N_MAXBET 25          // AI 플레이어가 베팅할 수 있는 최대 금액 
#define GAMEEND 100          // 게임이 끝났다는 의미 

// 플레이어 상태 초기화와 관련된 상수 
#define SET 1
#define ROUND 2

// 플레이어들의 고유 번호
#define PLAYER 1
#define DEALER -1
#define USER 0

// 승리 조건과 관련된 상수
#define BLACKJACK 21
#define DEAD -1

// 문자열 사용에 필요한 상수 
#define MAXLENGTH 100
#define MINLENGTH 40

#endif
