#pragma once

#include "Directions.hpp"
#include <vector>
#include <memory>

class Rover;

class Command
{
public:
    virtual void Execute(Rover &rover) = 0;
};

class GridSizeCommand : public Command
{
public:
    GridSizeCommand(int width, int height);

    ~GridSizeCommand();
    GridSizeCommand(GridSizeCommand&&) noexcept;
    GridSizeCommand& operator=(GridSizeCommand&&) noexcept;

    void Execute(Rover &rover) override;

private:
    struct GridSizeCommandImpl;
    std::unique_ptr<GridSizeCommandImpl> pimpl;
};

class PositionCommand : public Command
{
public:
    PositionCommand(int x, int y);

    ~PositionCommand();
    PositionCommand(PositionCommand&&) noexcept;
    PositionCommand& operator=(PositionCommand&&) noexcept;

    void Execute(Rover &rover) override;

private:
    struct PositionCommandImpl;
    std::unique_ptr<PositionCommandImpl> pimpl;
};

class DirectionCommand : public Command
{
public:
    explicit DirectionCommand(Direction direction);

    ~DirectionCommand();
    DirectionCommand(DirectionCommand&&) noexcept;
    DirectionCommand& operator=(DirectionCommand&&) noexcept;

    void Execute(Rover &rover) override;

private:
    struct DirectionCommandImpl;
    std::unique_ptr<DirectionCommandImpl> pimpl;
};

class TurnLeftCommand : public Command
{
public:
    void Execute(Rover &rover) override;
};

class TurnRightCommand : public Command
{
public:
    void Execute(Rover &rover) override;
};

class MoveCommand : public Command
{
public:
    void Execute(Rover &rover) override;
};

class Commands
{
public:
    Commands();

    ~Commands();
    Commands(Commands&&) noexcept;
    Commands& operator=(Commands&&) noexcept;

    void AddCommand(std::unique_ptr<Command> &&cmd) const;

    void Execute(Rover &rover) const;

private:
    struct CommandsImpl;
    std::unique_ptr<CommandsImpl> pimpl;
};