#include "Log.h"

#include <iostream>

void Logger::log(const char* message)
{
  std::cout << message << std::endl;
}