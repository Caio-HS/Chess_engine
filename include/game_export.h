#include <stdbool.h>
#include <stdint.h>
#include "game_structs.h"

#define COLOR_MASK  0x01

#define NONE_MASK   (1 << 1)
#define PAWN_MASK   (1 << 2)
#define KNIGHT_MASK (1 << 3)
#define BISHOP_MASK (1 << 4)
#define ROOK_MASK   (1 << 5)
#define QUEEN_MASK  (1 << 6)
#define KING_MASK   (1 << 7)


_Static_assert(sizeof(bool) == 1, "bool must be 1 byte in GameExport");

// Board[i][j] i = 0 => x1, i = 7 => 8 / j = 0 => ax, j = 7 => hx
// Black = 0 / White = 1
// LSB defines color, each other bit defines a piece.
// 2^0 color
// 2^1 NONE
// 2^2 PAWN
// 2^3 KNIGHT
// 2^4 BISHOP
// 2^5 ROOK
// 2^6 QUEEN
// 2^7 KING
struct GameExport
{
	uint8_t board[8][8];
	
	bool side_to_move;
	
	bool white_can_castle_kingside;
    bool white_can_castle_queenside;
    bool black_can_castle_kingside;
    bool black_can_castle_queenside;
    
	bool en_passant_white[8]; //From 0 = a and 7 = h
	bool en_passant_black[8]; //From 0 = a and 7 = h
}

// Define tipos
typedef struct GameExport GAME_EXPORT;

int export_game(const GAME *restrict game, GAME_EXPORT *restrict out);
