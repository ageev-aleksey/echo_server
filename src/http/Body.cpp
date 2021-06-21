//
// Created by aleksey on 21.06.2021.
//

#include "Body.h"
#include <stdexcept>

void http::Body::write(std::vector<char> data) {
    m_buffers.push_back(std::move(data));
}

size_t http::Body::size() const {
    size_t s = 0;
    for (const auto &el : m_buffers) {
        s += el.size();
    }
    return s;
}

char http::Body::operator[](size_t index) const {
    return const_cast<Body*>(this)->operator[](index);
}

char &http::Body::operator[](size_t index) {
    size_t s = 0;
    for (auto &el : m_buffers) {
        if (el.size() + s <= index) {
            return el[index - s];
        }
        s += el.size();
    }
    throw std::out_of_range("index >= size of http::Body");
}
