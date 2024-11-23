#pragma once

class ILogger
{
public:
    virtual ~ILogger() = default;
    virtual void log(const char*) = 0;
};

class Logger: public ILogger
{
public:
    void log(const char* message) override;
};