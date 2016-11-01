#ifndef CPPKATAS_TICTACTOE_H
#define CPPKATAS_TICTACTOE_H

#include <vector>

enum TurnStatus
{
    InProgress,
    InvalidPlayer,
    InvalidPosition,
    Win
};

enum Player
{
    X,
    O,
    NONE
};

enum Row
{
    TOP = 0,
    MIDLDE = 1,
    BOTTOM = 2
};

enum Column
{
    LEFT = 0,
    CENTER = 1,
    RIGHT = 2
};

class TicTacToe
{
    Player lastPlayer = O;

    const std::vector<std::vector<Player>> starting_turns{{NONE, NONE, NONE}, {NONE, NONE, NONE}, {NONE, NONE, NONE}};
    std::vector<std::vector<Player>> turns = starting_turns;

	void SaveTurn(const Player &player, const Row &row, const Column &column);
    bool IsPositionTaken(const Row &row, const Column &column) const; 
    bool IsPlayerInvalid(const Player &player) const;
    bool IsWinner(const Player &player) const;
    bool WinnerOnColumns(const Player &player) const;
    bool WinnerOnRows(const Player &player) const;
    bool WinnerOnDiagonal(const Player &player, Column start, Column end) const;

  public:
    TurnStatus PlayTurn(const Player &player, const Row &row, const Column &column);
};

#endif //CPPKATAS_TICTACTOE_H