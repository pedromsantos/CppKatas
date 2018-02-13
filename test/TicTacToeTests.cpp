#include "catch.hpp"
#include "../src/TicTacToe.hpp"

SCENARIO("Play game of tic tac toe", "[TicTacToe]")
{
    GIVEN("A tic tac toe game")
    {
        std::unique_ptr<TicTacToe> game = std::make_unique<TicTacToe>();

        WHEN("its the first move")
        {
            THEN("player X can play")
            {
                REQUIRE(game->PlayTurn(X, TOP, LEFT) == InProgress);
            }
        }

        WHEN("its the first move")
        {
            THEN("player O cannot play")
            {
                REQUIRE(game->PlayTurn(O, TOP, LEFT) == InvalidPlayer);
            }
        }

        WHEN("its the second move")
        {
            game->PlayTurn(X, TOP, LEFT);

            THEN("player O can play")
            {
                REQUIRE(game->PlayTurn(O, MIDDLE, LEFT) == InProgress);
            }
        }

        WHEN("players do not alternate")
        {
            game->PlayTurn(X, TOP, LEFT);

            THEN("it signals an invalid player")
            {
                REQUIRE(game->PlayTurn(X, MIDDLE, LEFT) == InvalidPlayer);
            }
        }

        WHEN("player plays in same position as previous player")
        {
            game->PlayTurn(X, TOP, LEFT);

            THEN("it signals an invalid position")
            {
                REQUIRE(game->PlayTurn(O, TOP, LEFT) == InvalidPosition);
            }
        }

        WHEN("player plays in any played positions")
        {
            game->PlayTurn(X, TOP, LEFT);
            game->PlayTurn(O, TOP, CENTER);

            THEN("it signals an invalid position")
            {
                REQUIRE(game->PlayTurn(X, TOP, LEFT) == InvalidPosition);
            }
        }

        WHEN("player X fills all columns in top row")
        {
            game->PlayTurn(X, TOP, LEFT);
            game->PlayTurn(O, MIDDLE, CENTER);
            game->PlayTurn(X, TOP, CENTER);
            game->PlayTurn(O, MIDDLE, LEFT);

            THEN("player X wins")
            {
                REQUIRE(game->PlayTurn(X, TOP, RIGHT) == Win);
            }
        }

        WHEN("player X fills all columns middle row")
        {
            game->PlayTurn(X, MIDDLE, LEFT);
            game->PlayTurn(O, BOTTOM, CENTER);
            game->PlayTurn(X, MIDDLE, CENTER);
            game->PlayTurn(O, BOTTOM, LEFT);

            THEN("player X wins")
            {
                REQUIRE(game->PlayTurn(X, MIDDLE, RIGHT) == Win);
            }
        }

        WHEN("player X fills all columns bottom row")
        {
            game->PlayTurn(X, BOTTOM, LEFT);
            game->PlayTurn(O, MIDDLE, CENTER);
            game->PlayTurn(X, BOTTOM, CENTER);
            game->PlayTurn(O, MIDDLE, LEFT);

            THEN("player X wins")
            {
                REQUIRE(game->PlayTurn(X, BOTTOM, RIGHT) == Win);
            }
        }

        WHEN("player X fills all rows in left column")
        {
            game->PlayTurn(X, TOP, LEFT);
            game->PlayTurn(O, MIDDLE, CENTER);
            game->PlayTurn(X, MIDDLE, LEFT);
            game->PlayTurn(O, MIDDLE, RIGHT);

            THEN("player X wins")
            {
                REQUIRE(game->PlayTurn(X, BOTTOM, LEFT) == Win);
            }
        }

        WHEN("player X fills all rows in center column")
        {
            game->PlayTurn(X, TOP, CENTER);
            game->PlayTurn(O, MIDDLE, LEFT);
            game->PlayTurn(X, MIDDLE, CENTER);
            game->PlayTurn(O, MIDDLE, RIGHT);

            THEN("player X wins")
            {
                REQUIRE(game->PlayTurn(X, BOTTOM, CENTER) == Win);
            }
        }

        WHEN("player X fills all rows in right column")
        {
            game->PlayTurn(X, TOP, RIGHT);
            game->PlayTurn(O, MIDDLE, LEFT);
            game->PlayTurn(X, MIDDLE, RIGHT);
            game->PlayTurn(O, MIDDLE, CENTER);

            THEN("player X wins")
            {
                REQUIRE(game->PlayTurn(X, BOTTOM, RIGHT) == Win);
            }
        }

        WHEN("pPlayer X has three in left to right diagonal")
        {
            game->PlayTurn(X, TOP, LEFT);
            game->PlayTurn(O, TOP, CENTER);
            game->PlayTurn(X, MIDDLE, CENTER);
            game->PlayTurn(O, TOP, RIGHT);

            THEN("player X wins")
            {
                REQUIRE(game->PlayTurn(X, BOTTOM, RIGHT) == Win);
            }
        }

        WHEN("player X has three in right to left diagonal")
        {
            game->PlayTurn(X, TOP, RIGHT);
            game->PlayTurn(O, TOP, CENTER);
            game->PlayTurn(X, MIDDLE, CENTER);
            game->PlayTurn(O, TOP, LEFT);

            THEN("player X wins")
            {
                REQUIRE(game->PlayTurn(X, BOTTOM, LEFT) == Win);
            }
        }
    }
}