#include "server/Server.h"
#include "boost/asio.hpp"

int main() {
    Server s("127.0.0.1", 8080);
    s.start();
    return 0;
}