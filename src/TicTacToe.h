#ifndef CPPKATAS_TICTACTOE_H
#define CPPKATAS_TICTACTOE_H

enum Player { X, O };

enum TurnStatus { InProgress, InvalidPlayer };

class TicTacToe
{
    Player lastPlayer = O;

public:
    const TurnStatus PlayTurn(const Player player);
};

#endif //CPPKATAS_TICTACTOE_H