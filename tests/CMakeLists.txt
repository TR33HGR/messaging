include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(tools)

add_executable(test_main test_main.cpp)
target_link_libraries(test_main PRIVATE gtest_main gmock_main thing log)

add_test(all_tests test_main)
