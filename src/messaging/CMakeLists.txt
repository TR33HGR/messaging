add_library(messaging client.cpp)
target_include_directories(messaging PUBLIC .)
target_link_libraries(messaging PRIVATE socket)
