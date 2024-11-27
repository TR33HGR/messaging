#pragma once

#include <string>
#include <functional>

namespace ui
{
  class IInput
  {
  public:
    virtual ~IInput() = default;
    virtual void startReceivingInput(std::function<void(std::string)> outputMessage) = 0;
  };

  class Input: public IInput
  {
  public:
    Input();
    void startReceivingInput(std::function<void(std::string)> outputMessage) override;
  };
}