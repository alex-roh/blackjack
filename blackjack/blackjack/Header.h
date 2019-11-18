#pragma once


void get_player_number(int* player_number);
void initialize_cards(int* cards);
void randomize_cards(int* cards);
void swap(int* x_ptr, int* y_ptr);
void print_array(int* arr, int size);
char* get_card_type(int value);
void define_card_type(char* card_name, int value);
char* get_player_cards(int* player_cards, int size);
