#pragma once
#include <memory>
#include <vector>
#include <map>
#include "Directions.hpp"

using namespace std;

class Commands;

typedef map<string, Direction> InstructionsToDirections;

class InstructionParser
{	
	static InstructionsToDirections instructionsToDirections_;
	
	vector<string> InstructionParser::Split(const string &text, char sep) const;
		
public:
	virtual ~InstructionParser()
	{
	}

	unique_ptr<Commands> Parse(const string& instructions) const;
};

class Rover
{
	unique_ptr<InstructionParser> instruction_parser_;	

public:
	Rover();

	void virtual InitializeGridSize(int width, int heigth) const;
	void virtual InitializePosition(int x, int y) const;
	void virtual InitializeDirection(Direction direction) const;

	string Execute(const string& instructions) const;
};