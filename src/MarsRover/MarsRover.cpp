#include "MarsRover.hpp"
#include "Commands.hpp"
#include <memory>
#include <string>
#include <functional>

InstructionsToDirections InstructionParser::instructionsToDirections_ =
	{
		{ "N", North },
		{ "E", East },
		{ "S", South },
		{ "W", West }
	};

vector<string> InstructionParser::Split(const string &text, char sep) const
{
	vector<string> tokens;
	size_t start = 0, end;
	
	while ((end = text.find(sep, start)) != string::npos) 
	{
		if (end != start) 
		{
			tokens.push_back(text.substr(start, end - start));
		}

		start = end + 1;
	}
	
	if (end != start) 
	{
		auto token = text.substr(start);
		token.erase(token.find_last_not_of(" \n\r\t") + 1);
		tokens.push_back(token);
	}

	return tokens;
}

unique_ptr<Commands> InstructionParser::Parse(const string& instructions) const
{
	auto commands = make_unique<Commands>();

	auto instructionLines = Split(instructions, '\n');

	ParseGridSizeInstruction(commands, instructionLines[0]);	
	ParsePositionInstruction(commands, instructionLines[1]);
	ParseDirectionInstruction(commands, instructionLines[1]);
	ParseMovementCommands(commands, instructionLines[2]);

	return commands;
}

void InstructionParser::ParseGridSizeInstruction(unique_ptr<Commands>& commands, string line) const
{
	auto tokens = Split(line, ' ');
	auto width = stoi(tokens[0]);
	auto heigth = stoi(tokens[1]);
	commands->AddGridSizeCommand(width, heigth);
}

void InstructionParser::ParsePositionInstruction(unique_ptr<Commands>& commands, string line) const
{
	auto tokens = Split(line, ' ');
	auto x = stoi(tokens[0]);
	auto y = stoi(tokens[1]);
	commands->AddPositionCommand(x, y);
}

void InstructionParser::ParseDirectionInstruction(unique_ptr<Commands>& commands, string line) const
{
	auto tokens = Split(line, ' ');
	auto rawDirection= tokens.back();
	auto direction = instructionsToDirections_[rawDirection];
	commands->AddDirectionCommand(direction);
}

void InstructionParser::ParseMovementCommands(const unique_ptr<Commands>& commands, string line) const
{
	for (auto movement : line) 
	{
		if (movement == 'R')
		{
			commands->AddTurnRightCommand();
		}

		if (movement == 'L')
		{
			commands->AddTurnLeftCommand();
		}
		
		if (movement == 'M')
		{
			commands->AddMoveCommand();
		}
	}
}

map<Direction, Direction> Rover::turnRight_ =
{
	{North, East},
	{East, South},
	{South, West},
	{West, North}
};

map<Direction, Direction> Rover::turnLeft_ =
{
	{ North, West },
	{ East, North },
	{ South, East },
	{ West, South }
};

map<Direction, string> Rover::directionToDescription_ =
{
	{ North, "N" },
	{ East, "E" },
	{ South, "S" },
	{ West, "W" }
};

Rover::Rover()
	: Rover(0, 0, 1, 1, North)
{	
}

Rover::Rover(int width, int heigth, int x, int y, Direction direction)
	: x_(x), y_(y), width_(width), heigth_(heigth), direction_(direction)
{
	instruction_parser_ = make_unique<InstructionParser>();

	move_ =
	{
		{ North, [this]() { y_ = y_ + 1;} },
		{ South, [this]() { y_ = y_ - 1;} },
		{ East, [this]() { x_ = x_ + 1;} },
		{ West, [this]() { x_ = x_ - 1;} },
	};
}

void Rover::InitializeGridSize(int width, int heigth)
{
	width_ = width;
	heigth_ = heigth;
}

void Rover::InitializePosition(int x, int y)
{
	x_ = x;
	y_ = y;
}

void Rover::InitializeDirection(Direction direction)
{
	direction_ = direction;
}

string Rover::Execute(const string& instructions)
{
	instruction_parser_
		->Parse(instructions)
		->Execute(this);

	return to_string(x_) + " " + to_string(y_) + " " + directionToDescription_[direction_];
}

void Rover::TurnLeft()
{
	direction_ = turnLeft_[direction_];
}

void Rover::TurnRight()
{
	direction_ = turnRight_[direction_];
}

void Rover::Move()
{
	move_[direction_]();
}