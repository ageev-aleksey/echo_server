#include "Session.h"

static constexpr char DELIMITER = ';';

namespace asio = boost::asio;

void Session::init(boost::asio::ip::tcp::socket socket) {
    if (!m_socket) {
        m_socket = std::make_unique<asio::ip::tcp::socket>(std::move(socket));
    } else {
        *m_socket = std::move(socket);
    }
    m_buffer.clear();
}

size_t CommandBuffer::getCommandsNum() {
    if (m_bufferState == BufferState::UPDATE) {
        reload();
        m_bufferState = BufferState::LOADED;
    }
    return m_indexes.size();
}

std::vector<char> CommandBuffer::getCommand(size_t index) {
    if (m_bufferState == BufferState::UPDATE) {
        reload();
        m_bufferState = BufferState::LOADED;
    }

    if (index == 0) {
        return std::vector<char>( m_buffer.begin(), m_buffer.begin() + m_indexes[index]);
    }

//    if (index == m_indexes.size()-1) {
//        return std::vector<char>(m_buffer.begin() + m_indexes[index], m_buffer.end());
//    }
    return std::vector<char>(m_buffer.begin() + m_indexes[index-1], m_buffer.begin() + m_indexes[index]);
}

void CommandBuffer::push(std::vector<char> data, size_t copySize) {
    m_buffer.insert(m_buffer.end(), data.begin(), data.begin() + copySize);
    m_bufferState = BufferState::UPDATE;
}

void CommandBuffer::reload() {
    m_indexes.clear();
    size_t index = 0;
    //m_indexes.push_back(index);
    for (auto itr = m_buffer.begin(); itr != m_buffer.end(); itr++) {
        if ((*itr == DELIMITER) && (itr + 1 != m_buffer.end())) {
            index++;
            m_indexes.push_back(index);
            continue;
        }
        index++;
    }
}

void CommandBuffer::clear() {
    m_buffer.resize(0);
    m_bufferState = BufferState::UPDATE;
}

boost::asio::ip::tcp::socket &Session::getSocket() {
    return *m_socket;
}

CommandBuffer &Session::getBuffer() {
    return m_buffer;
}

std::vector<char> &Session::getReadBuffer() {
    return m_readBuffer;
}
