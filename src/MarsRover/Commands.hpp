#pragma once

#include <vector>
#include "MarsRover.hpp"

class Command
{
public:
    void virtual Execute(Rover &rover)
    {};
};

class GridSizeCommand : public Command
{
    int width_;
    int heigth_;

public:
    GridSizeCommand(int width, int heigth)
            : width_(width), heigth_(heigth)
    {
    }

    void Execute(Rover &rover) override;
};

class Commands
{
    vector<unique_ptr<Command >> commands;

public:
    void AddGridSizeCommand(int width, int heigth);

    void ExecuteNext(Rover &rover);
};