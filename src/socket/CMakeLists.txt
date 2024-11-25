add_library(socket clientSocket.cpp serverSocket.cpp socket.cpp)
target_include_directories(socket PUBLIC .)
target_link_libraries(socket PRIVATE ws2_32)
