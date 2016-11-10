#pragma once
 #include "Directions.hpp"
 #include <vector>
 #include <memory>

class Rover;

class Command
{
public:
	void virtual Execute(Rover* rover) {};
};

class GridSizeCommand : public Command
{
	int width_;
	int heigth_;

public:
	GridSizeCommand(int width, int heigth)
		: width_(width), heigth_(heigth)
	{
	}

	void Execute(Rover* rover) override;	
};

class PositionCommand : public Command
{
	int x_;
	int y_;

public:
	PositionCommand(int x, int y)
		: x_(x), y_(y)
	{
	}

	void Execute(Rover* rover) override;
};


class DirectionCommand : public Command
{
	Direction direction_;

public:
	DirectionCommand(Direction direction)
		: direction_(direction)
	{
	}

	void Execute(Rover* rover) override;
};

class TurnLeftCommand : public Command
{
public:
	void Execute(Rover* rover) override;
};

class TurnRightCommand : public Command
{
public:
	void Execute(Rover* rover) override;
};

class MoveCommand : public Command
{
public:
	void Execute(Rover* rover) override;
};

class Commands
{
	std::vector<std::unique_ptr<Command >> commands;

public:
	void AddCommand(std::unique_ptr<Command> &&cmd);
	void Execute(Rover* rover);
};