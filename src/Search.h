#pragma once

#include <cassert>

#include "Board.h"
#include "StackVector.h"

class Search
{
	using Data = std::array<std::array<byte, 511>, 511>;

	static constexpr StackVector<Board, 9> generateMoves(const Board &board) noexcept
	{
		StackVector<Board, 9> moves{};

		const Side sideToMove = board.sideToMove;

		for (byte square = 0u; square < moves.capacity(); ++square)
		{
			Board tempBoard = board;

			// Skip this move if the board is not valid
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

	static constexpr int negaMax(Data &data, const Board &board) noexcept
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

		Board bestMove = moves.front();
		int bestScore = State::O_WINNER;

		for (const Board &move : moves)
		{
			const int newState = -negaMax(data, move);

			if (newState > bestScore)
			{
				bestMove = move;
				bestScore = newState;
			}
		}

		data[board.oPieces][board.xPieces] = bestMove.lastPlacedSquare;
		return bestScore;
	}

	static Data initData() noexcept
	{
		Data data{};

		const Board emptyBoard;
		const auto moves = generateMoves(emptyBoard);

		Board bestMove = moves.front();
		int bestScore = -100;

		for (const Board &move : moves)
		{
			const int newScore = -negaMax(data, move);

			if (bestScore < newScore)
			{
				bestScore = newScore;
				bestMove = move;
			}
		}

		data[emptyBoard.oPieces][emptyBoard.xPieces] = bestMove.lastPlacedSquare;
		return data;
	}

public:
	static byte getBestMove(const Board board) noexcept
	{
		const static Data bestMoves = initData();
		return bestMoves[board.oPieces][board.xPieces];
	}
};
