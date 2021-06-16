//
// Created by nrx on 16.06.2021.
//

#ifndef CONAN_EXAMPLE_SESSION_H
#define CONAN_EXAMPLE_SESSION_H

#include <boost/asio.hpp>

#include <vector>
#include <memory>

/// TODO необходиом написать обертку над вектором vector_view


class CommandBuffer {
public:
    size_t getCommandsNum();
    std::vector<char> getCommand(size_t index);
    void push(std::vector<char> data, size_t copySize);
    void clear();

private:
    void reload();

private:
    enum class BufferState {
        UPDATE,
        LOADED,
    };

private:
    BufferState m_bufferState;
    std::vector<char> m_buffer;
    std::vector<size_t> m_indexes;
};



class Session {
public:
    Session() = default;
    void init(boost::asio::ip::tcp::socket socket);

    boost::asio::ip::tcp::socket& getSocket();
    CommandBuffer& getBuffer();
    std::vector<char>& getReadBuffer();

private:
    std::vector<char> m_readBuffer;
    CommandBuffer m_buffer;
    std::unique_ptr<boost::asio::ip::tcp::socket> m_socket;
};



#endif //CONAN_EXAMPLE_SESSION_H
