#pragma once

#include "Board.h"

class Search
{
public:
	static unsigned char getBestMove(const Board &board);

private:
	static int negaMax(const Board &board, int depth);
};
