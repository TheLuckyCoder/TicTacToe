#include "Search.h"

#include <cassert>
#include <iostream>

#include "StackVector.h"

static int maxDepth = 0;

StackVector<Board, 9> generateMoves(const Board &board)
{
	StackVector<Board, 9> moves;

	const Side sideToMove = board.sideToMove;

	for (byte square = 0u; square < moves.capacity(); ++square)
	{
		Board tempBoard = board;

		if (!tempBoard.makeMove(square))
			continue; // if the board is not valid
		if (sideToMove == Side::X && tempBoard.state == O_WINNER)
			continue;
		if (sideToMove == Side::O && tempBoard.state == X_WINNER)
			continue;
		moves.push_back(tempBoard);
	}

	return moves;
}

byte Search::getBestMove(const Board &board)
{
	maxDepth = 0;

	const auto moves = generateMoves(board);
	Board bestMove = moves.front();

	for (const Board &move : moves)
	{
		const int newState = -negaMax(move, 1);

		if (bestMove.state > newState)
			bestMove = move;
	}

	return bestMove.lastPlacedSquare;
}

int Search::negaMax(const Board &board, const int depth)
{
	const auto moves = generateMoves(board);

	if (depth > maxDepth)
	{
		maxDepth = depth;
		std::cout << "New Max Depth Reached: " << maxDepth << std::endl;
	}

	if (moves.empty())
		return board.state;

	int bestState = -1;

	for (const Board &move : moves)
	{
		const int newState = -negaMax(move, depth + 1);

		if (newState > bestState)
			bestState = newState;
	}

	return bestState;
}
