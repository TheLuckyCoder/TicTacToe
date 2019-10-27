#pragma once

#include <cassert>
#include <iostream>

#include "Board.h"
#include "StackVector.h"

class Search
{
	static constexpr StackVector<Board, 9> generateMoves(const Board &board) noexcept
	{
		StackVector<Board, 9> moves{};

		const Side sideToMove = board.sideToMove;

		for (byte square = 0u; square < moves.capacity(); ++square)
		{
			Board tempBoard = board;

			// skip this move if the board is not valid
			if (!tempBoard.makeMove(square))
				continue;
			if (sideToMove == Side::X && tempBoard.state == O_WINNER)
				continue;
			if (sideToMove == Side::O && tempBoard.state == X_WINNER)
				continue;

			moves.push_back(tempBoard);
		}

		return moves;
	}

	static constexpr int negaMax(const Board &board, const int depth) noexcept
	{
		const auto moves = generateMoves(board);

		if (moves.empty())
			return (board.sideToMove == Side::X) ? board.state : -board.state;

		int bestState = State::O_WINNER;

		for (const Board &move : moves)
		{
			const int newState = -negaMax(move, depth + 1);

			if (newState > bestState)
				bestState = newState;
		}

		return bestState;
	}

public:
	static constexpr byte getBestMove(const Board &board)
	{
		const auto moves = generateMoves(board);
		assert(!moves.empty());
		Board bestMove = moves.front();
		int bestScore = -100;

		for (const Board &move : moves)
		{
			const int newScore = -negaMax(move, 1);

			if (bestScore > newScore)
				bestMove = move;
		}

		return bestMove.lastPlacedSquare;
	}
};
