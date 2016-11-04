#include "catch.hpp"
#include "fakeit.hpp"

#include "../src/MarsRover.hpp"

using namespace std;

TEST_CASE("Mars Rover", "[TicTacToe]")
{
	SECTION("Unit Tests")
	{
		using namespace fakeit;

		SECTION("Mars rover should")
		{
			SECTION("Parse instructions")
			{
				stringstream instructions;
				instructions << "5 5" << endl << "1 1 N" << endl << "LMLMLMLMM" << ends;

				Mock<InstructionParser> instructionParser;
				Fake(Method(instructionParser, Parse));

				Rover rover(instructionParser.get());
				rover.Execute(instructions.str());

				Verify(Method(instructionParser, Parse));
			}
		}
	}

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

						stringstream instructions;
						instructions << gridSize << endl << startPosition << endl << commands << ends;

						InstructionParser instructionParser;

						Rover rover(instructionParser);
						rover.Execute(instructions.str());

						REQUIRE(rover.Execute(instructions.str()) == endPosition);
					}
				}
			}
		}
	}
}