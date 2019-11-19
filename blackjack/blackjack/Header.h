#pragma once
#include "Constants.h"
#include "Players.h"

// global variables
int player_number;               // �÷��̾� ��
int cards_tray[N_TOTAL_CARDS];   // ���� ī����� ��� Ʈ����
int distribution_cursor;         // (Ʈ������ ������ ���Ұ� �ִ� �ε��� + 1)�� ����Ű�� Ŀ��

// Source.c
int check_if_game_end();
int get_winner();

// initialize_cards.c
void initialize_cards(int* cards);
void randomize_cards(int* cards);
void swap(int* x_ptr, int* y_ptr);

// initialize_player.c
void set_players();
void initialize_players_after_round();

// cards_to_string.c
void cards_to_string(int* player_cards, char* player_cards_string, int size, int dealer_flag);
void define_card_type(char* card_name, int value);

// game_logic.c
void game_logic_per_round();
int over_under_flow_detection(int max_num, int min_num, int current_num);
void set_players_bet(int* players_bet);
void distribute_cards(int dealer_turn_flag, int i);
void print_cards(int dealer_turn_flag, int i);
void select_go_stop(int i, int* result);
void card_offering();
void update_sum(player* player_ptr);
int check_blackjack(player* player_ptr);
void end_round(int is_blackjack, int* players_bet);
int selection(player* player_type, int i);
int who_is_blackjack();
