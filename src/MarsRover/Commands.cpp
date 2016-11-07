#include "MarsRover.hpp"
#include "Commands.hpp"

void Commands::Execute(Rover& rover)
{
	for (auto const& command : commands)
	{
		command->Execute(rover);
	}
}

void Commands::AddGridSizeCommand(int width, int heigth)
{
	auto command = make_unique<GridSizeCommand>(width, heigth);
	commands.push_back(move(command));
}

void Commands::AddPositionCommand(int x, int y)
{
	auto command = make_unique<PositionCommand>(x, y);
	commands.push_back(move(command));
}

void Commands::AddDirectionCommand(Direction direction)
{
	auto command = make_unique<DirectionCommand>(direction);
	commands.push_back(move(command));
}

void GridSizeCommand::Execute(Rover& rover)
{
	rover.InitializeGridSize(width_, heigth_);
}

void PositionCommand::Execute(Rover& rover)
{
	rover.InitializePosition(x_, y_);
}

void DirectionCommand::Execute(Rover& rover)
{
	rover.InitializeDirection(direction_);
}

void TurnLeftCommand::Execute(Rover& rover)
{
	rover.TurnLeft();
}