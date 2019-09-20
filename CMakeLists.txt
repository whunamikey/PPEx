cmake_minimum_required(VERSION 3.13)
project(PPEx)

set(CMAKE_CXX_STANDARD 14)

set(socket_head
    socket/tcp/TcpClass.h

    socket/udp/UdpClass.h
    socket/udp/UdpServer.h
)
set(socket_src
    socket/tcp/TcpClass.cpp

    socket/udp/UdpClass.cpp
    socket/udp/UdpServer.cpp
)

set(proto_head
    proto/Message.h
    )

set(proto_src
    proto/Message.cpp
    )

set(pack_head
    pack/Endpoint.h
    pack/EndpointManager.h
    )

set(pack_src
    pack/Endpoint.cpp
    pack/EndpointManager.cpp
    )

set(HEADS
    ${socket_head}
    ${proto_head}
    ${pack_head}
   )

set(SRCS
    ${socket_src}
    ${proto_src}
    ${pack_src}
    )

add_executable(PPEx
        ${HEADS}
        ${SRCS}
        main.cpp)