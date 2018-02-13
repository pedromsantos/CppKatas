#include "TicTacToe.hpp"

struct InvalidPlayerException : public std::exception {
  const char *what() const throw() override { return "Invalid player turn"; }
};

struct InvalidPositionException : public std::exception {
  const char *what() const throw() override {
    return "Position has already been played";
  }
};

struct Board::BoardImpl {
  const std::vector<std::vector<Player>> starting_turns{
      {NONE, NONE, NONE}, {NONE, NONE, NONE}, {NONE, NONE, NONE}};

  std::vector<std::vector<Player>> turns = starting_turns;

  bool PositionIsTaken(const Row &row, const Column &column) const;
  bool WinnerOnColumns(const Player &player) const;
  bool WinnerOnRows(const Player &player) const;
  bool WinnerOnDiagonals(const Player &player, Column start, Column end) const;
  void SaveTurn(const Player &player, const Row &row, const Column &column);
};

bool Board::BoardImpl::WinnerOnRows(const Player &player) const {
  for (const auto row : {TOP, MIDDLE, BOTTOM}) {
    if (player == turns[row][LEFT] && player == turns[row][CENTER] &&
        player == turns[row][RIGHT]) {
      return true;
    }
  }
  return false;
}

bool Board::BoardImpl::WinnerOnColumns(const Player &player) const {
  for (const auto column : {LEFT, CENTER, RIGHT}) {
    if (player == turns[TOP][column] && player == turns[MIDDLE][column] &&
        player == turns[BOTTOM][column]) {
      return true;
    }
  }
  return false;
}

bool Board::BoardImpl::WinnerOnDiagonals(const Player &player, Column start,
                                         Column end) const {
  return (player == turns[TOP][start] && player == turns[MIDDLE][CENTER] &&
          player == turns[BOTTOM][end]);
}

bool Board::BoardImpl::PositionIsTaken(const Row &row,
                                       const Column &column) const {
  return turns[row][column] != NONE;
}

void Board::BoardImpl::SaveTurn(const Player &player, const Row &row,
                                const Column &column) {
  if (PositionIsTaken(row, column)) {
    throw InvalidPositionException();
  }

  turns[row][column] = player;
}

void Board::SaveTurn(const Player &player, const Row &row,
                     const Column &column) {
  pimpl->SaveTurn(player, row, column);
}

bool Board::IsWinner(const Player &player) const {
  return pimpl->WinnerOnRows(player) || pimpl->WinnerOnColumns(player) ||
         pimpl->WinnerOnDiagonals(player, LEFT, RIGHT) ||
         pimpl->WinnerOnDiagonals(player, RIGHT, LEFT);
}

Board::Board() : pimpl(new BoardImpl()) {}

Board::~Board() = default;
Board::Board(Board && op) noexcept = default;
Board& Board::operator=(Board && op) noexcept = default;

struct TicTacToe::TicTacToeImpl {
  std::unique_ptr<Board> board_;
  Player lastPlayer_ = O;

  bool IsWinner(const Player &player) const;
  void SaveTurn(const Player &player, const Row &row, const Column &column);
};

bool TicTacToe::TicTacToeImpl::IsWinner(const Player &player) const {
  return board_->IsWinner(player);
}

void TicTacToe::TicTacToeImpl::SaveTurn(const Player &player, const Row &row,
                                        const Column &column) {
  if (player == lastPlayer_) {
    throw InvalidPlayerException();
  }

  lastPlayer_ = player;

  return board_->SaveTurn(player, row, column);
}

TicTacToe::TicTacToe() : TicTacToe(std::make_unique<Board>()) {}

TicTacToe::TicTacToe(std::unique_ptr<Board> &&board)
    : pimpl(new TicTacToeImpl()) {
  pimpl->board_ = std::move(board);
}

TicTacToe::~TicTacToe() = default;
TicTacToe::TicTacToe(TicTacToe && op) noexcept = default;
TicTacToe& TicTacToe::operator=(TicTacToe && op) noexcept = default;

TurnStatus TicTacToe::PlayTurn(const Player &player, const Row &row,
                               const Column &column) throw() {
  try {
    pimpl->SaveTurn(player, row, column);
  } catch (InvalidPositionException &exception) {
    return TurnStatus::InvalidPosition;
  } catch (InvalidPlayerException &exception) {
    return TurnStatus::InvalidPlayer;
  }

  if (pimpl->IsWinner(player)) {
    return TurnStatus::Win;
  }

  return TurnStatus::InProgress;
}