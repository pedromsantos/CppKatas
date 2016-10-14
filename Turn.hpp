#pragma once

enum Player { X, O };

enum Row { TOP, MIDLDE, BOTTOM };

enum Column { LEFT, CENTER, RIGHT };

class Turn
{
private:
	Player player;
	Row row;
	Column column;

public:
	Turn(const Player player, const Row row, const Column column);

	bool IsSamePosition(const Row &row, const Column &column) const;

	bool IsSamePlayer(const Player &player) const;
};