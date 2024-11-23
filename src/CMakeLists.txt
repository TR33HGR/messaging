add_subdirectory(log)
add_subdirectory(thing)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE log thing)