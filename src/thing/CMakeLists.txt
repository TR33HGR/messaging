add_library(thing Thing.cpp)
target_include_directories(thing PUBLIC .)
target_link_libraries(thing PRIVATE log)