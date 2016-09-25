#include "catch.hpp"
#include "../src/TicTacToe.cpp"

TEST_CASE("Play game of tic tac toe", "[TicTacToe]")
{
    auto game = new TicTacToe();

    SECTION( "Player X plays first" )
    {
        REQUIRE(game->PlayTurn(X) == InProgress);
    }

    SECTION( "Player O cannot play first" )
    {
        REQUIRE(game->PlayTurn(O) == InvalidPlayer);
    }

    SECTION( "Player O plays second" )
    {
        game->PlayTurn(X);
        REQUIRE(game->PlayTurn(O) == InProgress);
    }
}
