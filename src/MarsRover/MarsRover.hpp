#pragma once

#include "Directions.hpp"

#include <memory>
#include <vector>
#include <functional>
#include <string>
#include <map>

class Commands;

class InstructionParser
{
public:
    InstructionParser();

    virtual ~InstructionParser();

    Commands Parse(const std::string &instructions) const;

private:
    struct InstructionParserImpl;
    std::unique_ptr<InstructionParserImpl> pimpl;
};

struct Plateau
{
public:
    Plateau(int width, int height);

    ~Plateau();

    bool IsEqual(const Plateau &other) const;

private:
    struct PlateauImpl;
    std::unique_ptr<PlateauImpl> pimpl;
};

inline bool operator==(const Plateau &lPlateau, const Plateau &rPlateau)
{
    return typeid(lPlateau) == typeid(rPlateau)
           && lPlateau.IsEqual(rPlateau);
}

struct Position
{
public:
    Position(int x, int y);

    ~Position();

    bool IsEqual(const Position &other) const;

    std::unique_ptr<Position> Move(Direction direction) const;

    std::string ToString() const;

private:
    struct PositionImpl;
    std::unique_ptr<PositionImpl> pimpl;
};

inline bool operator==(const Position &lPosition, const Position &rPosition)
{
    return typeid(lPosition) == typeid(rPosition)
           && lPosition.IsEqual(rPosition);
}

class Rover
{
public:
    Rover();

    Rover(std::unique_ptr<Plateau> &&plateau, std::unique_ptr<Position> &&position, Direction direction);

    ~Rover();

    virtual void InitializeGridSize(std::unique_ptr<Plateau> &&plateau);

    virtual void InitializePosition(std::unique_ptr<Position> &&position);

    virtual void InitializeDirection(Direction direction);

    std::string Execute(const std::string &instructions);

    virtual void TurnLeft();

    virtual void TurnRight();

    virtual void Move();

    bool IsEqual(const Rover &rover) const;

private:
    struct RoverImpl;
    std::unique_ptr<RoverImpl> pimpl;
};

inline bool operator==(const Rover &lRover, const Rover &rRover)
{
    return typeid(lRover) == typeid(rRover)
           && lRover.IsEqual(rRover);
}