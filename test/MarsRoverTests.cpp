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

		SECTION("Direction command should")
		{
			Mock<Rover> rover;
			Fake(Method(rover, InitializeDirection));

			SECTION("initialize direction on rover")
			{
				DirectionCommand command(West);
				command.Execute(rover.get());

				Verify(Method(rover, InitializeDirection));
			}
		}

		SECTION("Turn left command should")
		{
			Mock<Rover> rover;
			Fake(Method(rover, TurnLeft));

			SECTION("turn rover left")
			{
				TurnLeftCommand command;
				command.Execute(rover.get());

				Verify(Method(rover, TurnLeft));
			}
		}

		SECTION("Turn right command should")
		{
			Mock<Rover> rover;
			Fake(Method(rover, TurnRight));

			SECTION("turn rover right")
			{
				TurnRightCommand command;
				command.Execute(rover.get());

				Verify(Method(rover, TurnRight));
			}
		}

		SECTION("Move command should")
		{
			Mock<Rover> rover;
			Fake(Method(rover, Move));

			SECTION("move rover forward")
			{
				MoveCommand command;
				command.Execute(rover.get());

				Verify(Method(rover, Move));
			}
		}

		SECTION("Commands should")
		{
			Mock<Rover> rover;
			Fake(Method(rover, InitializeGridSize));
			Fake(Method(rover, InitializePosition));
			Fake(Method(rover, InitializeDirection));
			Fake(Method(rover, TurnLeft));
			Fake(Method(rover, TurnRight));
			Fake(Method(rover, Move));

			SECTION("store grid size instruction")
			{
				Commands commands;	

				commands.AddGridSizeCommand(0, 0);
				commands.Execute(rover.get());

				Verify(Method(rover, InitializeGridSize));
			}

			SECTION("store position instruction")
			{
				Commands commands;

				commands.AddPositionCommand(0, 0);
				commands.Execute(rover.get());

				Verify(Method(rover, InitializePosition));
			}

			SECTION("store direction instruction")
			{
				Commands commands;

				commands.AddDirectionCommand(North);
				commands.Execute(rover.get());

				Verify(Method(rover, InitializeDirection));
			}

			SECTION("store turn left instruction")
			{
				Commands commands;

				commands.AddTurnLeftCommand();
				commands.Execute(rover.get());

				Verify(Method(rover, TurnLeft));
			}	

			SECTION("store turn right instruction")
			{
				Commands commands;

				commands.AddTurnRightCommand();
				commands.Execute(rover.get());

				Verify(Method(rover, TurnRight));
			}

			SECTION("store move instruction")
			{
				Commands commands;

				commands.AddMoveCommand();
				commands.Execute(rover.get());

				Verify(Method(rover, Move));
			}
		}

		SECTION("Instruction parser should")
		{
			Mock<Rover> rover;
			Fake(Method(rover, InitializeGridSize));
			Fake(Method(rover, InitializePosition));
			Fake(Method(rover, InitializeDirection));
			Fake(Method(rover, TurnLeft));
			Fake(Method(rover, TurnRight));
			Fake(Method(rover, Move));

			SECTION("parse grid size instruction")
			{
				InstructionParser parser;

				auto commands = parser.Parse("5 5\n1 1 W\nL");
				commands->Execute(rover.get());

				Verify(Method(rover, InitializeGridSize));
			}

			SECTION("parse position instruction")
			{
				InstructionParser parser;

				auto commands = parser.Parse("5 5\n1 1 W\nL");
				commands->Execute(rover.get());

				Verify(Method(rover, InitializePosition));
			}

			SECTION("parse direction instruction")
			{
				InstructionParser parser;

				auto commands = parser.Parse("5 5\n1 1 W\nL");
				commands->Execute(rover.get());

				Verify(Method(rover, InitializeDirection));
			}

			SECTION("parse turn left instruction")
			{
				InstructionParser parser;

				auto commands = parser.Parse("5 5\n1 1 W\nL");
				commands->Execute(rover.get());

				Verify(Method(rover, TurnLeft));
			}

			SECTION("parse turn right instruction")
			{
				InstructionParser parser;

				auto commands = parser.Parse("5 5\n1 1 W\nR");
				commands->Execute(rover.get());

				Verify(Method(rover, TurnRight));
			}

			SECTION("parse move instruction")
			{
				InstructionParser parser;

				auto commands = parser.Parse("5 5\n1 1 W\nM");
				commands->Execute(rover.get());

				Verify(Method(rover, Move));
			}

			SECTION("parse multiple turn instructions")
			{
				InstructionParser parser;

				auto commands = parser.Parse("5 5\n1 1 W\nLR");
				commands->Execute(rover.get());

				Verify(Method(rover, TurnLeft));
				Verify(Method(rover, TurnRight));
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