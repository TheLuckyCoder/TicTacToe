#include "Board.h"

#include "Rays.h"

Bitboard Board::getOccupied() const
{
	return oPieces | xPieces;
}

/*
 * Returns false if the move couldn't be made or the new board is invalid
 */
bool Board::makeMove(const byte square)
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

/*
 * Returns false is this board is invalid
 */
bool Board::updateState()
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

bool Board::isWinner(const Bitboard side)
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
