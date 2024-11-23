#pragma once
#include <memory>

class ILogger;

class Thing
{
public:
    Thing(std::unique_ptr<ILogger>);
};