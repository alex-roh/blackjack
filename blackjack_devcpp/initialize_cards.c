#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "Header.h"
#include "Constants.h"

// ���α׷��� ���ڸ��� ����� ī�� �ʱ�ȭ �Լ� 
void initialize_cards(int* cards)
{
	// ī�� �й迡 �ʿ��� Ŀ���� 0���� �ʱ�ȭ
	distribution_cursor = 0;

	int i, j, index = 0, determine_type;

	// (11 = 'J', 12 = 'Q', 13 = 'K' -> ��� 10���� �ؼ�)
	// 101-113 : ��Ʈ
	// 201-213 : ���̾Ƹ��
	// 301-313 : �����̵�
	// 401-413 : Ŭ�ι�

	int count = N_SET;

	// ī�带 ���� 
	while (count > 0) {
		for (i = 1; i <= N_TYPE; i++)
		{
			determine_type = i * 100;

			for (j = 1; j <= N_CARDS_PER_TYPE; j++)
			{
				*(cards + index) = determine_type + j;
				index++;
			}
		}
		count--;
	}

	randomize_cards(cards);
	printf("\n----> %d�� ī�� ��Ʈ�� ��� Ʈ���̿� �־����ϴ�.\n", N_SET);
}

// ī�带 ���� �Լ� 
void randomize_cards(int* cards)
{
	srand(time(NULL));
	int i;

	for (i = 0; i < N_TOTAL_CARDS; i++)
	{
		// ��� ī�尡 ���� Ȯ���� Ư�� ��ġ�� ���� 
		int rand_index = rand() % (N_TOTAL_CARDS - i) + i;
		swap(cards + i, cards + rand_index);
	}
}

void swap(int* x_ptr, int* y_ptr)
{
	int temp = *(x_ptr);
	*(x_ptr) = *(y_ptr);
	*(y_ptr) = temp;
}
