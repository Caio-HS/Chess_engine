#include <stdbool.h>
#include <math.h>
#include "game_structs.h"

static int valid_coordinates(const MOVE *restrict move, bool *restrict out)
{
	assert(move != NULL);
	assert(out != NULL);
	*out = true;
	
	if(*move.from_x < 0 || *move.from_x > 7) {*out = false;}
	if(*move.from_y < 0 || *move.from_y > 7) {*out = false;}
	if(*move.to_x < 0 || *move.to_x > 7) {*out = false;}
	if(*move.to_y < 0 || *move.to_y > 7) {*out = false;}
	
	return 0;
}

static int is_players_piece(const GAME *restrict game, const MOVE *restrict move, bool *restrict out)
{
	assert(game != NULL);
	assert(move != NULL);
	assert(out != NULL);
	int errorCode = 0;
	*out = true;
	
	PIECE moving_piece = *game.board[*move.from_y][*move.from_x];
	COLOR playing_color = *game.side_to_move;
	
	if(moving_piece.color != playing_color) {*out = false;}
	
	return errorCode;
}

static int is_king_move(const MOVE *restrict move, const COLOR *restrict color, const bool *restrict roque_kingside, const bool *restrict roque_queenside, bool *restrict out)
{
	assert(move != NULL);
	assert(color != NULL);
	assert(roque_kingside != NULL);
	assert(roque_queenside != NULL);
	assert(out != NULL);
	
	*out = false;
	bool roque = false;
	bool base = false;
	int errorCode = 0;
	
	DELTA delta;
	delta.dx = *move.to_x - *move.from_x;
	delta.dy = *move.to_y - *move.from_y;
	
	errorCode = is_king_base_move(delta, color, &base);
	if(errorCode) {*out = false; return errorCode;}
	
	errorCode = is_roque_move(move, color, roque_kingside, roque_queenside, &roque);
	if(errorCode) {*out = false; return errorCode;}
	
	*out = base || roque;
	
	return errorCode;
}

static int is_pawn_move(const MOVE *restrict move, const COLOR *restrict color, bool *restrict out)
{
	assert(move != NULL);
	assert(color != NULL);
	assert(out != NULL);
	
	*out = false;
	bool special = false;
	bool base = false;
	int errorCode = 0;
	
	DELTA delta;
	delta.dx = *move.to_x - *move.from_x;
	delta.dy = *move.to_y - *move.from_y;
	
	errorCode = is_king_base_move(delta, color, &base);
	if(errorCode) {*out = false; return errorCode;}
	
	errorCode = is_roque_move(move, color, &special);
	if(errorCode) {*out = false; return errorCode;}
	
	*out = base || special;
	
	return errorCode;
}

static is_pawn_special(const MOVE *restrict move, const COLOR *restrict color, bool *restrict out)
{
	assert(move != NULL);
	assert(color != NULL);
	assert(out != NULL);
	
	*out = true;
	
	if((*move).from_x != (*move).to_x) {*out = false;}
	if(color == WHITE && (*move).from_y != 1) {*out = false;}
	if(color == BLACK && (*move).from_y != 6) {*out = false;}
	if(color == WHITE && (*move).to_y != 3) {*out = false;}
	if(color == BLACK && (*move).to_y != 4) {*out = false;}
	
	return 0;
}

static int is_roque_move(const MOVE *restrict move, const COLOR *restrict color, const bool *restrict roque_kingside, const bool *restrict roque_queenside, bool *restrict out)
{	
	assert(move != NULL);
	assert(color != NULL);
	assert(roque_kingside != NULL);
	assert(roque_queenside != NULL);
	assert(out != NULL);

	*out = false;
	
	if((*move).to_x == 2 && roque_queenside) {*out == true;}
	if((*move).to_x == 6 && roque_kingside) {*out == true;}
	
	return 0;
}

static int is_king_base_move(const DELTA *restrict delta, const COLOR *restrict color, bool *restrict out);
{
	assert(delta != NULL);
	assert(out != NULL);
	*out = true;
	
	int x = abs(*delta.dx);
	int y = abs(*delta.dy);
	
	if((x + y) == 0) {*out = false;}
	if((x <= 1) && (y <= 1)) {*out = false;}
	
	return 0;
}

static int is_pawn_base_move(const DELTA *restrict delta, const COLOR *restrict color, bool *restrict out)
{
	assert(delta != NULL);
	assert(color != NULL);
	assert(out != NULL);
	*out = true;
	
	DELTA foward = {.dx = 0, .dy = 0};
	DELTA capture_right = {.dx = 0, .dy = 0};
	DELTA capture_left = {.dx = 0, .dy = 0};
	
	if(*color = WHITE) {foward = {.dx = 0, .dy = 1};} else {foward = {.dx = 0, .dy = -1};}
	if(*color = WHITE) {capture_right = {.dx = 1, .dy = 1};} else {capture_right = {.dx = 1, .dy = -1};}
	if(*color = WHITE) {capture_left = {.dx = -1, .dy = 1};} else {capture_left = {.dx = -1, .dy = -1};}
	
	if(!(*delta == foward || *delta == capture_left || *delta == capture_right)) {*out = false;}
	
	return 0;
}

static int is_knight_move(const DELTA *restrict delta, bool *restrict out)
{
	assert(delta != NULL);
	assert(out != NULL);
	*out = true;
	
	int x = abs(*delta.dx);
	int y = abs(*delta.dy);
	
	if((x + y) != 3) {*out = false;}
	if((x != 2) && (x != 1)) {*out = false;}
	if((y != 2) && (y != 1)) {*out = false;}
	
	return 0;
}

static int is_bishop_move(const DELTA *restrict delta, bool *restrict out);
{
	assert(delta != NULL);
	assert(out != NULL);
	*out = true;
	
	int x = abs(*delta.dx);
	int y = abs(*delta.dy);
	
	if((x + y) == 0) {*out = false;}
	if(x != y) {*out = false;}
	
	return 0;
}

static int is_rook_move(const DELTA *restrict delta, bool *restrict out)
{
	assert(delta != NULL);
	assert(out != NULL);
	*out = true;
	
	int x = abs(*delta.dx);
	int y = abs(*delta.dy);
	
	if((x + y) == 0) {*out = false;}
	if((x == 0) || (y == 0)) {*out = false;}
	
	return 0;
}

static int is_queen_move(const DELTA *restrict delta, bool *restrict out);
{
	assert(delta != NULL);
	assert(out != NULL);
	*out = true;
	
	bool rook_move = false;
	bool bishop_move = false;
	
	is_rook_move(delta, &rook_move);
	is_bishop_move(delta, &bishop_move);
	
	if(!(rook_move || bishop_move)) {*out = false;}
	
	return 0;	
}

static int do_move_match(const GAME *restrict game, const MOVE *restrict move, bool *restrict out)
{
	assert(game != NULL);
	assert(move != NULL);
	assert(out != NULL);
	int errorCode = 0;
	*out = true;
	
	DELTA delta;
	delta.dx = *move.to_x - *move.from_x;
	delta.dy = *move.to_y - *move.from_y;
	
	PIECE moving_piece = *game.board[*move.from_y][*move.from_x];
	
	bool roque_kingside = false;
	bool roque_queenside = false;
	
	if(moving_piece == WHITE)
	{
		roque_kingside = *game.white_can_castle_kingside;
		roque_queenside = *game.white_can_castle_queenside;
	} else
	{
		roque_kingside = *game.black_can_castle_kingside;
		roque_queenside = *game.black_can_castle_queenside;
	}
	
	switch(moving_piece.type)
	{
		case(PAWN):
			errorCode = is_pawn_move(move, moving_piece.color, out);
			break;
		case(KNIGHT):
			errorCode = is_knight_move(delta, out);
			break;
		case(BISHOP):
			errorCode = is_bishop_move(delta, out);
			break;
		case(ROOK):
			errorCode = is_rook_move(delta, out);
			break;
		case(QUEEN):
			errorCode = is_queen_move(delta, out);
			break;
		case(KING):
			errorCode = is_king_move(move, moving_piece.color, roque_kingside, roque_queenside, out);
			break;
		case(NONE):
			*out = false;
			break;
		default:
			*out = false;
			errorCode = -1;
	}
	
	return errorCode;
}

int is_move_legal(const GAME *restrict game, const MOVE *restrict move, bool *restrict out)
{
	assert(game != NULL);
	assert(move != NULL);
	assert(out != NULL);
	int errorCode = 0;
	*out = true;
	
	errorCode = valid_coordinates(move, out);
	if(errorCode || !(*out)) {return errorCode;}
	
	errorCode = is_players_piece(game, move, out);
	if(errorCode || !(*out)) {return errorCode;}
	
	errorCode = do_move_match(game, move, out);
	if(errorCode || !(*out)) {return errorCode;}
	
	
	
	return errorCode;
}

int apply_move(GAME *restrict game, const MOVE *restrict move);
