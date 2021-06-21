#define BOOST_JSON_STACK_BUFFER_SIZE 1024
#include <boost/json/src.hpp>


#include "server/Server.h"


#include <boost/asio.hpp>
#include <boost/di.hpp>
#include <boost/json.hpp>

#include <memory>
#include <iostream>
#include <fstream>

namespace di = boost::di;
namespace json = boost::json;

auto configure(std::string file_path) {
    std::ifstream file(file_path);
    std::string cfg;
    if (file.is_open()) {
        std::stringstream stream;
        stream << file.rdbuf();
        cfg = stream.str();
        file.close();
    } else {
        std::ofstream default_file(file_path);
        cfg = R"({
    "server": {
        "host": "127.0.0.1",
        "port": 8080
    }
}
                )";
        default_file << cfg;
        default_file.close();
    }


    json::value j = json::parse(cfg);

    std::string v = j.at("server").at("host").as_string().c_str();
    return di::make_injector(
                di::bind<int>.to(static_cast<int>(j.at("server").at("port").as_int64())),
                di::bind<std::string>.to(v)
            );
}

int main() {
  //  auto injector = di::make_injector(di::bind<std::string>.to("127.0.0.1"),
    //                                  di::bind<int>.to(8080));
    auto injector = configure("./config.json");

    //auto injector = di::make_injector(Configuraintion{});
    //Server s("127.0.0.1", 8080);
    auto *s = injector.create<Server*>();
    s->start();
    return 0;
}