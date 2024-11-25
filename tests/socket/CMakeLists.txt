add_executable(test_socket testClientSocket.cpp testServerSocket.cpp)
target_link_libraries(test_socket PRIVATE gtest_main gmock_main socket)

add_test(test_socket_lib test_socket)
