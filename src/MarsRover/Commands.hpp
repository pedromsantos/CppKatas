#pragma once
#include <vector>
#include "MarsRover.hpp"

class Command
{
public:
	void virtual Execute(Rover& rover) {};
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

	void Execute(Rover& rover) override;	
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

	void Execute(Rover& rover) override;
};


class DirectionCommand : public Command
{
	Direction direction_;

public:
	DirectionCommand(Direction direction)
		: direction_(direction)
	{
	}

	void Execute(Rover& rover) override;
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
	vector<unique_ptr<Command >> commands;

public:
	void AddGridSizeCommand(int width, int heigth);
	void AddPositionCommand(int x, int y);
	void Execute(Rover& rover);
	void AddDirectionCommand(Direction direction);
	void AddTurnLeftCommand();
	void AddTurnRightCommand();
	void AddMoveCommand();
};