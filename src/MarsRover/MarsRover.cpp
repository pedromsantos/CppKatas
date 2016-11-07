#include "MarsRover.hpp"
#include "Commands.hpp"
#include <memory>
#include <string>

vector<string> InstructionParser::Split(const string &text, char sep) const
{
	vector<string> tokens;
	size_t start = 0, end = 0;
	
	while ((end = text.find(sep, start)) != string::npos) {
		if (end != start) {
			tokens.push_back(text.substr(start, end - start));
		}
		start = end + 1;
	}
	
	if (end != start) {
		tokens.push_back(text.substr(start));
	}

	return tokens;
}

unique_ptr<Commands> InstructionParser::Parse(const string& instructions) const
{
	auto commands = make_unique<Commands>();

	auto tokens = Split(instructions, ' ');

	commands->AddGridSizeCommand(stoi(tokens[0]), stoi(tokens[1]));

	return commands;
}

Rover::Rover()
{
	instruction_parser_ = make_unique<InstructionParser>();
}

void Rover::InitializeGridSize(int width, int heigth) const
{
}

void Rover::InitializePosition(int x, int y) const
{
}

string Rover::Execute(const string& instructions) const
{
	instruction_parser_->Parse(instructions);

	return  "";
}
