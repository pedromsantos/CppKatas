#include "Commands.hpp"
#include "MarsRover.hpp"

struct GridSizeCommand::GridSizeCommandImpl
{
    int width_;
    int height_;
};

GridSizeCommand::GridSizeCommand(int width, int height) : pimpl(new GridSizeCommandImpl())
{
    pimpl->width_ = width;
    pimpl->height_ = height;
}

GridSizeCommand::~GridSizeCommand() = default;

void GridSizeCommand::Execute(Rover &rover)
{
    rover.InitializeGridSize(std::make_unique<Plateau>(pimpl->width_, pimpl->height_));
}

struct PositionCommand::Impl
{
    int x_;
    int y_;
};

PositionCommand::PositionCommand(int x, int y) : pimpl(new Impl())
{
    pimpl->x_ = x;
    pimpl->y_ = y;
}

PositionCommand::~PositionCommand() = default;

void PositionCommand::Execute(Rover &rover)
{
    rover.InitializePosition(std::make_unique<Position>(pimpl->x_, pimpl->y_));
}

struct DirectionCommand::DirectionCommandImpl
{
    Direction direction_;
};

DirectionCommand::DirectionCommand(Direction direction) : pimpl(new DirectionCommandImpl())
{
    pimpl->direction_ = direction;
}

DirectionCommand::~DirectionCommand() = default;

void DirectionCommand::Execute(Rover &rover)
{
    rover.InitializeDirection(pimpl->direction_);
}

void TurnLeftCommand::Execute(Rover &rover)
{
    rover.TurnLeft();
}

void TurnRightCommand::Execute(Rover &rover)
{
    rover.TurnRight();
}

void MoveCommand::Execute(Rover &rover)
{
    rover.Move();
}

struct Commands::CommandsImpl
{
    std::vector<std::unique_ptr<Command >> commands;

	void AddCommand(std::unique_ptr<Command> &&command)
	{
		commands.push_back(std::move(command));
	}
};

Commands::Commands() : pimpl(new CommandsImpl())
{}

Commands::~Commands() = default;

void Commands::Execute(Rover &rover) const
{
    for (auto const &command : pimpl->commands)
    {
        command->Execute(rover);
    }
}

void Commands::AddCommand(std::unique_ptr<Command> &&command) const
{
	pimpl->AddCommand(std::move(command));
}