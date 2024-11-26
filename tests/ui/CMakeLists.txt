add_executable(test_ui testOutput.cpp)
target_link_libraries(test_ui PRIVATE gtest_main gmock_main ui)

add_test(test_ui_lib test_ui)
