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
    MIDDLE = 1,
    BOTTOM = 2
};

enum Column
{
    LEFT = 0,
    CENTER = 1,
    RIGHT = 2
};

class Board
{
private:
    struct BoardImpl;
    std::unique_ptr<BoardImpl> pimpl;

public:

    Board();
    virtual ~Board();

    Board(Board && op) noexcept;
    Board& operator=(Board && op) noexcept;

    bool IsWinner(const Player &player) const;
    void SaveTurn(const Player &player, const Row &row, const Column &column);
};

class TicTacToe
{
public:
    TicTacToe();
    virtual ~TicTacToe();

    TicTacToe(TicTacToe && op) noexcept;
    TicTacToe& operator=(TicTacToe && op) noexcept;

    TurnStatus PlayTurn(const Player &player, const Row &row, const Column &column) throw();

private:
    struct TicTacToeImpl;
    std::unique_ptr<TicTacToeImpl> pimpl;

    explicit TicTacToe(std::unique_ptr<Board>&& board);
};

#endif //CPPKATAS_TICTACTOE_H