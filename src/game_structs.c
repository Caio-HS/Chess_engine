#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include "game_structs.h"

static int initialize_board(BOARD *restrict board, const char *restrict definition);
static int loadDefaultMap(BOARD *restrict board);
static int loadCustomMap(BOARD *restrict board, FILE *restrict inputStream); // SOON TO BE

int initialize_game(GAME *restrict game, const char *restrict definition)
{
	assert(game != NULL);
	int errorCode = 0;
	if(definition != NULL) isCustomMapDefined == true;
	
	// Variaveis de estado
	*game = (GAME)
	{
		.side_to_move = WHITE;
	
		.haltmove_clock = 0;
		.fullmove_number = 0;
	
		.white_can_castle_kingside = true;
		.white_can_castle_queenside = true;
		.black_can_castle_kingside = true;
		.black_can_castle_queenside = true;
	
		.game_over = false;
	
		.winner = NONE;
	}
	
	// En_passant
	for(int i = 0; i < 8; i++) {*game.en_passant_white[i] = false;}
	for(int i = 0; i < 8; i++) {*game.en_passant_black[i] = false;}
	
	
	errorCode = initialize_board(game.board, NULL);
	
	return errorCode;
}

static int initialize_board(BOARD *restrict board, const char *restrict definition)
{
	assert(board != NULL);
	bool isCustomMapDefined = false;
	int errorCode = 0;
	FILE *restrict mapFile = NULL;
	
	if(definition != NULL) {isCustomMapDefined = true;}
	
	if(isCustomMapDefined)
	{
		mapFile = fopen(definition, "r");
		if(mapFile == NULL) return -1;
	}
	
	// Vou deixar a implementacao de mapas customizados para depois.
	if(!isCustomMapDefined){errorCode = loadDefaultMap(board);} else {errorCode = loadCustomMap(board, mapFile);}
	
	if(isCustomMapDefined) {fclose(mapFile);}
	return errorCode;
}

static int loadDefaultMap(BOARD *restrict board)
{
	assert(board != NULL);
	
	*board.squares[0][0] = (PIECE){.type = ROOK; .color = WHITE};
	*board.squares[0][7] = (PIECE){.type = ROOK; .color = WHITE};
	*board.squares[0][1] = (PIECE){.type = KNIGHT; .color = WHITE};
	*board.squares[0][6] = (PIECE){.type = KNIGHT; .color = WHITE};
	*board.squares[0][2] = (PIECE){.type = BISHOP; .color = WHITE};
	*board.squares[0][5] = (PIECE){.type = BISHOP; .color = WHITE};
	*board.squares[0][3] = (PIECE){.type = QUEEN; .color = WHITE};
	*board.squares[0][4] = (PIECE){.type = KING; .color = WHITE};
	
	*board.squares[7][0] = (PIECE){.type = ROOK; .color = BLACK};
	*board.squares[7][7] = (PIECE){.type = ROOK; .color = BLACK};
	*board.squares[7][1] = (PIECE){.type = KNIGHT; .color = BLACK};
	*board.squares[7][6] = (PIECE){.type = KNIGHT; .color = BLACK};
	*board.squares[7][2] = (PIECE){.type = BISHOP; .color = BLACK};
	*board.squares[7][5] = (PIECE){.type = BISHOP; .color = BLACK};
	*board.squares[7][3] = (PIECE){.type = QUEEN; .color = BLACK};
	*board.squares[7][4] = (PIECE){.type = KING; .color = BLACK};
	
	// Coloca os peoes
	for(int i = 0; i <= 7; ++i){*board.squares[6][i] = (PIECE){.type = PAWN; .color = BLACK};}
	for(int i = 0; i <= 7; ++i){*board.squares[1][i] = (PIECE){.type = PAWN; .color = WHITE};}
	
	// Limpa o lixo do meio do tabuleiro
	for(int i = 2; i < 6; i++)
	{
		for(int j = 0; j <=7; i++)
		{
			for(int i = 0; i <= 7; ++i){*board.squares[i][j] = (PIECE){.type = NONE; .color = NONE};}
		}
	}
	
	return 0;
}
