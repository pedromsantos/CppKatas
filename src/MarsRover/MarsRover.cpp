#include "MarsRover.hpp"
#include "Commands.hpp"

#include <memory>
#include <string>
#include <functional>

struct InstructionParser::PImpl
{
	static InstructionsToDirections instructionsToDirections_;

	std::vector<std::string> Split(const std::string &text, char sep) const;
	void ParseGridSizeInstruction(std::unique_ptr<Commands>& commands, std::string line) const;
	void ParsePositionInstruction(std::unique_ptr<Commands>& commands, std::string line) const;
	void ParseDirectionInstruction(std::unique_ptr<Commands>& commands, std::string line) const;
	void ParseMovementsInstruction(const std::unique_ptr<Commands>& commands, std::string line) const;
};

InstructionsToDirections InstructionParser::PImpl::instructionsToDirections_ =
{
	{ "N", Direction::North },
	{ "E", Direction::East },
	{ "S", Direction::South },
	{ "W", Direction::West }
};

InstructionParser::InstructionParser() : pimpl(new PImpl())
{
}

InstructionParser::~InstructionParser()
{
}

std::vector<std::string> InstructionParser::PImpl::Split(const std::string &text, char sep) const
{
	std::vector<std::string> tokens;
	size_t start = 0, end;
	
	while ((end = text.find(sep, start)) != std::string::npos) 
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

std::unique_ptr<Commands> InstructionParser::Parse(const std::string& instructions) const
{
	auto commands = std::make_unique<Commands>();

	auto instructionLines = pimpl->Split(instructions, '\n');

	pimpl->ParseGridSizeInstruction(commands, instructionLines[0]);
	pimpl->ParsePositionInstruction(commands, instructionLines[1]);
	pimpl->ParseDirectionInstruction(commands, instructionLines[1]);
	pimpl->ParseMovementsInstruction(commands, instructionLines[2]);

	return commands;
}

void InstructionParser::PImpl::ParseGridSizeInstruction(std::unique_ptr<Commands>& commands, std::string line) const
{
	auto tokens = Split(line, ' ');
	auto width = std::stoi(tokens[0]);
	auto heigth = std::stoi(tokens[1]);
	commands->AddCommand(std::make_unique<GridSizeCommand>(width, heigth));
}

void InstructionParser::PImpl::ParsePositionInstruction(std::unique_ptr<Commands>& commands, std::string line) const
{
	auto tokens = Split(line, ' ');
	auto x = std::stoi(tokens[0]);
	auto y = std::stoi(tokens[1]);
	commands->AddCommand(std::make_unique<PositionCommand>(x, y));
}

void InstructionParser::PImpl::ParseDirectionInstruction(std::unique_ptr<Commands>& commands, std::string line) const
{
	auto tokens = Split(line, ' ');
	auto rawDirection = tokens.back();
	auto direction = instructionsToDirections_[rawDirection];
	commands->AddCommand(std::make_unique<DirectionCommand>(direction));
}

void InstructionParser::PImpl::ParseMovementsInstruction(const std::unique_ptr<Commands>& commands, std::string line) const
{
	for (auto movement : line) 
	{
		if (movement == 'R')
		{
			commands->AddCommand(std::make_unique<TurnRightCommand>());
		}

		if (movement == 'L')
		{
			commands->AddCommand(std::make_unique<TurnLeftCommand>());
		}
		
		if (movement == 'M')
		{
			commands->AddCommand(std::make_unique<MoveCommand>());
		}
	}
}

std::map<Direction, Direction> Rover::turnRight_ =
{
	{Direction::North, Direction::East},
	{Direction::East, Direction::South},
	{Direction::South, Direction::West},
	{Direction::West, Direction::North}
};

std::map<Direction, Direction> Rover::turnLeft_ =
{
	{Direction::North, Direction::West },
	{Direction::East, Direction::North },
	{Direction::South, Direction::East },
	{Direction::West, Direction::South }
};

std::map<Direction, std::string> Rover::directions_ =
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
	instruction_parser_ = std::make_unique<InstructionParser>();
}

void Rover::InitializeGridSize(int width, int heigth)
{
	plateau_ = Plateau(width, heigth);
}

void Rover::InitializePosition(int x, int y)
{
	position_ = Position(x, y);
}

void Rover::InitializeDirection(Direction direction)
{
	direction_ = direction;
}

std::string Rover::Execute(const std::string& instructions)
{
	instruction_parser_
		->Parse(instructions)	
		->Execute(this);

	return position_.ToString() + " " + directions_[direction_];
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
	position_ = position_.Move(direction_);
}