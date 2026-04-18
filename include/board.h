#ifndef BOARD_H
# define BOARD_H

# include <stdint.h>

# define MAX_MOVES  256
# define MAX_COLORS 2
# define MAX_TYPES  6
# define COLOR_STATES 3


# define WHITE  0
# define BLACK  1
# define BOTH   2

# define PAWN   0
# define KNIGHT 1
# define BISHOP 2
# define ROOK   3
# define QUEEN  4
# define KING   5

typedef uint64_t bitboard_t;

/* * Performance Enhancement: Packed Move
 * bit 0-5:   source square (0-63)
 * bit 6-11:  destination square (0-63)
 * bit 12-15: flags (Capture, Promotion, Special moves)
 */
typedef uint16_t move_t;

typedef struct movelist_s
{
	move_t		moves[MAX_MOVES];
	uint64_t	count;
}	movelist_t;

typedef struct board_s
{
	bitboard_t	pieces[MAX_COLORS][MAX_TYPES];
	bitboard_t	occupancy[COLOR_STATES];

	uint64_t	hash;
	uint32_t	fm_num;
	uint8_t		turn;
	uint8_t		castling_rights;
	uint8_t		hm_clock;
}	board_t;

/* --- Performance-Critical Function Signatures --- */

/* Infrastructure & Bit Manipulation */
int			get_lsb_index(bitboard_t bb);
int			pop_lsb(bitboard_t *bb); /* Returns index and clears the bit */

/* Pure Bitboard Lookups */
int			get_piece_on_sq(const board_t *board, int sq, int *color);

/* Move Generation (Now strictly Bitwise) */
void		gen_all_moves(const board_t *board, movelist_t *list);
bitboard_t	get_attacks(const board_t *board, int color);

/* State Transitions */
int			make_move(board_t *board, move_t move);
void		unmake_move(board_t *board, move_t move);

/* UCI & Parsing */
int			parse_fen(board_t *board, const char *fen);
void		print_board(const board_t *board);

#endif
