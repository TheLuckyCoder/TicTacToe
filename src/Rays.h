#pragma once

#include <array>

#include "Enums.h"

namespace Rays
{
	constexpr auto shiftedBoards = [] {
		std::array<Bitboard, 9> boards{};
		boards[0] = 1u;

		for (unsigned i = 1; i < boards.max_size(); ++i)
			boards[i] = boards[i - 1] << 1u;

		return boards;
	}();

	enum Rays : unsigned short
	{
		WEST = 0b100'100'100,
		EAST = 0b001'001'001,
		NORTH = 0b111'000'000,
		SOUTH = 0b000'000'111,
		HORIZONTAL = 0b010'010'010,
		VERTICAL = 0b000'111'000,
		DIAGONAL_MAIN = 0b001'010'100,
		DIAGONAL_SEC = 0b100'010'001,
	};
}
