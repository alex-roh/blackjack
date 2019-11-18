#pragma once

void get_player_number(int* player_number);
void initialize_cards(int* cards);
void randomize_cards(int* cards);
void swap(int* x_ptr, int* y_ptr);
void print_array(int* arr, int size);
void define_card_type(char* card_name, int value);
void cards_to_string(int* player_cards, char* player_cards_string, int size);