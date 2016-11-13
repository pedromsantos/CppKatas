#include "MarsRover.hpp"
#include "Commands.hpp"

typedef std::map<char, std::function<void(Commands &)>> InstructionsToCommands;

struct InstructionParser::PImpl
{
    static InstructionsToDirections instructionsToDirections_;
    static InstructionsToCommands instructionsToCommands_;

    std::vector<std::string> Split(const std::string &text, char sep) const;

    void ParseGridSizeInstruction(std::unique_ptr<Commands> &commands, std::string line) const;

    void ParsePositionInstruction(std::unique_ptr<Commands> &commands, std::string line) const;

    void ParseDirectionInstruction(std::unique_ptr<Commands> &commands, std::string line) const;

    void ParseMovementsInstruction(const std::unique_ptr<Commands> &commands, std::string line) const;
};

InstructionParser::InstructionParser() : pimpl(new PImpl())
{
}

InstructionParser::~InstructionParser()
{
}

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

InstructionsToDirections InstructionParser::PImpl::instructionsToDirections_ =
{
    {"N", Direction::North},
    {"E", Direction::East},
    {"S", Direction::South},
    {"W", Direction::West}
};

InstructionsToCommands InstructionParser::PImpl::instructionsToCommands_ =
{
    {'R', [](Commands &commands) { commands.AddCommand(std::make_unique<TurnRightCommand>()); }},
    {'L', [](Commands &commands) { commands.AddCommand(std::make_unique<TurnLeftCommand>()); }},
    {'M', [](Commands &commands) { commands.AddCommand(std::make_unique<MoveCommand>()); }},
    {0,   [](Commands &commands) {}}
};

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

void InstructionParser::PImpl::ParseGridSizeInstruction(std::unique_ptr<Commands> &commands, std::string line) const
{
    auto tokens = Split(line, ' ');
    auto width = std::stoi(tokens[0]);
    auto height = std::stoi(tokens[1]);
    commands->AddCommand(std::make_unique<GridSizeCommand>(width, height));
}

void InstructionParser::PImpl::ParsePositionInstruction(std::unique_ptr<Commands> &commands, std::string line) const
{
    auto tokens = Split(line, ' ');
    auto x = std::stoi(tokens[0]);
    auto y = std::stoi(tokens[1]);
    commands->AddCommand(std::make_unique<PositionCommand>(x, y));
}

void InstructionParser::PImpl::ParseDirectionInstruction(std::unique_ptr<Commands> &commands, std::string line) const
{
    auto tokens = Split(line, ' ');
    auto rawDirection = tokens.back();
    auto direction = instructionsToDirections_[rawDirection];
    commands->AddCommand(std::make_unique<DirectionCommand>(direction));
}

void InstructionParser::PImpl::ParseMovementsInstruction(const std::unique_ptr<Commands> &commands, std::string line) const
{
    for (auto movement : line)
    {
        instructionsToCommands_[movement](*commands);
    }
}

struct Plateau::PImpl
{
    int width_;
    int height_;
};

Plateau::Plateau(int width, int height) : pimpl(new PImpl)
{
    pimpl->width_ = width;
    pimpl->height_ = height;
}

Plateau::~Plateau()
{
}

bool Plateau::IsEqual(const Plateau &other) const
{
    return pimpl->height_ == other.pimpl->height_
           && pimpl->width_ == other.pimpl->width_;
}

std::map<Direction, Direction> Rover::turnRight_ =
{
    {Direction::North, Direction::East},
    {Direction::East,  Direction::South},
    {Direction::South, Direction::West},
    {Direction::West,  Direction::North}
};

std::map<Direction, Direction> Rover::turnLeft_ =
{
    {Direction::North, Direction::West},
    {Direction::East,  Direction::North},
    {Direction::South, Direction::East},
    {Direction::West,  Direction::South}
};

std::map<Direction, std::string> Rover::directions_ =
{
    {Direction::North, "N"},
    {Direction::East,  "E"},
    {Direction::South, "S"},
    {Direction::West,  "W"}
};

Rover::Rover()
        : Rover(std::make_unique<Plateau>(0, 0), std::make_unique<Position>(0, 0), Direction::North)
{
}

Rover::Rover(std::unique_ptr<Plateau>&& plateau, std::unique_ptr<Position>&& position, Direction direction)
        : plateau_(std::move(plateau)), position_(std::move(position)), direction_(direction)
{
    instruction_parser_ = std::make_unique<InstructionParser>();
}

void Rover::InitializeGridSize(std::unique_ptr<Plateau>&& plateau)
{
    plateau_ = std::move(plateau);
}

void Rover::InitializePosition(std::unique_ptr<Position>&& position)
{
    position_ = std::move(position);
}

void Rover::InitializeDirection(Direction direction)
{
    direction_ = direction;
}

std::string Rover::Execute(const std::string &instructions)
{
    instruction_parser_
            ->Parse(instructions)
            ->Execute(*this);

    return position_->ToString() + " " + directions_[direction_];
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
    position_ = position_->Move(direction_);
}