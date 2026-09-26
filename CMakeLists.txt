cmake_minimum_required(VERSION 4.4.1)
set(CMAKE_CXX_COMPILER g++)
project(engo-net VERSION 0.1.0 LANGUAGES C CXX)

add_executable(engo-net
    main/main.cpp
    main/engo_net.cpp
    main/engo_server.cpp
    main/engo_client.cpp
    server/tcp_server.cpp
    server/internal_node.cpp
    client/tcp_client.cpp
    client/user.cpp
    common/logger.cpp
    common/network/connection.cpp
    common/network/socket.cpp
    common/network/packet.cpp
    common/file_handling/filesystem.cpp
    common/file_handling/formed_file.cpp
    common/tui/buffer.cpp
    common/tui/server_tui.cpp
    common/tui/client_tui.cpp
    common/tui/tui.cpp
    common/tui/rect.cpp
)
