#pragma once


void get_player_number(int* player_number);
void initialize_cards(int* cards);
void swap_cards(int* cards, int size);
void swap(int* x_ptr, int* y_ptr);
void print_array(int* arr, int size);
char* check_type(int value, int size);
char* check_card_num_check(int num, char* temp, char* type_as_charptr, char** specified_type);