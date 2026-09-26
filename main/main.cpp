#include <sys/ioctl.h>
#include <unistd.h>

#include <string_view>

#include "engo_client.hpp"
#include "engo_server.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) throw std::logic_error("usage: engo-net <client:server>");

    std::string_view mode = argv[1];

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    if (mode == "client") {
        EngoClient engo_client{w.ws_col, w.ws_row};
        engo_client.loop();
    }

    if (mode == "server") {
        EngoServer engo_server{w.ws_col, w.ws_row};
        engo_server.loop();
    }

    return 0;
}
