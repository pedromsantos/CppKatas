#include "MarsRover.hpp"
#include "Commands.hpp"
#include <memory>
#include <string>
#include <functional>

InstructionsToDirections InstructionParser::instructionsToDirections_ =
	{
		{ "N", Direction::North },
		{ "E", Direction::East },
		{ "S", Direction::South },
		{ "W", Direction::West }
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
	{Direction::North, Direction::East},
	{Direction::East, Direction::South},
	{Direction::South, Direction::West},
	{Direction::West, Direction::North}
};

map<Direction, Direction> Rover::turnLeft_ =
{
	{Direction::North, Direction::West },
	{Direction::East, Direction::North },
	{Direction::South, Direction::East },
	{Direction::West, Direction::South }
};

map<Direction, string> Rover::directions_ =
{
	{Direction::North, "N" },
	{Direction::East, "E" },
	{Direction::South, "S" },
	{Direction::West, "W" }
};

Rover::Rover()
	: Rover(Plateau(0,0), Position(0,0), Direction::North)
{	
}

Rover::Rover(Plateau plateau, Position position, Direction direction)
	: plateau_(plateau), position_(position) , direction_(direction)
{
	instruction_parser_ = make_unique<InstructionParser>();

	move_ =
	{
		{Direction::North, [this]() { position_.y_ = position_.y_ + 1;} },
		{Direction::South, [this]() { position_.y_ = position_.y_ - 1;} },
		{Direction::East, [this]() { position_.x_ = position_.x_ + 1;} },
		{Direction::West, [this]() { position_.x_ = position_.x_ - 1;} },
	};
}

void Rover::InitializeGridSize(int width, int heigth)
{
	plateau_.width_ = width;
	plateau_.heigth_ = heigth;
}

void Rover::InitializePosition(int x, int y)
{
	position_.x_ = x;
	position_.y_ = y;
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

	return to_string(position_.x_) + " " + to_string(position_.y_) + " " + directions_[direction_];
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