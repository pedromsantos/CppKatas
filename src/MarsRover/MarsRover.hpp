#pragma once

#include "Directions.hpp"

#include <memory>
#include <vector>
#include <functional>
#include <string>
#include <map>

class Commands;

typedef std::map<std::string, Direction> InstructionsToDirections;

class InstructionParser
{
public:
    InstructionParser();

    virtual ~InstructionParser();

    std::unique_ptr<Commands> Parse(const std::string &instructions) const;

private:
    struct PImpl;
    std::unique_ptr<PImpl> pimpl;
};

struct Plateau
{
public:
    Plateau(int width, int height);

    ~Plateau();

    bool IsEqual(const Plateau &other) const;

private:
    struct PImpl;
    std::unique_ptr<PImpl> pimpl;
};

inline bool operator==(const Plateau &lPlateau, const Plateau &rPlateau)
{
    return typeid(lPlateau) == typeid(rPlateau)
           && lPlateau.IsEqual(rPlateau);
}

struct Position
{
private:
    int x_;
    int y_;

    std::map<Direction, std::function<std::unique_ptr<Position> (int, int)>> move_;

public:
    Position(int x, int y)
            : x_(x), y_(y)
    {
        move_ =
                {
                    {Direction::North, [](int xx, int yy) { return std::make_unique<Position>(xx, yy + 1); }},
                    {Direction::South, [](int xx, int yy) { return std::make_unique<Position>(xx, yy - 1); }},
                    {Direction::East,  [](int xx, int yy) { return std::make_unique<Position>(xx + 1, yy); }},
                    {Direction::West,  [](int xx, int yy) { return std::make_unique<Position>(xx - 1, yy); }},
                };
    }

    bool IsEqual(const Position &other) const
    {
        return x_ == other.x_
               && y_ == other.y_;
    }

    std::unique_ptr<Position> Move(Direction direction)
    {
        return move_[direction](x_, y_);
    }

    std::string ToString()
    {
        return std::to_string(x_) + " " + std::to_string(y_);
    }
};

inline bool operator==(const Position &lPosition, const Position &rPosition)
{
    return typeid(lPosition) == typeid(rPosition)
           && lPosition.IsEqual(rPosition);
}

class Rover
{
    Direction direction_;
    std::unique_ptr<Plateau> plateau_;
    std::unique_ptr<Position> position_;
    std::unique_ptr<InstructionParser> instruction_parser_;

    static std::map<Direction, Direction> turnRight_;
    static std::map<Direction, Direction> turnLeft_;
    static std::map<Direction, std::string> directions_;

public:
    Rover();

    Rover(std::unique_ptr<Plateau>&& plateau, std::unique_ptr<Position>&& position, Direction direction);

    void virtual InitializeGridSize(std::unique_ptr<Plateau>&& plateau);

    void virtual InitializePosition(std::unique_ptr<Position>&& position);

    void virtual InitializeDirection(Direction direction);

    std::string Execute(const std::string &instructions);

    void virtual TurnLeft();

    void virtual TurnRight();

    void virtual Move();

    virtual bool IsEqual(const Rover &rover) const
    {
        return
                *rover.plateau_ == *plateau_
                && *rover.position_ == *position_
                && rover.direction_ == direction_;
    }
};

inline bool operator==(const Rover &lRover, const Rover& rRover)
{
    return typeid(lRover) == typeid(rRover)
           && lRover.IsEqual(rRover);
}