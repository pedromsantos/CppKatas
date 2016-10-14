#include <algorithm> 

#include "TicTacToe.h"

TurnStatus TicTacToe::PlayTurn(const Player &player, const Row &row, const Column &column)
{
    if(IsTurnValid(player))
    {
        return InvalidPlayer;
    }

    if(IsPositionTaken(row, column))
    {
        return InvalidPosition;
    }

    SaveTurn(player, row, column);

    return InProgress;
}

bool TicTacToe::IsTurnValid(const Player& player)
{
	return IsFirstTurn() 
		? player == O
		: IsSamePlayerAsLastTurn(player);
}

bool TicTacToe::IsPositionTaken(const Row &row, const Column &column) const
{
    auto it = find_if(turns.begin(), turns.end(),
                      [&row, &column](Turn t)
                      {
                          return t.IsSamePosition(row, column);
                      });

    return (it != turns.end());
}

void TicTacToe::SaveTurn(const Player& player, const Row& row, const Column& column)
{
	turns.push_back(Turn(player, row, column));
}

bool TicTacToe::IsFirstTurn() const
{
    return turns.size() == 0;
}

Turn::Turn(Player player, Row row, Column column)
{
    this->player = player;
    this->row = row;
    this->column = column;
}

bool Turn::IsSamePosition(const Row &row, const Column &column) const
{
    return this->row == row && this->column == column;
}

bool Turn::IsSamePlayer(const Player &player) const
{
    return this->player == player;
}

bool TicTacToe::IsSamePlayerAsLastTurn(const Player& player)
{
	return turns.back().IsSamePlayer(player);
}