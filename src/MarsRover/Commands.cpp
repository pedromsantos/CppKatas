#include "MarsRover.hpp"
#include "Commands.hpp"

void Commands::ExecuteNext(Rover& rover)
{
	commands.front()->Execute(rover);
}

void Commands::AddGridSizeCommand(int width, int heigth)
{
	auto command = make_unique<GridSizeCommand>(width, heigth);
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