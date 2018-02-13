#include "Commands.hpp"
#include "MarsRover.hpp"

struct GridSizeCommand::GridSizeCommandImpl
{
    int width_;
    int height_;

    GridSizeCommandImpl(int width, int height) {
        width_ = width;
        height_ = height;
    }
};

GridSizeCommand::GridSizeCommand(int width, int height)
        : pimpl(std::make_unique<GridSizeCommandImpl>(width, height))
{
}

GridSizeCommand::~GridSizeCommand() = default;
GridSizeCommand::GridSizeCommand(GridSizeCommand && op) noexcept = default;
GridSizeCommand& GridSizeCommand::operator=(GridSizeCommand && op) noexcept = default;

void GridSizeCommand::Execute(Rover &rover)
{
    rover.InitializeGridSize(std::make_unique<Plateau>(pimpl->width_, pimpl->height_));
}

struct PositionCommand::PositionCommandImpl
{
    int x_;
    int y_;

    PositionCommandImpl(int x, int y) {
        x_ = x;
        y_ = y;
    }
};

PositionCommand::PositionCommand(int x, int y)
        : pimpl(std::make_unique<PositionCommandImpl>(x, y))
{
}

PositionCommand::~PositionCommand() = default;
PositionCommand::PositionCommand(PositionCommand && op) noexcept = default;
PositionCommand& PositionCommand::operator=(PositionCommand && op) noexcept = default;

void PositionCommand::Execute(Rover &rover)
{
    rover.InitializePosition(std::make_unique<Position>(pimpl->x_, pimpl->y_));
}

struct DirectionCommand::DirectionCommandImpl
{
    Direction direction_;

    explicit DirectionCommandImpl(Direction direction)
    {
        direction_ = direction;
    }
};

DirectionCommand::DirectionCommand(Direction direction)
        : pimpl(std::make_unique<DirectionCommandImpl>(direction))
{
}

void DirectionCommand::Execute(Rover &rover)
{
    rover.InitializeDirection(pimpl->direction_);
}

DirectionCommand::~DirectionCommand() = default;
DirectionCommand::DirectionCommand(DirectionCommand && op) noexcept = default;
DirectionCommand& DirectionCommand::operator=(DirectionCommand && op) noexcept = default;

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
    std::vector<std::unique_ptr<Command>> commands;

    void AddCommand(std::unique_ptr<Command> &&command)
    {
        commands.push_back(std::move(command));
    }
};

Commands::Commands()
        : pimpl(std::make_unique<CommandsImpl>())
{
}

Commands::~Commands() = default;
Commands::Commands(Commands && op) noexcept = default;
Commands& Commands::operator=(Commands && op) noexcept = default;

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