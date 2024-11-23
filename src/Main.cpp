#include "Thing.h"
#include "Log.h"

#include <memory>

int main()
{
  std::unique_ptr<ILogger> logger = std::make_unique<Logger>();
  Thing thing{std::move(logger)};
}
