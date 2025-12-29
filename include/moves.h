#include <stdbool.h>
#include "game_structs.h"

struct Move
{
	int from_x, from_y;
	int to_x, to_y;
};

struct Delta
{
	int dx;
	int dy;
};

typedef struct Delta DELTA;
typedef struct Move MOVE;

int is_move_legal(const GAME *restrict game, const MOVE *restrict move, bool *restrict out);
int apply_move(GAME *restrict game, const MOVE *restrict move);
