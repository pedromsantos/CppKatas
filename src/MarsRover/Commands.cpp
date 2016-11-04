#include "MarsRover.hpp"
#include "Commands.hpp"

void Commands::AddGridSizeCommand(int width, int heigth)
{
	auto command = make_unique<GridSizeCommand>(width, heigth);
	commands.push_back(move(command));
}

void Commands::ExecuteNext(Rover& rover)
{
	commands.front()->Execute(rover);
}

void GridSizeCommand::Execute(Rover& rover)
{
	rover.InitializeGridSize(width_, heigth_);
}