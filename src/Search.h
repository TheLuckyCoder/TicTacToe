#pragma once

#include "Board.h"

class Search
{
	class Moves
	{
	public:
		constexpr void push_back(const Board &board) noexcept
		{
			if (size() < capacity())
			{
				*_end = board;
				++_end;
			}
		}

		constexpr bool empty() const noexcept { return begin() == end(); }
		constexpr byte size() const noexcept { return end() - begin(); }

		constexpr Board *begin() noexcept { return _boards; }
		constexpr const Board *begin() const noexcept { return _boards; }
		constexpr Board *end() noexcept { return _end; }
		constexpr const Board *end() const noexcept { return _end; }

		constexpr Board &front() noexcept { return *begin(); }
		constexpr const Board &front() const noexcept { return *begin(); }
		constexpr Board &back() noexcept { return *end(); }
		constexpr const Board &back() const noexcept { return *end(); }

		static constexpr byte capacity() { return CAPACITY; }

	private:
		static constexpr byte CAPACITY = 9;

	private:
		Board _boards[CAPACITY]{};
		Board *_end = _boards;
	};

	using SearchData = std::array<std::array<byte, Rays::ALL_SQUARES>, Rays::ALL_SQUARES>;

	static constexpr Moves generateMoves(const Board &board) noexcept
	{
		Moves moves{};

		const Side sideToMove = board.sideToMove;

		for (byte square = 0u; square < Moves::capacity(); ++square)
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

	static constexpr int negaMax(SearchData &data, const Board &board) noexcept
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

	static constexpr SearchData initSearchData() noexcept
	{
		SearchData data{};

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
	static byte getBestMove(const Board &board) noexcept
	{
		// Compute the entire search tree only once
		const static SearchData bestMoves = initSearchData();
		return bestMoves[board.oPieces][board.xPieces];
	}
};
