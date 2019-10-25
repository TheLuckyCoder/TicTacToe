#pragma once

using byte = unsigned char;
using Bitboard = unsigned short;

enum State : char
{
	O_WINNER = -1,
	NONE = 0,
	X_WINNER = 1
};

enum class Side : bool
{
	O, X
};

constexpr Side invertSide(const Side side)
{
	return (side == Side::X) ? Side::O : Side::X;
}
