#include "catch.hpp"
#include "fakeit.hpp"

#include "../src/MarsRover/MarsRover.hpp"
#include "../src/MarsRover/Commands.hpp"

using namespace std;

TEST_CASE("Mars Rover", "[Mars Rover]")
{
	SECTION("Unit Tests")
	{
		using namespace fakeit;

		SECTION("Grid size command should")
		{
			Mock<Rover> rover;
			Fake(Method(rover, InitializeGridSize));

			SECTION("initialize grid on rover")
			{
				GridSizeCommand command(0, 0);
				command.Execute(rover.get());

				Verify(Method(rover, InitializeGridSize));
			}
		}

		SECTION("Position command should")
		{
			Mock<Rover> rover;
			Fake(Method(rover, InitializePosition));

			SECTION("initialize position on rover")
			{
				PositionCommand command(0, 0);
				command.Execute(rover.get());

				Verify(Method(rover, InitializePosition));
			}
		}

		SECTION("Commands should")
		{
			Mock<Rover> rover;
			Fake(Method(rover, InitializeGridSize));
			Fake(Method(rover, InitializePosition));

			SECTION("store grid size instruction")
			{
				Commands commands;	

				commands.AddGridSizeCommand(0, 0);
				commands.ExecuteNext(rover.get());

				Verify(Method(rover, InitializeGridSize));
			}

			SECTION("store position instruction")
			{
				Commands commands;

				commands.AddPositionCommand(0, 0);
				commands.ExecuteNext(rover.get());

				Verify(Method(rover, InitializePosition));
			}
		}

		SECTION("Instruction parser should")
		{
			Mock<Rover> rover;
			Fake(Method(rover, InitializeGridSize));
			Fake(Method(rover, InitializePosition));

			SECTION("Parse grid size instruction")
			{
				InstructionParser parser;

				auto commands = parser.Parse("5 5");
				commands->ExecuteNext(rover.get());

				Verify(Method(rover, InitializeGridSize));
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

						Rover rover;
						rover.Execute(instructions.str());

						//REQUIRE(rover.Execute(instructions.str()) == endPosition);
					}
				}
			}
		}
	}
}