#include "TicTacToe.h"

TurnStatus TicTacToe::PlayTurn(const Player &player, const Row &row, const Column &column)
{
    if(IsPlayerInvalid(player))
    {
        return InvalidPlayer;
    }

    if(IsPositionTaken(row, column))
    {
        return InvalidPosition;
    }

    SaveTurn(player, row, column);

	if(turns[TOP][LEFT] == turns[TOP][CENTER] 
		&& turns[TOP][LEFT] == turns[TOP][RIGHT])
	{
		return Win;
	}

    return InProgress;
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