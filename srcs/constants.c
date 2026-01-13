#include "libbitboard.h"

const Bitboard NOT_A_FILE = 0xFEFEFEFEFEFEFEFEULL;
const Bitboard NOT_H_FILE = 0x7F7F7F7F7F7F7F7FULL;
const Bitboard NOT_AB_FILE = 0xfcfcfcfcfcfcfcfcULL; // ~(A file | B file)
const Bitboard NOT_HG_FILE = 0x3f3f3f3f3f3f3f3fULL; // ~(G file | H file)
const Bitboard RANK_2 = 0x000000000000FF00ULL;
const Bitboard RANK_7 = 0x00FF000000000000ULL;
const Bitboard RANK_PROMOTION_W = 0xFF00000000000000ULL; // Rank 8
const Bitboard RANK_PROMOTION_B = 0x00000000000000FFULL; // Rank 1
