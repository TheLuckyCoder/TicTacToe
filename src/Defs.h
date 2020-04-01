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
	constexpr static auto SQUARE_BITBOARDS = []
	{
		std::array<Bitboard, 9> boards{};
		boards[0] = 1u;

		for (unsigned i = 1; i < boards.max_size(); ++i)
			boards[i] = boards[i - 1] << 1u;

		return boards;
	}();

	constexpr Bitboard toBitboard(const byte index) noexcept
	{
		assert(index < 9u);
		return SQUARE_BITBOARDS[index];
	}

	constexpr Bitboard ALL_SQUARES = 0b111'111'111;
	constexpr Bitboard WEST = 0b100'100'100;
	constexpr Bitboard EAST = 0b001'001'001;
	constexpr Bitboard NORTH = 0b111'000'000;
	constexpr Bitboard SOUTH = 0b000'000'111;
	constexpr Bitboard HORIZONTAL = 0b010'010'010;
	constexpr Bitboard VERTICAL = 0b000'111'000;
	constexpr Bitboard DIAGONAL_MAIN = 0b001'010'100;
	constexpr Bitboard DIAGONAL_SEC = 0b100'010'001;
}
