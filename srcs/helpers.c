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

void test_board_set_piece(void)
{
    t_board	b;
    ft_clean_board(&b);

	// Place white knight on e4 (SQ(4,3) = 28)
	int e4 = SQ(4,3);
	board_set_piece(&b, e4, W_KNIGHT);
	
	assert(b.board[e4] == W_KNIGHT);
	assert(b.white & (1ULL << e4));
	assert(b.knights & (1ULL << e4));
	assert(!(b.pawns & (1ULL << e4)));
	
	
	board_set_piece(&b, e4, EMPTY);
	assert(b.board[e4] == EMPTY);
	assert(!(b.white & (1ULL << e4)));
	assert(!(b.knights & (1ULL << e4)));
	
	printf("✅ board_set_piece test passed.\n");
}

void test_ft_clean_board_and_board_set_piece() {
    t_board b;

    // Test 1: Clean board
    ft_clean_board(&b);
    assert(b.white == 0ULL);
    assert(b.black == 0ULL);
    assert(b.pawns == 0ULL);
    assert(b.knights == 0ULL);
    assert(b.bishops == 0ULL);
    assert(b.rooks == 0ULL);
    assert(b.queens == 0ULL);
    assert(b.kings == 0ULL);
    for (int i = 0; i < 64; i++) {
        assert(b.board[i] == EMPTY);
    }
    printf("✅ Test 1: ft_clean_board works.\n");

    // Test 2: Set white knight on e4 (SQ_E4 = 28)
    int sq = SQ_E4; // or 28
    board_set_piece(&b, sq, W_KNIGHT);

    Bitboard mask = 1ULL << sq;
    assert(b.white & mask);
    assert(!(b.black & mask));
    assert(b.knights & mask);
    assert(!(b.pawns & mask));
    assert(!(b.bishops & mask));
    assert(!(b.rooks & mask));
    assert(!(b.queens & mask));
    assert(!(b.kings & mask));
    assert(b.board[sq] == W_KNIGHT);
    printf("✅ Test 2: Setting W_KNIGHT on e4 works.\n");

    // Test 3: Set black queen on same square — should clear knight first
    board_set_piece(&b, sq, B_QUEEN);

    assert(!(b.white & mask)); // white bit cleared
    assert(b.black & mask);    // black bit set
    assert(!(b.knights & mask)); // knight bit cleared
    assert(b.queens & mask);     // queen bit set
    assert(b.board[sq] == B_QUEEN);
    printf("✅ Test 3: Overwriting square with B_QUEEN works.\n");

    // Test 4: Set EMPTY — should clear everything
    board_set_piece(&b, sq, EMPTY);

    assert(!(b.white & mask));
    assert(!(b.black & mask));
    assert(!(b.pawns & mask));
    assert(!(b.knights & mask));
    assert(!(b.bishops & mask));
    assert(!(b.rooks & mask));
    assert(!(b.queens & mask));
    assert(!(b.kings & mask));
    assert(b.board[sq] == EMPTY);
    printf("✅ Test 4: Setting EMPTY works.\n");

    printf("🎉 All board_set_piece tests passed.\n");
}
