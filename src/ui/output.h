#pragma once

#include <string>

namespace ui
{
  class IOutput
  {
  public:
    virtual ~IOutput() = default;
    virtual void printMessage(const std::string &message) = 0;
  };

  class Output: public IOutput
  {
  public:
    Output();
    void printMessage(const std::string &message) override;
  };
}