#pragma once
#include "Directions.hpp"
#include <vector>
#include <memory>

class Rover;

class Command
{
public:
	virtual void Execute(Rover& rover) = 0;
};

class GridSizeCommand : public Command
{
public:
	GridSizeCommand(int width, int height);
	~GridSizeCommand();

	void Execute(Rover& rover) override;

private:
	struct PImpl;
	std::unique_ptr<PImpl> pimpl;
};

class PositionCommand : public Command
{
public:
	PositionCommand(int x, int y);
	~PositionCommand();

	void Execute(Rover& rover) override;

private:
	struct PImpl;
	std::unique_ptr<PImpl> pimpl;
};

class DirectionCommand : public Command
{
public:
	DirectionCommand(Direction direction);
	~DirectionCommand();

	void Execute(Rover& rover) override;

private:
	struct PImpl;
	std::unique_ptr<PImpl> pimpl;
};

class TurnLeftCommand : public Command
{
public:
	void Execute(Rover& rover) override;
};

class TurnRightCommand : public Command
{
public:
	void Execute(Rover& rover) override;
};

class MoveCommand : public Command
{
public:
	void Execute(Rover& rover) override;
};

class Commands
{
public:
	Commands();
	~Commands();

	void AddCommand(std::unique_ptr<Command> &&cmd) const;
	void Execute(Rover& rover) const;

private:
	struct PImpl;
	std::unique_ptr<PImpl> pimpl;
};