#include <string>
#include "MarsRover.hpp"

void InstructionParser::Parse(const string& instructions)
{
}

Rover::Rover(InstructionParser& instructionParser)
{
	instruction_parser_ = &instructionParser;
}

string Rover::Execute(const string& instructions)
{
	instruction_parser_->Parse(instructions);

	return  "";
}