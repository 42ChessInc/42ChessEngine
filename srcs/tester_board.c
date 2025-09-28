#include "libbitboard.h"

int	main(int argc, char **argv)
{
    if (argc != 2)
    {
	printf("Wrong number of arguments.");
	exit(1);
    }
    if (!strcmp(argv[1], "--board"))
    {
	test_board_set_piece();
	test_ft_clean_board_and_board_set_piece();
    }
    else if (!strcmp(argv[1], "--parser"))
	test_parser();
    else
    {
	printf("No known flag.\n \
		 Usage: ./unit_test [--option]\n \
		 --board\tRun test for board state \
		 --parser\tRun test for FEN parser");
	exit(1);
    }
    return (0);
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

void test_ft_clean_board_and_board_set_piece(void)
{
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
    for (int i = 0; i < 64; i++)
        assert(b.board[i] == EMPTY);
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

void	test_parser(void)
{
    char	*buff[] = {
	"rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2",
	"rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2",
	"rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1",
	"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
	};
    char	**arr;
    char	**board;
    size_t	i;
    size_t	j;

    i = 0;
    /*
    arr = ft_fen2arr(buff[i], " ");
    while (arr[i])
	printf("%s\n", arr[i++]);
    cleanup(arr, NULL);
    */
    while (i < 4)
    {
	j = 0;
	printf("\n\nARRAY PARSER\n");
	arr = ft_fen2arr(buff[i], " ");
	while (arr[j])
	{
	    printf("%s\n", arr[j]);
	    j++;
	}
	printf("\n\nBOARD ROWS\n");
	j = 0;
	board = ft_fen2arr(arr[0], "/");
	while (board[j])
	{
	    printf("%s\n", board[j]);
	    j++;
	}
	cleanup(board, NULL);
	cleanup(arr, NULL);
	i++;
    }
}
