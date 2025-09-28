#include "libbitboard.h"

void	ft_clean_board(t_board *b)
{
	b->white = 0ULL;
	b->black = 0ULL;
	b->pawns = 0ULL;
	b->knights = 0ULL;
	b->bishops = 0ULL;
	b->rooks = 0ULL;
	b->queens = 0ULL;
	b->kings = 0ULL;
	memset(b->board, 0, 64 * sizeof(int));
}

void	board_set_piece(t_board *b, int sq, int piece)
{
	Bitboard	sq_mask;

	sq_mask = 1ULL << sq;
	b->white &= ~sq_mask;
	b->black &= ~sq_mask;
	b->pawns &= ~sq_mask;
	b->knights &= ~sq_mask;
	b->bishops &= ~sq_mask;
	b->rooks &= ~sq_mask;
	b->queens &= ~sq_mask;
	b->kings &= ~sq_mask;

	if (piece != EMPTY)
	{
		if (piece >= W_PAWN && piece <= W_KING)
			b->white |= sq_mask;
		else if (piece >= B_PAWN && piece <= B_KING)
			b->black |= sq_mask;
		switch (piece)
		{
			case W_PAWN: case B_PAWN: b->pawns |= sq_mask; break ;
			case W_KNIGHT: case B_KNIGHT: b->knights |= sq_mask; break ;
			case W_BISHOP: case B_BISHOP: b->bishops |= sq_mask; break ;
			case W_ROOK: case B_ROOK: b->rooks |= sq_mask; break ;
			case W_QUEEN: case B_QUEEN: b->queens |= sq_mask; break ;
			case W_KING: case B_KING: b->kings |= sq_mask; break ;
		}
		b->board[sq] = piece;
	}
	else
		b->board[sq] = EMPTY;
}
