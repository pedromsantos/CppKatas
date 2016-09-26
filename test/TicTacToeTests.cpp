#include "catch.hpp"
#include "../src/TicTacToe.h"

TEST_CASE("Play game of tic tac toe", "[TicTacToe]")
{
    auto game = new TicTacToe();

    SECTION( "Player X plays first" )
    {
        REQUIRE(game->PlayTurn(X, TOP, LEFT) == InProgress);
    }

    SECTION( "Player O cannot play first" )
    {
        REQUIRE(game->PlayTurn(O, TOP, LEFT) == InvalidPlayer);
    }

    SECTION( "Player O plays second" )
    {
        game->PlayTurn(X, TOP, LEFT);
        REQUIRE(game->PlayTurn(O, MIDLDE, LEFT) == InProgress);
    }

    SECTION( "Players must alternate" )
    {
        game->PlayTurn(X, TOP, LEFT);
        REQUIRE(game->PlayTurn(X, MIDLDE, LEFT) == InvalidPlayer);
    }

    SECTION( "Player cannot play in same position as previous player" )
    {
        game->PlayTurn(X, TOP, LEFT);
        REQUIRE(game->PlayTurn(O, TOP, LEFT) == InvalidPosition);
    }
}
