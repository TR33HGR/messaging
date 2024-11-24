add_executable(test_socket test_client.cpp)
target_link_libraries(test_socket PRIVATE gtest_main gmock_main)

add_test(test_socket_lib test_socket)
