#pragma once
#include <memory>
#include <vector>
#include <map>
#include "Directions.hpp"
#include <type_traits>
#include <type_traits>
#include <type_traits>

using namespace std;

class Commands;

typedef map<string, Direction> InstructionsToDirections;

class InstructionParser
{	
	static InstructionsToDirections instructionsToDirections_;
	
	vector<string> InstructionParser::Split(const string &text, char sep) const;
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
public:
	Rover();

	void virtual InitializeGridSize(int width, int heigth) const;
	void virtual InitializePosition(int x, int y) const;
	void virtual InitializeDirection(Direction direction) const;

	string Execute(const string& instructions) const;
	
	void virtual TurnLeft();
};