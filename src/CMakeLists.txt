add_subdirectory(socket)
add_subdirectory(messaging)

add_executable(client client.cpp)
target_link_libraries(client PRIVATE socket messaging)

add_executable(server server.cpp)
target_link_libraries(server PRIVATE socket)
