add_subdirectory(socket)
add_subdirectory(messaging)
add_subdirectory(ui)

add_executable(client client.cpp)
target_link_libraries(client PRIVATE socket messaging ui)

add_executable(server server.cpp)
target_link_libraries(server PRIVATE socket)
