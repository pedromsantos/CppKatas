#include "Commands.hpp"
#include "MarsRover.hpp"

void Commands::Execute(Rover* rover)
{
	for (auto const& command : commands)
	{
		command->Execute(rover);
	}
}

void Commands::AddCommand(std::unique_ptr<Command>&& command)
{
	commands.push_back(std::move(command));
}

void GridSizeCommand::Execute(Rover* rover)
{
	rover->InitializeGridSize(width_, heigth_);
}

void PositionCommand::Execute(Rover* rover)
{
	rover->InitializePosition(x_, y_);
}

void DirectionCommand::Execute(Rover* rover)
{
	rover->InitializeDirection(direction_);
}

void TurnLeftCommand::Execute(Rover* rover)
{
	rover->TurnLeft();
}

void TurnRightCommand::Execute(Rover* rover)
{
	rover->TurnRight();
}

void MoveCommand::Execute(Rover* rover)
{
	rover->Move();
}