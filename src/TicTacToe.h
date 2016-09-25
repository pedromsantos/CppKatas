#ifndef CPPKATAS_TICTACTOE_H
#define CPPKATAS_TICTACTOE_H

#import <vector>

enum Player { X, O };

enum TurnStatus { InProgress, InvalidPlayer, InvalidPosition };

enum Row { TOP, MIDLDE, BOTTOM};

enum Column { LEFT, CENTER, RIGHT};

class Turn
{
private:
    Player player;
    Row row;
    Column column;

public:
    Turn(const Player player, const Row row, const Column column);

    bool IsSamePosition(const Row row, const Column column);

    bool IsSamePlayer(const Player player);
};

class TicTacToe
{
    std::vector<Turn> turns;

public:
    const TurnStatus PlayTurn(const Player player, const Row row, const Column column);

    bool IsFirstTurn() const;

    bool IsPositionTaken(const Row &row, const Column &column) const;
};

#endif //CPPKATAS_TICTACTOE_H