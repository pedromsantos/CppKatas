#pragma once
#include <memory>
#include <vector>
#include <functional>
#include <string>
#include <map>

#include "Directions.hpp"

class Commands;

typedef std::map<std::string, Direction> InstructionsToDirections;

class InstructionParser
{	
	static InstructionsToDirections instructionsToDirections_;
	
	std::vector<std::string> InstructionParser::Split(const std::string &text, char sep) const;
	void ParseGridSizeInstruction(std::unique_ptr<Commands>& commands, std::string line) const;
	void ParsePositionInstruction(std::unique_ptr<Commands>& commands, std::string line) const;
	void ParseDirectionInstruction(std::unique_ptr<Commands>& commands, std::string line) const;
	void ParseMovementCommands(const std::unique_ptr<Commands>& commands, std::string line) const;
	
public:
	virtual ~InstructionParser()
	{
	}
	
	std::unique_ptr<Commands> Parse(const std::string& instructions) const;
};

struct Plateau
{
private:
	int width_;
	int heigth_;

public:
	Plateau(int width, int height)
		:width_(width), heigth_(height)
	{
	}

	bool IsEqual(const Plateau& other) const
	{
		return heigth_ == other.heigth_
			&& width_ == other.width_;
	}
};

inline bool operator==(const Plateau& lPlateau, const Plateau& rPlateau) {
	return typeid(lPlateau) == typeid(rPlateau)
		&& lPlateau.IsEqual(rPlateau);
}

struct Position
{
private:
	int x_;
	int y_;

	std::map<Direction, std::function<Position(int, int)>> move_;

public:
	Position(int x, int y)
		:x_(x), y_(y)
	{
		move_ =
		{
			{ Direction::North, [](int x, int y) { return Position(x, y + 1);} },
			{ Direction::South, [](int x, int y) {return Position(x, y - 1);} },
			{ Direction::East, [](int x, int y) { return Position(x + 1, y);} },
			{ Direction::West, [](int x, int y) { return Position(x - 1, y);} },
		};
	}
	
	bool IsEqual(const Position& other) const
	{
		return x_ == other.x_
			&& y_ == other.y_;
	}

	Position Move(Direction direction)
	{
		return move_[direction](x_, y_);
	}

	std::string ToString()
	{
		return std::to_string(x_) + " " + std::to_string(y_);
	}
};

inline bool operator==(const Position& lPosition, const Position& rPosition) {
	return typeid(lPosition) == typeid(rPosition)
		&& lPosition.IsEqual(rPosition);
}

class Rover
{
	Plateau plateau_;
	Position position_;
	Direction direction_;	
	std::unique_ptr<InstructionParser> instruction_parser_;

	static std::map<Direction, Direction> turnRight_;
	static std::map<Direction, Direction> turnLeft_;
	static std::map<Direction, std::string> directions_;
	
public:
	Rover();
	Rover(Plateau plateau, Position position, Direction direction);
	
	void virtual InitializeGridSize(int width, int heigth);
	void virtual InitializePosition(int x, int y);
	void virtual InitializeDirection(Direction direction);

	std::string Execute(const std::string& instructions);
	
	void virtual TurnLeft();
	void virtual TurnRight();
	void virtual Move();

	virtual bool IsEqual(const Rover& rover) const
	{
		return 
			rover.plateau_ == plateau_
			&& rover.position_ == position_
			&& rover.direction_ == direction_;
	}
};

inline bool operator==(const Rover& lRover, const Rover& rRover) {
	return typeid(lRover) == typeid(rRover)
		&& lRover.IsEqual(rRover);
}