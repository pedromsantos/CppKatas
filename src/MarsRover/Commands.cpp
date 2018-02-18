#include "Commands.hpp"
#include "MarsRover.hpp"

struct GridSizeCommand::GridSizeCommandImpl
{
    int width_;
    int height_;

    GridSizeCommandImpl(const int width, const int height);
};

GridSizeCommand::GridSizeCommandImpl::GridSizeCommandImpl(const int width, const int height)
{
    width_ = width;
    height_ = height;
}

GridSizeCommand::GridSizeCommand(const int width, const int height)
        : pimpl(std::make_unique<GridSizeCommandImpl>(width, height))
{
}

GridSizeCommand::~GridSizeCommand() = default;

GridSizeCommand::GridSizeCommand(GridSizeCommand &&) noexcept = default;

GridSizeCommand &GridSizeCommand::operator=(GridSizeCommand &&) noexcept = default;

void GridSizeCommand::Execute(Rover &rover) const
{
    rover.InitializeGridSize(std::make_unique<Plateau>(pimpl->width_, pimpl->height_));
}

struct PositionCommand::PositionCommandImpl
{
    int x_;
    int y_;

    PositionCommandImpl(const int x, const int y);
};

PositionCommand::PositionCommandImpl::PositionCommandImpl(const int x, const int y)
{
    x_ = x;
    y_ = y;
}

PositionCommand::PositionCommand(const int x, const int y)
        : pimpl(std::make_unique<PositionCommandImpl>(x, y))
{
}

PositionCommand::~PositionCommand() = default;

PositionCommand::PositionCommand(PositionCommand &&) noexcept = default;

PositionCommand &PositionCommand::operator=(PositionCommand &&) noexcept = default;

void PositionCommand::Execute(Rover &rover) const
{
    rover.InitializePosition(std::make_unique<Position>(pimpl->x_, pimpl->y_));
}

struct DirectionCommand::DirectionCommandImpl
{
    Direction direction_;

    explicit DirectionCommandImpl(const Direction direction)
    {
        direction_ = direction;
    }
};

DirectionCommand::DirectionCommand(const Direction direction)
        : pimpl(std::make_unique<DirectionCommandImpl>(direction))
{
}

void DirectionCommand::Execute(Rover &rover) const
{
    rover.InitializeDirection(pimpl->direction_);
}

DirectionCommand::~DirectionCommand() = default;

DirectionCommand::DirectionCommand(DirectionCommand &&) noexcept = default;

DirectionCommand &DirectionCommand::operator=(DirectionCommand &&) noexcept = default;

void TurnLeftCommand::Execute(Rover &rover) const
{
    rover.TurnLeft();
}

void TurnRightCommand::Execute(Rover &rover) const
{
    rover.TurnRight();
}

void MoveCommand::Execute(Rover &rover) const
{
    rover.Move();
}

void NoMoveCommand::Execute(Rover &rover) const
{
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

Commands::Commands(Commands &&) noexcept = default;

Commands &Commands::operator=(Commands &&) noexcept = default;

void Commands::Execute(Rover &rover) const
{
    for (auto const &command : pimpl->commands)
    {
        command->Execute(rover);
    }
}

void Commands::AddCommand(std::unique_ptr<Command> &&command)
{
    pimpl->AddCommand(std::move(command));
}