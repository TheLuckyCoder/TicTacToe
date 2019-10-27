#pragma once

#include <cassert>

#include "Board.h"
#include "StackVector.h"

class Search
{
public:
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

	static constexpr int negaMax(const Board &board) noexcept
	{
		const auto moves = generateMoves(board);

		if (moves.empty())
		{
			int score = board.state;
			if (score == State::X_WINNER)
				score -= board.movesCount;
			else if (score == State::O_WINNER)
				score += board.movesCount;
			else
				return 0;

			return (board.sideToMove == Side::X) ? score : -score;
		}

		int bestState = State::O_WINNER;

		for (const Board &move : moves)
		{
			const int newState = -negaMax(move);

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
			const int newScore = -negaMax(move);

			if (bestScore < newScore)
			{
				bestScore = newScore;
				bestMove = move;
			}
		}

		return bestMove.lastPlacedSquare;
	}
};
