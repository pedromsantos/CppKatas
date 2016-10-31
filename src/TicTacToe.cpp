#include "TicTacToe.hpp"

TurnStatus TicTacToe::PlayTurn(const Player &player, const Row &row, const Column &column)
{
	auto status = InProgress;

    if(IsPlayerInvalid(player))
    {
		status = InvalidPlayer;
    }

    if(IsPositionTaken(row, column))
    {
		status = InvalidPosition;
    }

    SaveTurn(player, row, column);

	if(IsWinner(player))
	{
		status = Win;
	}

    return status;
}

bool TicTacToe::IsPlayerInvalid(const Player& player) const
{
	return player == lastPlayer;
}

bool TicTacToe::IsPositionTaken(const Row &row, const Column &column) const
{
	return turns[row][column] != NONE;
}

void TicTacToe::SaveTurn(const Player& player, const Row& row, const Column& column)
{
	lastPlayer = player;
	turns[row][column] = player;
}

bool TicTacToe::IsWinner(const Player& player) const
{
	return WinnerOnRows(player) 
		|| WinnerOnColumns(player)
		|| WinnerOnDiagonal(player, LEFT, RIGHT)
		|| WinnerOnDiagonal(player, RIGHT, LEFT);
}

bool TicTacToe::WinnerOnRows(const Player& player) const
{
	for (const auto row : { TOP, MIDLDE, BOTTOM })
	{
		if (player == turns[row][LEFT]
			&& player == turns[row][CENTER]
			&& player == turns[row][RIGHT])
		{
			return true;
		}
	}
	return false;
}

bool TicTacToe::WinnerOnColumns(const Player& player) const
{
	for (const auto column : { LEFT, CENTER, RIGHT })
	{
		if (player == turns[TOP][column]
			&& player == turns[MIDLDE][column]
			&& player == turns[BOTTOM][column])
		{
			return true;
		}
	}
	return false;
}

bool TicTacToe::WinnerOnDiagonal(const Player& player, Column start, Column end) const
{
	return (player == turns[TOP][start]
			&& player == turns[MIDLDE][CENTER]
			&& player == turns[BOTTOM][end]);
}