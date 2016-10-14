#ifndef CPPKATAS_TICTACTOE_H
#define CPPKATAS_TICTACTOE_H

#include <vector>
#include "../Turn.hpp"

enum TurnStatus { InProgress, InvalidPlayer, InvalidPosition };

class TicTacToe
{
    std::vector<Turn> turns;

    bool IsFirstTurn() const;

    bool IsPositionTaken(const Row &row, const Column &column) const;

	bool IsSamePlayerAsLastTurn(const Player& player);
	void SaveTurn(const Player& player, const Row& row, const Column& column);
	bool IsTurnValid(const Player& player);

public:	
    TurnStatus PlayTurn(const Player &player, const Row &row, const Column &column);
};

#endif //CPPKATAS_TICTACTOE_H