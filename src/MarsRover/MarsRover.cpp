#include "MarsRover.hpp"
#include "Commands.hpp"

struct InstructionsToCommands
{
private:
    std::map<char, std::function<void(Commands &)>> map =
            {
                    {'R', [](Commands &commands) { commands.AddCommand(std::make_unique<TurnRightCommand>()); }},
                    {'L', [](Commands &commands) { commands.AddCommand(std::make_unique<TurnLeftCommand>()); }},
                    {'M', [](Commands &commands) { commands.AddCommand(std::make_unique<MoveCommand>()); }},
                    {0,   [](Commands &commands) {}}
            };

public:
    std::function<void(Commands &)> InstructionToCommand(const char instruction) const
    {
        return map.at(instruction);
    }
};

struct InstructionsToDirections
{
private:
    std::map<std::string, Direction> map =
            {
                    {"N", Direction::North},
                    {"E", Direction::East},
                    {"S", Direction::South},
                    {"W", Direction::West}
            };

public:
    Direction InstructionToDirection(const std::string &instruction) const
    {
        return map.at(instruction);
    }
};

struct InstructionParser::InstructionParserImpl
{
private:
    const InstructionsToDirections instructionsToDirections_ = InstructionsToDirections();
    const InstructionsToCommands instructionsToCommands_ = InstructionsToCommands();
public:

    std::vector<std::string> Split(const std::string &text, char sep) const;

    void ParseGridSizeInstruction(std::unique_ptr<Commands> &commands, const std::string& line) const;

    void ParsePositionInstruction(std::unique_ptr<Commands> &commands, const std::string& line) const;

    void ParseDirectionInstruction(std::unique_ptr<Commands> &commands, const std::string& line) const;

    void ParseMovementsInstruction(const std::unique_ptr<Commands> &commands, const std::string& line) const;
};

InstructionParser::InstructionParser() : pimpl(new InstructionParserImpl())
{
}

InstructionParser::~InstructionParser() =  default;

std::unique_ptr<Commands> InstructionParser::Parse(const std::string &instructions) const
{
    auto commands = std::make_unique<Commands>();

    auto instructionLines = pimpl->Split(instructions, '\n');

    pimpl->ParseGridSizeInstruction(commands, instructionLines[0]);
    pimpl->ParsePositionInstruction(commands, instructionLines[1]);
    pimpl->ParseDirectionInstruction(commands, instructionLines[1]);
    pimpl->ParseMovementsInstruction(commands, instructionLines[2]);

    return commands;
}

std::vector<std::string> InstructionParser::InstructionParserImpl::Split(const std::string &text, char sep) const
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

void InstructionParser::InstructionParserImpl::ParseGridSizeInstruction(std::unique_ptr<Commands> &commands, const std::string& line) const
{
    auto tokens = Split(line, ' ');
    auto width = std::stoi(tokens[0]);
    auto height = std::stoi(tokens[1]);
    commands->AddCommand(std::make_unique<GridSizeCommand>(width, height));
}

void InstructionParser::InstructionParserImpl::ParsePositionInstruction(std::unique_ptr<Commands> &commands, const std::string& line) const
{
    auto tokens = Split(line, ' ');
    auto x = std::stoi(tokens[0]);
    auto y = std::stoi(tokens[1]);
    commands->AddCommand(std::make_unique<PositionCommand>(x, y));
}

void InstructionParser::InstructionParserImpl::ParseDirectionInstruction(std::unique_ptr<Commands> &commands, const std::string& line) const
{
    auto tokens = Split(line, ' ');
    auto rawDirection = tokens.back();
    auto direction = instructionsToDirections_.InstructionToDirection(rawDirection);
    commands->AddCommand(std::make_unique<DirectionCommand>(direction));
}

void InstructionParser::InstructionParserImpl::ParseMovementsInstruction(const std::unique_ptr<Commands> &commands, const std::string& line) const
{
    for (auto movement : line)
    {
        instructionsToCommands_.InstructionToCommand(movement)(*commands);
    }
}

struct Plateau::PlateauImpl
{
    int width_;
    int height_;

    bool IsEqual(const PlateauImpl &other) const
    {
        return height_ == other.height_
               && width_ == other.width_;
    }
};

Plateau::Plateau(int width, int height) : pimpl(new PlateauImpl)
{
    pimpl->width_ = width;
    pimpl->height_ = height;
}

Plateau::~Plateau() = default;

bool Plateau::IsEqual(const Plateau &other) const
{
    return pimpl->IsEqual(*other.pimpl);
}

struct Moves
{
private:
    std::map<Direction, std::function<std::unique_ptr<Position>(int, int)>> map =
            {
                    {Direction::North, [](int xx, int yy) { return std::make_unique<Position>(xx, yy + 1); }},
                    {Direction::South, [](int xx, int yy) { return std::make_unique<Position>(xx, yy - 1); }},
                    {Direction::East,  [](int xx, int yy) { return std::make_unique<Position>(xx + 1, yy); }},
                    {Direction::West,  [](int xx, int yy) { return std::make_unique<Position>(xx - 1, yy); }},
            };

public:
    std::function<std::unique_ptr<Position>(int, int)> Move(const Direction direction) const
    {
        return map.at(direction);
    }
};

struct Position::PositionImpl
{
    int x_ = 0;
    int y_ = 0;

    const Moves moves_ = Moves();

    bool IsEqual(const Position::PositionImpl &other) const
    {
        return x_ == other.x_
               && y_ == other.y_;
    }

	std::string ToString() const
	{
		return std::to_string(x_) + " " + std::to_string(y_);
	}	

	std::unique_ptr<Position> Move(Direction direction) const
	{
		return moves_.Move(direction)(x_, y_);
	}
};

Position::Position(int x, int y) : pimpl(new PositionImpl)
{
    pimpl->x_ = x;
    pimpl->y_ = y;
}

Position::~Position() = default;

bool Position::IsEqual(const Position &other) const
{
    return pimpl->IsEqual(*other.pimpl);
}

std::unique_ptr<Position> Position::Move(Direction direction) const
{
	return pimpl->Move(direction);
}

std::string Position::ToString() const
{
    return pimpl->ToString();
}

struct RightTurns
{
private:
    std::map<Direction, Direction> map =
            {
                    {Direction::North, Direction::East},
                    {Direction::East,  Direction::South},
                    {Direction::South, Direction::West},
                    {Direction::West,  Direction::North}
            };

public:
    Direction Turn(const Direction direction) const
    {
        return map.at(direction);
    }
};

struct LeftTurns
{
private:
    std::map<Direction, Direction> map =
            {
                    {Direction::North, Direction::West},
                    {Direction::East,  Direction::North},
                    {Direction::South, Direction::East},
                    {Direction::West,  Direction::South}
            };

public:
    Direction Turn(const Direction direction) const
    {
        return map.at(direction);
    }
};

struct DirectionsToText
{
private:
    std::map<Direction, std::string> map =
            {
                    {Direction::North, "N"},
                    {Direction::East,  "E"},
                    {Direction::South, "S"},
                    {Direction::West,  "W"}
            };

public:
    std::string ToText(const Direction direction) const
    {
        return map.at(direction);
    }
};

struct Rover::RoverImpl
{
    Direction direction_ = Direction::North;
    std::unique_ptr<Plateau> plateau_;
    std::unique_ptr<Position> position_;
    std::unique_ptr<InstructionParser> instruction_parser_;

    const RightTurns turnRight_ = RightTurns();
    const LeftTurns turnLeft_ = LeftTurns();
    const DirectionsToText directions_ = DirectionsToText();

    void TurnLeft()
    {
        direction_ = turnLeft_.Turn(direction_);
    }

    void TurnRight()
    {
        direction_ = turnRight_.Turn(direction_);
    }

    void Move()
    {
        position_ = position_->Move(direction_);
    }

    bool IsEqual(const Rover::RoverImpl &rover) const
    {
        return
                *rover.plateau_ == *plateau_
                && *rover.position_ == *position_
                && rover.direction_ == direction_;
    }
};

Rover::Rover()
        : Rover(std::make_unique<Plateau>(0, 0), std::make_unique<Position>(0, 0), Direction::North)
{
}

Rover::Rover(std::unique_ptr<Plateau>&& plateau, std::unique_ptr<Position>&& position, Direction direction)
        : pimpl(new RoverImpl)
{
    pimpl->plateau_ = std::move(plateau);
    pimpl->position_ = std::move(position);
    pimpl->direction_ = direction;

    pimpl->instruction_parser_ = std::make_unique<InstructionParser>();
}

Rover::~Rover() = default;

void Rover::InitializeGridSize(std::unique_ptr<Plateau>&& plateau)
{
    pimpl->plateau_ = std::move(plateau);
}

void Rover::InitializePosition(std::unique_ptr<Position>&& position)
{
    pimpl->position_ = std::move(position);
}

void Rover::InitializeDirection(Direction direction)
{
    pimpl->direction_ = direction;
}

std::string Rover::Execute(const std::string &instructions)
{
    pimpl->instruction_parser_
            ->Parse(instructions)
            ->Execute(*this);

    return pimpl->position_->ToString() + " " + pimpl->directions_.ToText(pimpl->direction_);
}

void Rover::TurnLeft()
{
    pimpl->TurnLeft();
}

void Rover::TurnRight()
{
    pimpl->TurnRight();
}

void Rover::Move()
{
    pimpl->Move();
}

bool Rover::IsEqual(const Rover &rover) const
{
    return pimpl->IsEqual(*rover.pimpl);
}