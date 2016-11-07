#pragma once
#include <memory>
#include <vector>
#include <map>
#include "Directions.hpp"
#include <type_traits>
#include <type_traits>
#include <type_traits>
#include <functional>
#include <map>

using namespace std;

class Commands;

typedef map<string, Direction> InstructionsToDirections;

class InstructionParser
{	
	static InstructionsToDirections instructionsToDirections_;
	
	vector<string> Split(const string &text, char sep) const;
	void ParseGridSizeInstruction(unique_ptr<Commands>& commands, string line) const;
	void ParsePositionInstruction(unique_ptr<Commands>& commands, string line) const;
	void ParseDirectionInstruction(unique_ptr<Commands>& commands, string line) const;
	void ParseMovementCommands(const unique_ptr<Commands>& commands, string line) const;
	
public:
	virtual ~InstructionParser()
	{
	}
	
	unique_ptr<Commands> Parse(const string& instructions) const;
};

class Rover
{
	int x_;
	int y_;
	int width_;
	int heigth_;
	Direction direction_;	
	map<Direction, function<void()>> move_;
	unique_ptr<InstructionParser> instruction_parser_;

	static map<Direction, Direction> turnRight_;
	static map<Direction, Direction> turnLeft_;
	static map<Direction, string> directionToDescription_;
	
public:
	Rover();
	Rover(int width, int heigth, int x, int y, Direction direction);
	
	void virtual InitializeGridSize(int width, int heigth);
	void virtual InitializePosition(int x, int y);
	void virtual InitializeDirection(Direction direction);

	string Execute(const string& instructions);
	
	void virtual TurnLeft();
	void virtual TurnRight();
	void virtual Move();

	virtual bool isEqual(const Rover& rover) const
	{
		return
			rover.width_ == width_
			&& rover.heigth_ == heigth_
			&& rover.x_ == x_
			&& rover.y_ == y_
			&& rover.direction_ == direction_;
	}
};

inline bool operator==(const Rover& lRover, const Rover& rRover) {
	return typeid(lRover) == typeid(rRover)
		&& lRover.isEqual(rRover);
}