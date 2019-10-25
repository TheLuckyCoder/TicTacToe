#pragma once

#include "Enums.h"

class Board
{
public:
	Bitboard oPieces{};
	Bitboard xPieces{};
	State state = State::NONE;
	Side sideToMove = Side::X;
	byte lastPlacedSquare{}; // needed for the Search function

	[[nodiscard]] Bitboard getOccupied() const;
	[[nodiscard]] bool makeMove(byte square);

private:
	bool updateState();

	static bool isWinner(Bitboard side);
 };
