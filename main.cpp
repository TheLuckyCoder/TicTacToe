#include <iostream>

#include "src/Search.h"

void clear()
{
	// Flush all data to the screen before clearing it
	std::flush(std::cout);
#if defined _WIN32
	system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
#elif defined (__APPLE__)
	system("clear");
#endif
}

template<typename Arg, typename... Args>
void print(Arg &&arg, Args &&...args)
{
	std::cout << std::forward<Arg>(arg);
	((std::cout << std::forward<Args>(args)), ...);
}

void printMainBoard(const Board &board)
{
	clear();
	std::array<char, 9> chars{};

	for (unsigned i = 0; i < chars.max_size(); ++i)
	{
		if (board.oPieces & Rays::shiftedBoards[i])
			chars[i] = 'O';
		else if (board.xPieces & Rays::shiftedBoards[i])
			chars[i] = 'X';
		else
			chars[i] = ' ';
	}

	// Iterate backwards so we can print from bottom to top
	for (auto i = chars.size(); i--;)
	{
		print(chars[i]);
		if (i % 3 == 0)
			print("\n- - -\n");
		else
			print('|');
	}

	print("\nPress q to quit\n");
}

bool checkForWinners(const Board &board)
{
	if (board.state == State::X_WINNER)
	{
		print("X has Won!\n");
		return true;
	}

	if (board.state == State::O_WINNER)
	{
		print("O has Won!\n");
		return true;
	}

	return false;
}

int main()
{
	Board board;

	printMainBoard(board);

	while (true)
	{
		const char input = std::cin.get();
		if (input == 'q')
			break;

		if (input < '1' || input > '9')
			continue;

		const byte selectedSquare = static_cast<byte>(input - '1');
		assert(board.makeMove(selectedSquare));

		printMainBoard(board);
		if (checkForWinners(board))
			break;

		// Print the board before and after the move is made
		{
			const byte bestMoveFound = Search::getBestMove(board);
			assert(board.makeMove(bestMoveFound));
			printMainBoard(board);
			if (checkForWinners(board))
				break;
		}
	}
	
	return 0;
}
