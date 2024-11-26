#include "output.h"

#include <iostream>

namespace ui
{

  Output::Output(){}

  void Output::printMessage(const std::string &message)
  {
    std::cout << message << std::endl;
  }

}