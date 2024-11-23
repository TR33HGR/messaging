add_library(socket client.cpp server.cpp socket.cpp)
target_include_directories(socket PUBLIC .)
target_link_libraries(socket PRIVATE ws2_32)
