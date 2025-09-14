#include "board.h"

int		isvalid(int *queens, int n, int i);
void	print_result(int *queens, int size);
void	algorithm(int *queens, int size, int nth_queen, int *flag);

int	main(int argc, char **argv)
{
	int	*queens;
	int	size;
	int	found_solution;

	if (argc != 2)
		return (-1);
	found_solution = 0;
	size = atoi(argv[1]);
	queens = (int *)malloc(size * sizeof(int));
	memset(queens, -1, size * sizeof(int));
	algorithm(queens, size, 0, &found_solution);
	if (!found_solution)
		printf("No solution...\n");
	free(queens);
	return (0);
}

void	algorithm(int *queens, int size, int nth_queen, int *flag)
{
	int	col;

	if (nth_queen == size)
	{
		print_result(queens, size);
		*flag = 1;
		return ;
	}
	col = 0;
	while (col < size)
	{
		if (isvalid(queens, nth_queen, col))
		{
			queens[nth_queen] = col;
			algorithm(queens, size, nth_queen + 1, flag);
		}
		col++;
	}
}

int	isvalid(int *queens, int row, int col)
{
	int	i;

	i = 0;
	while (i < row)
	{
		if (queens[i] == col || abs(row - i) == abs(col - queens[i]))
			return (0);
		i++;
	}
	return (1);
}

void	print_result(int *queens, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("%d ", queens[i]);
		i++;
	}
	printf("\n");
}
/*
int	main(int argc, char **argv)
{
	t_state	*this;
	//int	solution4[4] = {2, 0, 3, 1};
	//int	solution5[5] = {0, 2, 4, 1, 3};
	//int	solution6[6] = {1, 3, 5, 0, 2, 4};
	//int	solution7[7] = {0, 2, 4, 6, 1, 3, 5};
	//int	solution8[8] = {1, 3, 5, 7, 0, 2, 4, 6};

	if (argc != 2)
		return (-1);
	init_state(argv, &this);
	At start:
	row index    -> -1	-1	-1	-1
	column index ->  0	 1	 2	 3
	//print_board(board_state, problem_size);
	print_board(this->board, this->size);
	cleanup(&this);
}
*/
