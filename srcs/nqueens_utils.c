#include "board.h"
#include <stdio.h>

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

int	init_state(char **argv, t_state **state)
{
	int	i;

	*state = (t_state *)calloc(1, sizeof(t_state));
	if (!*state)
		return (-1);
	(*state)->size = atoi(argv[1]);
	(*state)->board = (int *)calloc((*state)->size, sizeof(int));
	if (!(*state)->board)
		return (-1);
	i = -1;
	while (++i < (*state)->size)
		(*state)->board[i] = -1;
	(*state)->next = NULL;
	(*state)->prev = NULL;
	return (0);
}

t_state	*new_state(t_state **old_board)
{
	t_state	*new;

	if (!*old_board)
		return (NULL);
	memcpy(new, *old_board, sizeof(t_state));
}

int	cleanup(t_state **state)
{
	if (!*state)
		return (-1);
	if ((*state)->board)
		free((*state)->board);
	if ((*state)->next)
		free((*state)->next);
	if ((*state)->prev)
		free((*state)->prev);
	free(*state);
	return (0);
}








