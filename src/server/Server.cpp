//
// Created by nrx on 16.06.2021.
//

#include "server/Server.h"

#include <iostream>

namespace {
    std::ostream& operator<<(std::ostream &stream, std::vector<char> vec) {
        for (const auto &el : vec) {
            stream << el;
        }
        return stream;
    }
} // namespace

namespace asio = boost::asio;

Server::Server(std::string ip, int port)
    : m_service(), m_acceptor(m_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address_v4("127.0.0.1"), 8080))
{
    std::cout << "ip -> " << ip << "\nport -> " << port << std::endl;
    m_acceptor.async_accept([this](const boost::system::error_code &err, asio::ip::tcp::socket socket) {
        this->accept_handler(err, socket);
    });
}

void Server::accept_handler(const boost::system::error_code &err, asio::ip::tcp::socket &socket) {
    if (err) {
        std::cout << "Ошибка принятия подлкючения | " << err.message() << std::endl;
        return;
    }
    std::cout << "Подключен новый клиент | " << socket.remote_endpoint().address().to_string() << std::endl;

    std::list<Session>::iterator s_ptr;
    if (m_disableSessions.empty()) {
        m_enableSessions.push_back(Session());
    } else {
        m_enableSessions.splice(m_enableSessions.end(), m_disableSessions, m_disableSessions.begin());
    }
    s_ptr = m_enableSessions.end();
    s_ptr--;
    s_ptr->init(std::move(socket));
    s_ptr->getReadBuffer().resize(10);
    s_ptr->getSocket().async_read_some(asio::buffer(s_ptr->getReadBuffer(), 10), [this, s_ptr](const boost::system::error_code &err, int tb) {
        this->read_handler(s_ptr, err, tb);
    });
}

void Server::read_handler(std::list<Session>::iterator sessionItr, const boost::system::error_code &err, int tb) {
 //   auto &session = m_sess[sessionId];
    if (err) {
        std::cout << "Ошибка чтения из сокета | " << err.message() << std::endl;
        closeSession(sessionItr);
        return;
    }

    sessionItr->getBuffer().push(sessionItr->getReadBuffer(), tb);

    if(sessionItr->getBuffer().getCommandsNum() != 0) {
        auto echo_response = sessionItr->getBuffer().getCommand(0);
        std::cout << "Echo: " << echo_response << std::endl;
        sessionItr->getSocket().async_write_some(asio::buffer(echo_response),
        [this, sessionItr](const boost::system::error_code &err, size_t bt) {
            this->write_handler(sessionItr, err, bt);
        });
        sessionItr->getBuffer().clear();
    } else {
        sessionItr->getSocket().async_read_some(asio::buffer(sessionItr->getReadBuffer(), 10),
                                                [this, sessionItr](const boost::system::error_code &er, size_t bt) {
            read_handler(sessionItr, er, bt);
        });
    }
}

void Server::write_handler(std::list<Session>::iterator sessionItr, const boost::system::error_code &err, int tb) {
    if (err) {
        std::cout << "Ошибка записи в сокет | " << err.message() << std::endl;
        closeSession(sessionItr);
        return;
    }

    sessionItr->getReadBuffer().clear();
    sessionItr->getReadBuffer().resize(10);
    sessionItr->getSocket().async_read_some(asio::buffer(sessionItr->getReadBuffer(), 10),
                                            [this, sessionItr](const boost::system::error_code &err, int tb) {
        this->read_handler(sessionItr, err, tb);
    });
}

void Server::closeSession(std::list<Session>::iterator sessionItr) {
    sessionItr->getSocket().close();
    sessionItr->getBuffer().clear();
    m_disableSessions.splice(m_disableSessions.end(), m_enableSessions, sessionItr);
}

void Server::start() {
    m_service.run();
}
