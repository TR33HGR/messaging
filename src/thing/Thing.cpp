#include "Thing.h"
#include "Log.h"

Thing::Thing(std::unique_ptr<ILogger> l)
{
    l->log("Hello World");
}