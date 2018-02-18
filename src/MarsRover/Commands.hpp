#ifndef CPPKATAS_SRC_MARSROVER_COMMANDS_H
#define CPPKATAS_SRC_MARSROVER_COMMANDS_H

#include "Directions.hpp"
#include <vector>
#include <memory>

class Rover;

class Command
{
public:
    virtual void Execute(Rover &rover) const = 0;

    Command() = default;

    virtual ~Command() = default;
};

class GridSizeCommand final : public Command
{
public:
    GridSizeCommand(int width, int height);

    ~GridSizeCommand() override;

    GridSizeCommand(GridSizeCommand &&) noexcept;

    GridSizeCommand &operator=(GridSizeCommand &&) noexcept;

    void Execute(Rover &rover) const final;

private:
    struct GridSizeCommandImpl;
    std::unique_ptr<GridSizeCommandImpl> pimpl;
};

class PositionCommand final : public Command
{
public:
    PositionCommand(int x, int y);

    ~PositionCommand() override;

    PositionCommand(PositionCommand &&) noexcept;

    PositionCommand &operator=(PositionCommand &&) noexcept;

    void Execute(Rover &rover) const final;

private:
    struct PositionCommandImpl;
    std::unique_ptr<PositionCommandImpl> pimpl;
};

class DirectionCommand final : public Command
{
public:
    explicit DirectionCommand(Direction direction);

    ~DirectionCommand() override;

    DirectionCommand(DirectionCommand &&) noexcept;

    DirectionCommand &operator=(DirectionCommand &&) noexcept;

    void Execute(Rover &rover) const final;

private:
    struct DirectionCommandImpl;
    std::unique_ptr<DirectionCommandImpl> pimpl;
};

class TurnLeftCommand final : public Command
{
public:
    void Execute(Rover &rover) const final;
};

class TurnRightCommand final : public Command
{
public:
    void Execute(Rover &rover) const final;
};

class MoveCommand final : public Command
{
public:
    void Execute(Rover &rover) const final;
};

class NoMoveCommand final : public Command
{
public:
    void Execute(Rover &rover) const final;
};

class Commands
{
public:
    Commands();

    ~Commands();

    Commands(Commands &&) noexcept;

    Commands &operator=(Commands &&) noexcept;

    void AddCommand(std::unique_ptr<Command> &&cmd);

    void Execute(Rover &rover) const;

private:
    struct CommandsImpl;
    std::unique_ptr<CommandsImpl> pimpl;
};

#endif