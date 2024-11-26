add_executable(test_messaging testClient.cpp)
target_link_libraries(test_messaging PRIVATE gtest_main gmock_main messaging socket ui)

add_test(test_messaging_lib test_messaging)
