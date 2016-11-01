#include "test/catch.hpp"
#include "MarsRover.hpp"

TEST_CASE("Mars Rover Tests", "[TicTacToe]")
{
	SECTION("Acceptance Tests")
	{
		GIVEN("a grid of 5 by 5")
		{
			auto gridSize = "5 5";

			GIVEN("a starting position of 1 2 N")
			{
				auto startPosition = "1 2 N";

				WHEN("the commands LMLMLMLMM are executed")
				{
					auto commands = "LMLMLMLMM";

					THEN("Then the final position should be 1 3 N")
					{
						auto endPosition = "1 3 N";

						std::stringstream instructions;
						instructions << gridSize << std::endl << startPosition << std::endl << commands << std::ends;

						auto rover = std::make_unique<Rover>();

						REQUIRE(rover->Execute(instructions.str()) == endPosition);
					}
				}
			}
		}
	}
}