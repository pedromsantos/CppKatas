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

GridSizeCommand::~GridSizeCommand()
{}

void GridSizeCommand::Execute(Rover* rover)
{
	rover->InitializeGridSize(pimpl->width_, pimpl->heigth_);
}

struct PositionCommand::PImpl
{
	int x_;
	int y_;
};

PositionCommand::PositionCommand(int x, int y) : pimpl(new PImpl())
{
	pimpl->x_ = x;
	pimpl->y_ = y;
}

PositionCommand::~PositionCommand()
{}

void PositionCommand::Execute(Rover* rover)
{
	rover->InitializePosition(pimpl->x_, pimpl->y_);
}

struct DirectionCommand::PImpl
{
	Direction direction_;
};

DirectionCommand::DirectionCommand(Direction direction) : pimpl(new PImpl())
{
	pimpl->direction_ = direction;
}

DirectionCommand::~DirectionCommand()
{
}

void DirectionCommand::Execute(Rover* rover)
{
	rover->InitializeDirection(pimpl->direction_);
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

struct Commands::PImpl
{
	std::vector<std::unique_ptr<Command >> commands;
};

Commands::Commands() : pimpl(new PImpl())
{}

Commands::~Commands()
{}

void Commands::Execute(Rover* rover) const
{
	for (auto const& command : pimpl->commands)
	{
		command->Execute(rover);
	}
}

void Commands::AddCommand(std::unique_ptr<Command>&& command)
{
	pimpl->commands.push_back(std::move(command));
}