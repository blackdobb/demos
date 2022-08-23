cmake_minimum_required(VERSION 3.0.0)
project("UnixDemo")

set(SRC ${PROJECT_SOURCE_DIR})

add_executable(client ${SRC}/client.cc)
add_executable(server ${SRC}/server.cc)