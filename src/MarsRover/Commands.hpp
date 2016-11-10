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
public:
	GridSizeCommand(int width, int heigth);

	void Execute(Rover* rover) override;	

	~GridSizeCommand();

private:
	struct PImpl;
	std::unique_ptr<PImpl> pimpl;
};

class PositionCommand : public Command
{
public:
	PositionCommand(int x, int y);

	~PositionCommand();

	void Execute(Rover* rover) override;

private:
	struct PImpl;
	std::unique_ptr<PImpl> pimpl;
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