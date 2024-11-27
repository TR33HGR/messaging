#include "input.h"

#include <iostream>

namespace ui
{

  Input::Input() {}

  void Input::startReceivingInput(std::function<void(std::string)> outputMessage)
  {
    std::string inputMessage;
    std::cout << "Input a message to send..." << std::endl;
    while (true)
    {
      std::getline(std::cin, inputMessage);
      outputMessage(inputMessage);
    }
  }

}