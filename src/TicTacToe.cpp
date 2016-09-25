#include "TicTacToe.h"

const TurnStatus TicTacToe::PlayTurn(const Player player)
{
    if(player == lastPlayer)
    {
        return InvalidPlayer;
    }

    lastPlayer = player;

    return InProgress;
}