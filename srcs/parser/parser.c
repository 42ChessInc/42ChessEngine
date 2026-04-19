#include "board.h"
#include <unistd.h>
#include <stdlib.h>

typedef struct	

int	parse_fen(board_t *board, const char *fen)
{
	if (!board || !fen)
		return 0;
	memset(board, 0, sizeof(board_t));
	int	rank = 7;
	int	file = 0;

	while (*fen && *fen != ' ')
	{
		
	}
}
