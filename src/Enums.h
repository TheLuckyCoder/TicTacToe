#pragma once

using byte = unsigned char;
using Bitboard = unsigned short;

enum State : char
{
	O_WINNER = -100,
	NONE = 0,
	X_WINNER = 100
};

enum class Side : int
{
	O, X
};

constexpr Side invertSide(const Side side)
{
	return (side == Side::X) ? Side::O : Side::X;
}
