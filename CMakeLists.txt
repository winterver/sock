cmake_minimum_required(VERSION 3.15)
project(sock)

set(CMAKE_C_STANDARD 11)

add_executable(server src/server.c)
add_executable(client src/client.c)
target_link_libraries(server PRIVATE ws2_32)
target_link_libraries(client PRIVATE ws2_32)

add_executable(test src/main.cpp)
