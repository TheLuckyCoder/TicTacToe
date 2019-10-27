#pragma once

#include "Enums.h"
#include "Rays.h"

class Board
{
public:
	Bitboard oPieces{};
	Bitboard xPieces{};
	State state = State::NONE;
	Side sideToMove = Side::X;
	byte lastPlacedSquare{}; // needed for the Search function

	constexpr Bitboard getOccupied() const noexcept
	{
		return oPieces | xPieces;
	}

	/*
 	* Returns false if the move couldn't be made or the new board is invalid
 	*/
	constexpr bool makeMove(const byte square) noexcept
	{
		const Bitboard allPieces = getOccupied();

		if (allPieces & Rays::shiftedBoards[square])
			return false;

		auto &pieces = (sideToMove == Side::X) ? xPieces : oPieces;

		pieces |= Rays::shiftedBoards[square];
		sideToMove = invertSide(sideToMove);
		lastPlacedSquare = square;

		return updateState();
	}

private:
	/*
	* Returns false is this board is invalid
	*/
	constexpr bool updateState() noexcept
	{
		const bool isXWinner = isWinner(xPieces);
		const bool isOWinner = isWinner(oPieces);

		if (isXWinner && isOWinner)
			return false;

		if (isXWinner)
			state = State::X_WINNER;
		else if (isOWinner)
			state = State::O_WINNER;
		else
			state = State::NONE;

		return true;
	}

	static constexpr bool isWinner(const Bitboard side) noexcept
	{
		using namespace Rays;

		return (side & WEST) == WEST ||
			(side & EAST) == EAST ||
			(side & NORTH) == NORTH ||
			(side & SOUTH) == SOUTH ||
			(side & HORIZONTAL) == HORIZONTAL ||
			(side & VERTICAL) == VERTICAL ||
			(side & DIAGONAL_MAIN) == DIAGONAL_MAIN ||
			(side & DIAGONAL_SEC) == DIAGONAL_SEC;
	}
};
