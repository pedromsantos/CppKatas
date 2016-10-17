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

	SECTION("Player cannot play in any previous played position")
	{
		game->PlayTurn(X, TOP, LEFT);
		game->PlayTurn(O, TOP, CENTER);
		REQUIRE(game->PlayTurn(X, TOP, LEFT) == InvalidPosition);
	}

	SECTION("Player X wins if it fills all columns in top row")
	{
		game->PlayTurn(X, TOP, LEFT);
		game->PlayTurn(O, MIDLDE, CENTER);
		game->PlayTurn(X, TOP, CENTER);
		game->PlayTurn(O, MIDLDE, LEFT);
		REQUIRE(game->PlayTurn(X, TOP, RIGHT) == Win);
	}

	SECTION("Player X wins if it fills all columns middle row")
	{
		game->PlayTurn(X, MIDLDE, LEFT);
		game->PlayTurn(O, BOTTOM, CENTER);
		game->PlayTurn(X, MIDLDE, CENTER);
		game->PlayTurn(O, BOTTOM, LEFT);
		REQUIRE(game->PlayTurn(X, MIDLDE, RIGHT) == Win);
	}

	SECTION("Player X wins if it fills all columns bottom row")
	{
		game->PlayTurn(X, BOTTOM, LEFT);
		game->PlayTurn(O, MIDLDE, CENTER);
		game->PlayTurn(X, BOTTOM, CENTER);
		game->PlayTurn(O, MIDLDE, LEFT);
		REQUIRE(game->PlayTurn(X, BOTTOM, RIGHT) == Win);
	}

	SECTION("Player X wins if it fills all rows in left column")
	{
		game->PlayTurn(X, TOP, LEFT);
		game->PlayTurn(O, MIDLDE, CENTER);
		game->PlayTurn(X, MIDLDE, LEFT);
		game->PlayTurn(O, MIDLDE, RIGHT);
		REQUIRE(game->PlayTurn(X, BOTTOM, LEFT) == Win);
	}

	SECTION("Player X wins if it fills all rows in center column")
	{
		game->PlayTurn(X, TOP, CENTER);
		game->PlayTurn(O, MIDLDE, LEFT);
		game->PlayTurn(X, MIDLDE, CENTER);
		game->PlayTurn(O, MIDLDE, RIGHT);
		REQUIRE(game->PlayTurn(X, BOTTOM, CENTER) == Win);
	}

	SECTION("Player X wins if it fills all rows in rigth column")
	{
		game->PlayTurn(X, TOP, RIGHT);
		game->PlayTurn(O, MIDLDE, LEFT);
		game->PlayTurn(X, MIDLDE, RIGHT);
		game->PlayTurn(O, MIDLDE, CENTER);
		REQUIRE(game->PlayTurn(X, BOTTOM, RIGHT) == Win);
	}
}