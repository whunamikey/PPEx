cmake_minimum_required(VERSION 3.13)
project(PPEx)

set(CMAKE_CXX_STANDARD 14)

set(SOCKET_HEAD
    socket/tcp/TcpClass.h

    socket/udp/UdpClass.h
    socket/udp/UdpServer.h
)
set(SOCKET_SRC
    socket/tcp/TcpClass.cpp

    socket/udp/UdpClass.cpp
    socket/udp/UdpServer.cpp
)

add_executable(PPEx
        main.cpp
        socket/udp/UdpServer.h
        socket/udp/UdpServer.cpp)