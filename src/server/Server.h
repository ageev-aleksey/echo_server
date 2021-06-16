//
// Created by nrx on 16.06.2021.
//

#ifndef CONAN_EXAMPLE_SERVER_H
#define CONAN_EXAMPLE_SERVER_H
#include <string>
#include <list>

#include "./server/Session.h"

#include <boost/asio.hpp>

class Server {
public:
    Server(std::string ip, int port);
    void start();
private:
    void accept_handler(const boost::system::error_code &err, boost::asio::ip::tcp::socket &socket);
    void read_handler(std::list<Session>::iterator sessionItr, const boost::system::error_code &err, int tb);
    void write_handler(std::list<Session>::iterator sessionItr, const boost::system::error_code &err, int tb);

    void closeSession(std::list<Session>::iterator sessionItr);

    std::list<Session> m_enableSessions;
    std::list<Session> m_disableSessions;
    boost::asio::io_service m_service;
    boost::asio::ip::tcp::acceptor  m_acceptor;

};


#endif //CONAN_EXAMPLE_SERVER_H
