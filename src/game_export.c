#include <stdbool.h>
#include <stdint.h>
#include "game_structs.h"
#include "game_export.h"

static uint8_t export_piece(PieceType type, Color color);
static int write_export_board(const BOARD *restrict board, GAME_EXPORT *restrict out);

int export_game(const GAME *restrict game, GAME_EXPORT *restrict out)
{
	assert(board != NULL);
	assert(out != NULL);
	int errorCode = 0;
	
	errorCode = write_export_board(board, out);
	
	*out.side_to_move = *board.side_to_move;
	*out.white_can_castle_kingside = *board.white_can_castle_kingside;
    *out.white_can_castle_queenside = *board.white_can_castle_queenside;
    *out.black_can_castle_kingside = *board.black_can_castle_kingside;
    *out.black_can_castle_queenside = *board.black_can_castle_queenside;
    
    for(int i = 0; i <= 7; i++)
    {
		*out.en_passant_white[i] = *board.en_passant_white[i];
		*out.en_passant_black[i] = *board.en_passant_black[i];
	}
	
	return errorCode;
}

static int write_export_board(const BOARD *restrict board, GAME_EXPORT *restrict out)
{
	assert(board != NULL);
	assert(out != NULL);
	int errorCode = 0;
	
	for(int i = 0; i <= 7; i++)
	{
		for(int j = 0; j <= 7; j++)
		{
			PIECE piece = *board.squares[i][j];
			errorCode = export_piece(piece.type, piece.color, out.board[i][j]);
			if(errorCode) return errorCode;
		}
	}
	
	return 0;
}

static int export_piece(PieceType type, Color color, uint8_t *restrict out)
{
    uint8_t v = 0;

    if (color == WHITE)
        v |= COLOR_MASK;

    switch (type) {
        case PIECE_NONE:   v |= PIECE_NONE_MASK;   break;
        case PIECE_PAWN:   v |= PIECE_PAWN_MASK;   break;
        case PIECE_KNIGHT: v |= PIECE_KNIGHT_MASK; break;
        case PIECE_BISHOP: v |= PIECE_BISHOP_MASK; break;
        case PIECE_ROOK:   v |= PIECE_ROOK_MASK;   break;
        case PIECE_QUEEN:  v |= PIECE_QUEEN_MASK;  break;
        case PIECE_KING:   v |= PIECE_KING_MASK;   break;
        default -1;
    }
    
    *out = v;
    return 0;
}
