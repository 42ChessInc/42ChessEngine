#include "libbitboard.h"

static Bitboard get_bishop_attacks(int sq, Bitboard blockers)
{
    Bitboard attacks = 0ULL;
    int r, f;
    int tr, tf; // target rank, target file

    tr = sq / 8;
    tf = sq % 8;
    for (r = tr + 1, f = tf + 1; r <= 7 && f <= 7; r++, f++) {
        Bitboard target_sq_bb = (1ULL << SQ(f, r));
        attacks |= target_sq_bb;
        if (target_sq_bb & blockers) break; // Stop after hitting a piece
    }
    for (r = tr - 1, f = tf + 1; r >= 0 && f <= 7; r--, f++) {
        Bitboard target_sq_bb = (1ULL << SQ(f, r));
        attacks |= target_sq_bb;
        if (target_sq_bb & blockers) break;
    }
    for (r = tr - 1, f = tf - 1; r >= 0 && f >= 0; r--, f--) {
        Bitboard target_sq_bb = (1ULL << SQ(f, r));
        attacks |= target_sq_bb;
        if (target_sq_bb & blockers) break;
    }
    for (r = tr + 1, f = tf - 1; r <= 7 && f >= 0; r++, f--) {
        Bitboard target_sq_bb = (1ULL << SQ(f, r));
        attacks |= target_sq_bb;
        if (target_sq_bb & blockers) break;
    }
    return attacks;
}

void generate_bishop_moves(t_board *b, t_move move_list[], int *move_count)
{
    Bitboard my_bishops, my_pieces, enemy_pieces, all_pieces, attack_moves;
    int from_sq, to_sq;

    if (b->state.active_color == 0) // White's turn
    {
        my_bishops = b->bishops & b->white_pieces;
        my_pieces = b->white_pieces;
        enemy_pieces = b->black_pieces;
    }
    else // Black's turn
    {
        my_bishops = b->bishops & b->black_pieces;
        my_pieces = b->black_pieces;
        enemy_pieces = b->white_pieces;
    }

    all_pieces = b->white_pieces | b->black_pieces;
    while (my_bishops)
    {
        from_sq = get_lsb_index(my_bishops);
        // Get all squares this bishop attacks, considering all pieces as blockers
        attack_moves = get_bishop_attacks(from_sq, all_pieces);
        // Filter out moves to squares occupied by friendly pieces
        attack_moves &= ~my_pieces;
        while (attack_moves)
        {
            to_sq = get_lsb_index(attack_moves);
            int is_capture = (1ULL << to_sq) & enemy_pieces;
            add_move(move_list, move_count, from_sq, to_sq, EMPTY, is_capture, 0, 0);
            attack_moves &= attack_moves - 1;
        }
        my_bishops &= my_bishops - 1;
    }
}
