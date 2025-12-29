#include <stdbool.h>
#include <stdio.h>

// Define valores utilizados
enum PieceType 
{
    NONE,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

enum Color 
{
    WHITE,
    BLACK,
    NONE
};

// Define estruturas
struct Piece 
{
    PIECETYPE type;
    COLOR color;
};

struct Board 
{
    PIECE squares[8][8];
};

struct Game
{
	BOARD board;
	
	COLOR side_to_move;

    // Estado auxiliar
    int haltmove_clock;   // regra dos 50 lances
    int fullmove_number;

    // Roque
    bool white_can_castle_kingside;
    bool white_can_castle_queenside;
    bool black_can_castle_kingside;
    bool black_can_castle_queenside;

    // En passant
    bool en_passant_white[8];
	bool en_passant_black[8];
	
    // Estado do jogo
    bool game_over;
    COLOR winner; // WHITE, BLACK ou empate
};


// Define tipos
typedef struct Game GAME;
typedef struct Board BOARD;
typedef struct Piece PIECE;
typedef enum PieceType PIECETYPE;
typedef enum Color COLOR;

// Define funcoes de gerenciamento
int initialize_game(GAME *restrict game, const char *restrict definition);
