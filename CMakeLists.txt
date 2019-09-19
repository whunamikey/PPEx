cmake_minimum_required(VERSION 3.13)
project(PPEx)

set(CMAKE_CXX_STANDARD 14)

set(SOCKET_HEAD
    socket/tcp/TcpClass.h
)
set(SOCKET_SRC
    socket/tcp/TcpClass.cpp
)

add_executable(PPEx main.cpp)