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

		SECTION("Position should")
		{
			SECTION("update x or y when moving")
			{
				Position position(1, 1);

				SECTION("north")
				{
					Position finalPosition(1, 2);

					auto newPosition = position.Move(Direction::North);

					REQUIRE(newPosition == finalPosition);
				}

				SECTION("south")
				{
					Position finalPosition(1, 0);

					auto newPosition = position.Move(Direction::South);

					REQUIRE(newPosition == finalPosition);
				}

				SECTION("east")
				{
					Position finalPosition(2, 1);

					auto newPosition = position.Move(Direction::East);

					REQUIRE(newPosition == finalPosition);
				}

				SECTION("west")
				{
					Position finalPosition(-1, 1);

					auto newPosition = position.Move(Direction::West);
					auto newPosition1 = newPosition.Move(Direction::West);

					REQUIRE(newPosition1 == finalPosition);
				}
			}
		}

		SECTION("Rover should")
		{
			Plateau plateau(1, 1);
			Position position(0, 0);

			SECTION("turn right")
			{
				SECTION("from North to East")
				{
					Rover rover(plateau, position, Direction::North);
					Rover finalRover(plateau, position, Direction::East);
					rover.TurnRight();

					REQUIRE(rover == finalRover);
				}
				SECTION("from East to South")
				{
					Rover rover(plateau, position, Direction::East);
					Rover finalRover(plateau, position, Direction::South);
					rover.TurnRight();

					REQUIRE(rover == finalRover);
				}

				SECTION("from South to West")
				{
					Rover rover(plateau, position, Direction::South);
					Rover finalRover(plateau, position, Direction::West);
					rover.TurnRight();

					REQUIRE(rover == finalRover);
				}

				SECTION("from West to North")
				{
					Rover rover(plateau, position, Direction::West);
					Rover finalRover(plateau, position, Direction::North);
					rover.TurnRight();

					REQUIRE(rover == finalRover);
				}
			}

			SECTION("turn left")
			{
				SECTION("from North to West")
				{
					Rover rover(plateau, position, Direction::North);
					Rover finalRover(plateau, position, Direction::West);
					rover.TurnLeft();

					REQUIRE(rover == finalRover);
				}
				SECTION("from West to South")
				{
					Rover rover(plateau, position, Direction::West);
					Rover finalRover(plateau, position, Direction::South);
					rover.TurnLeft();

					REQUIRE(rover == finalRover);
				}

				SECTION("from South to East")
				{
					Rover rover(plateau, position, Direction::South);
					Rover finalRover(plateau, position, Direction::East);
					rover.TurnLeft();

					REQUIRE(rover == finalRover);
				}

				SECTION("from East to North")
				{
					Rover rover(plateau, position, Direction::East);
					Rover finalRover(plateau, position, Direction::North);
					rover.TurnLeft();

					REQUIRE(rover == finalRover);
				}
			}

			SECTION("Move")
			{
				SECTION("North")
				{
					Rover rover(plateau, position, Direction::North);
					Rover finalRover(plateau, Position(0, 1), Direction::North);
					rover.Move();

					REQUIRE(rover == finalRover);
				}
				SECTION("South")
				{
					Rover rover(plateau, position, Direction::South);
					Rover finalRover(plateau, Position(0, -1), Direction::South);
					rover.Move();

					REQUIRE(rover == finalRover);
				}

				SECTION("West")
				{
					Rover rover(plateau, position, Direction::West);
					Rover finalRover(plateau, Position(-1, 0), Direction::West);
					rover.Move();

					REQUIRE(rover == finalRover);
				}

				SECTION("East")
				{
					Rover rover(plateau, position, Direction::East);
					Rover finalRover(plateau, Position(1, 0), Direction::East);
					rover.Move();

					REQUIRE(rover == finalRover);
				}
			}
		}

		SECTION("Grid size command should")
		{
			Mock<Rover> rover;
			Fake(Method(rover, InitializeGridSize));

			SECTION("initialize grid on rover")
			{
				GridSizeCommand command(0, 0);
				command.Execute(&rover.get());

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
				command.Execute(&rover.get());

				Verify(Method(rover, InitializePosition));
			}
		}

		SECTION("Direction command should")
		{
			Mock<Rover> rover;
			Fake(Method(rover, InitializeDirection));

			SECTION("initialize direction on rover")
			{
				DirectionCommand command(Direction::West);
				command.Execute(&rover.get());

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
				command.Execute(&rover.get());

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
				command.Execute(&rover.get());

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
				command.Execute(&rover.get());

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
				commands.Execute(&rover.get());

				Verify(Method(rover, InitializeGridSize));
			}

			SECTION("store position instruction")
			{
				Commands commands;

				commands.AddPositionCommand(0, 0);
				commands.Execute(&rover.get());

				Verify(Method(rover, InitializePosition));
			}

			SECTION("store direction instruction")
			{
				Commands commands;

				commands.AddDirectionCommand(Direction::North);
				commands.Execute(&rover.get());

				Verify(Method(rover, InitializeDirection));
			}

			SECTION("store turn left instruction")
			{
				Commands commands;

				commands.AddTurnLeftCommand();
				commands.Execute(&rover.get());

				Verify(Method(rover, TurnLeft));
			}	

			SECTION("store turn right instruction")
			{
				Commands commands;

				commands.AddTurnRightCommand();
				commands.Execute(&rover.get());

				Verify(Method(rover, TurnRight));
			}

			SECTION("store move instruction")
			{
				Commands commands;

				commands.AddMoveCommand();
				commands.Execute(&rover.get());

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
				commands->Execute(&rover.get());

				Verify(Method(rover, InitializeGridSize));
			}

			SECTION("parse position instruction")
			{
				InstructionParser parser;

				auto commands = parser.Parse("5 5\n1 1 W\nL");
				commands->Execute(&rover.get());

				Verify(Method(rover, InitializePosition));
			}

			SECTION("parse direction instruction")
			{
				InstructionParser parser;

				auto commands = parser.Parse("5 5\n1 1 W\nL");
				commands->Execute(&rover.get());

				Verify(Method(rover, InitializeDirection));
			}

			SECTION("parse turn left instruction")
			{
				InstructionParser parser;

				auto commands = parser.Parse("5 5\n1 1 W\nL");
				commands->Execute(&rover.get());

				Verify(Method(rover, TurnLeft));
			}

			SECTION("parse turn right instruction")
			{
				InstructionParser parser;

				auto commands = parser.Parse("5 5\n1 1 W\nR");
				commands->Execute(&rover.get());

				Verify(Method(rover, TurnRight));
			}

			SECTION("parse move instruction")
			{
				InstructionParser parser;

				auto commands = parser.Parse("5 5\n1 1 W\nM");
				commands->Execute(&rover.get());

				Verify(Method(rover, Move));
			}

			SECTION("parse multiple turn instructions")
			{
				InstructionParser parser;

				auto commands = parser.Parse("5 5\n1 1 W\nLRM");
				commands->Execute(&rover.get());

				Verify(Method(rover, TurnLeft));
				Verify(Method(rover, TurnRight));
				Verify(Method(rover, Move));
			}
		}
	}

	SECTION("Acceptance Tests")
	{
		GIVEN("a grid of 5 by 5")
		{
			auto gridSize = "5 5";

			GIVEN("a starting position of 1 1 N")
			{
				auto startPosition = "1 1 N";

				WHEN("the commands L are executed")
				{
					auto commands = "L";

					THEN("Then the final position should be 1 1 W")
					{
						auto endPosition = "1 1 W";

						stringstream instructions;
						instructions << gridSize << endl << startPosition << endl << commands << ends;

						Rover rover;
						rover.Execute(instructions.str());

						REQUIRE(rover.Execute(instructions.str()) == endPosition);
					}
				}
			}
		}

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

						REQUIRE(rover.Execute(instructions.str()) == endPosition);
					}
				}
			}
		}
	}
}