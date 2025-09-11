#include "../include/board.h"
#include <stdio.h>

static
void	print_board(int	*board_state, int size);

int	main(int argc, char **argv)
{
	t_state	this;
	int	i;
	//int	solution4[4] = {2, 0, 3, 1};
	//int	solution5[5] = {0, 2, 4, 1, 3};
	//int	solution6[6] = {1, 3, 5, 0, 2, 4};
	//int	solution7[7] = {0, 2, 4, 6, 1, 3, 5};
	//int	solution8[8] = {1, 3, 5, 7, 0, 2, 4, 6};

	if (argc != 2)
		return (-1);
	init_state(argc, argv);
	/*
	At start:
	column index -> -1	-1	-1	-1
	row index    ->  0	 1	 2	 3
	*/
	i = -1;
	while (++i < problem_size)
		board_state[i] = -1;
	//print_board(board_state, problem_size);
	//print_board(solution4, 4);
	//print_board(solution5, 5);
	//print_board(solution6, 6);
	//print_board(solution7, 7);
	//print_board(solution8, 8);
	free(board_state);
}

static
void	print_board(int	*board_state, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		printf("\n");
		while (j < size)
		{
			if (i == board_state[j]) 
				printf(" \u2655 ");
			else
				printf(" * ");
			j++;
		}
		i++;
	}
	printf("\n");
	printf("\n");
}

static
int	init_state(char **argv, t_state **state)
{
	int	size;
	int	i;

	*state = (t_state *)calloc(1, sizeof(t_state));
	if (!*state)
		return (-1);
	size = atoi(argv[1]);
	(*state)->board = (int *)calloc(size, sizeof(int));
	if (!(*state)->board)
		return (-1);
	i = 0;
	while (i < size)
	{
		(*state)->board[i] = -1;
		i++;
	}
	(*state)->next = NULL;
}










