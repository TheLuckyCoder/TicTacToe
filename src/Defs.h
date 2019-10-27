#pragma once

#include <array>

using byte = unsigned char;
using Bitboard = unsigned short;

enum State : char
{
	O_WINNER = -100,
	NONE = 0,
	X_WINNER = 100
};

enum class Side : char
{
	O, X
};

constexpr Side invertSide(const Side side)
{
	return (side == Side::X) ? Side::O : Side::X;
}

namespace Rays
{
	constexpr auto shiftedBoards = [] {
		std::array<Bitboard, 9> boards{};
		boards[0] = 1u;

		for (unsigned i = 1; i < boards.max_size(); ++i)
			boards[i] = boards[i - 1] << 1u;

		return boards;
	}();

	constexpr unsigned short WEST = 0b100'100'100;
	constexpr unsigned short EAST = 0b001'001'001;
	constexpr unsigned short NORTH = 0b111'000'000;
	constexpr unsigned short SOUTH = 0b000'000'111;
	constexpr unsigned short HORIZONTAL = 0b010'010'010;
	constexpr unsigned short VERTICAL = 0b000'111'000;
	constexpr unsigned short DIAGONAL_MAIN = 0b001'010'100;
	constexpr unsigned short DIAGONAL_SEC = 0b100'010'001;
}
