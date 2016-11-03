#pragma once
#include <string>

using namespace std;

class InstructionParser
{
public:
	virtual ~InstructionParser()
	{
	}

	void virtual Parse(const string& instructions);
};

class Rover
{
	InstructionParser* instruction_parser_;

public:
	Rover(InstructionParser& instructionParser);

	string Execute(const string& instructions);
};