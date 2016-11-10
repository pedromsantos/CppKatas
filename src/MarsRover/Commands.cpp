#include "Commands.hpp"
#include "MarsRover.hpp"

struct GridSizeCommand::PImpl
{
	int width_;
	int heigth_;
};

GridSizeCommand::GridSizeCommand(int width, int heigth) : pimpl(new PImpl())
{
	pimpl->width_ = width;
	pimpl->heigth_ = heigth;
}

void GridSizeCommand::Execute(Rover* rover)
{
	rover->InitializeGridSize(pimpl->width_, pimpl->heigth_);
}

GridSizeCommand::~GridSizeCommand()
{}

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