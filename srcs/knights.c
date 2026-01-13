#include "libbitboard.h"

void	init_knight_attacks(void)
{
    for (int sq = 0; sq < 64; ++sq)
    {
	Bitboard knight_pos = 1ULL << sq;
	Bitboard attacks = 0ULL;

        attacks |= (knight_pos << 17) & NOT_A_FILE;
        attacks |= (knight_pos << 10) & NOT_AB_FILE;
        attacks |= (knight_pos >> 6)  & NOT_AB_FILE;
        attacks |= (knight_pos >> 15) & NOT_A_FILE;
        attacks |= (knight_pos << 15) & NOT_H_FILE;
        attacks |= (knight_pos << 6)  & NOT_HG_FILE;
        attacks |= (knight_pos >> 10) & NOT_HG_FILE;
        attacks |= (knight_pos >> 17) & NOT_H_FILE;
        knight_attacks[sq] = attacks;
    }
}

void generate_knight_moves(t_board *b, t_move move_list[], int *move_count)
{
    Bitboard my_knights, my_pieces, enemy_pieces, attack_moves;
    int from_sq, to_sq;
    if (b->state.active_color == 0) // White's turn
    {
	my_knights = b->knights & b->white;
    	my_pieces = b->white;
    	enemy_pieces = b->black;
    }
    else // Black's turn
    {
        my_knights = b->knights & b->black;
        my_pieces = b->black;
        enemy_pieces = b->white;
    }
    while (my_knights)
    {
        from_sq = get_lsb_index(my_knights);
        attack_moves = knight_attacks[from_sq] & ~my_pieces;
        while (attack_moves)
        {
	    to_sq = get_lsb_index(attack_moves);
            int is_capture = (1ULL << to_sq) & enemy_pieces;
            add_move(move_list, move_count, from_sq, to_sq, EMPTY, is_capture, 0, 0);
            attack_moves &= attack_moves - 1; // Clear LSB to process next move
        }
	my_knights &= my_knights - 1; // Clear LSB to process next knight
    }
}
