add_library(ui output.cpp input.cpp)
target_include_directories(ui PUBLIC .)
target_link_libraries(ui PRIVATE)
