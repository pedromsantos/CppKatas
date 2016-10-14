#include "Turn.hpp"

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