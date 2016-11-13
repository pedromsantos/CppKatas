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

struct Position::PImpl
{
    int x_;
    int y_;

    std::map<Direction, std::function<std::unique_ptr<Position> (int, int)>> move_;
};

Position::Position(int x, int y) : pimpl(new PImpl)
{
    pimpl->x_ = x;
    pimpl->y_ = y;

    pimpl->move_ =
        {
                {Direction::North, [](int xx, int yy) { return std::make_unique<Position>(xx, yy + 1); }},
                {Direction::South, [](int xx, int yy) { return std::make_unique<Position>(xx, yy - 1); }},
                {Direction::East,  [](int xx, int yy) { return std::make_unique<Position>(xx + 1, yy); }},
                {Direction::West,  [](int xx, int yy) { return std::make_unique<Position>(xx - 1, yy); }},
        };
}

Position::~Position()
{
}

bool Position::IsEqual(const Position &other) const
{
    return pimpl->x_ == other.pimpl->x_
           && pimpl->y_ == other.pimpl->y_;
}

std::unique_ptr<Position> Position::Move(Direction direction)
{
    return pimpl->move_[direction](pimpl->x_, pimpl->y_);
}

std::string Position::ToString()
{
    return std::to_string(pimpl->x_) + " " + std::to_string(pimpl->y_);
}

struct Rover::PImpl
{
    Direction direction_;
    std::unique_ptr<Plateau> plateau_;
    std::unique_ptr<Position> position_;
    std::unique_ptr<InstructionParser> instruction_parser_;

    static std::map<Direction, Direction> turnRight_;
    static std::map<Direction, Direction> turnLeft_;
    static std::map<Direction, std::string> directions_;
};

std::map<Direction, Direction> Rover::PImpl::turnRight_ =
{
    {Direction::North, Direction::East},
    {Direction::East,  Direction::South},
    {Direction::South, Direction::West},
    {Direction::West,  Direction::North}
};

std::map<Direction, Direction> Rover::PImpl::turnLeft_ =
{
    {Direction::North, Direction::West},
    {Direction::East,  Direction::North},
    {Direction::South, Direction::East},
    {Direction::West,  Direction::South}
};

std::map<Direction, std::string> Rover::PImpl::directions_ =
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
        : pimpl(new PImpl)
{
    pimpl->plateau_ = std::move(plateau);
    pimpl->position_ = std::move(position);
    pimpl->direction_ = direction;
    pimpl->instruction_parser_ = std::make_unique<InstructionParser>();
}

Rover::~Rover()
{
}

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

    return pimpl->position_->ToString() + " " + pimpl->directions_[pimpl->direction_];
}

void Rover::TurnLeft()
{
    pimpl->direction_ = pimpl->turnLeft_[pimpl->direction_];
}

void Rover::TurnRight()
{
    pimpl->direction_ = pimpl->turnRight_[pimpl->direction_];
}

void Rover::Move()
{
    pimpl->position_ = pimpl->position_->Move(pimpl->direction_);
}

bool Rover::IsEqual(const Rover &rover) const
{
    return
        *rover.pimpl->plateau_ == *pimpl->plateau_
        && *rover.pimpl->position_ == *pimpl->position_
        && rover.pimpl->direction_ == pimpl->direction_;
}