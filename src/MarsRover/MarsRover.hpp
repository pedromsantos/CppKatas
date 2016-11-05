#pragma once

#include <memory>
#include <vector>

using namespace std;

class Commands;

class InstructionParser
{
    vector<string> Split(const string &text, char sep) const;

public:
    virtual ~InstructionParser()
    {
    }

    unique_ptr<Commands> Parse(const string &instructions) const;
};

class Rover
{
    unique_ptr<InstructionParser> instruction_parser_;

public:
    Rover();

    void virtual InitializeGridSize(int width, int heigth) const;

    string Execute(const string &instructions) const;
};