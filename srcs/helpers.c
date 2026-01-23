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

void	board_set_piece(t_board *b, int sq, t_piece piece)
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
			default : break ;
		}
		b->board[sq] = piece;
	}
	else
		b->board[sq] = EMPTY;
}

int	get_lsb_index(Bitboard b)
{
	const Bitborad	magic_number = 0x03f79d71b4cb0a89ULL;
	const int	debruijn64[64] = {
		0, 1, 48, 2, 57, 49, 28, 3,
		61, 58, 50, 42, 38, 29, 17, 4,
		62, 55, 59, 36, 53, 51, 43, 22,
		45, 39, 33, 30, 24, 18, 12, 5,
		63, 47, 56, 27, 60, 41, 37, 16,
		54, 52, 21, 44, 32, 23, 11, 46,
		40, 26, 35, 20, 31, 25, 15, 19,
		13, 10, 14, 9, 8, 7, 6, 28
	};

	if (!b)
		return -1;
	Bitboard lsb = b & -b;
	return (debruijn64[((lsb * magic_number) >> 58)]);
}
