//
// Created by aleksey on 21.06.2021.
//

#include "Header.h"

std::string &http::Header::name() {
    return m_name;
}

std::string &http::Header::value() {
    return m_value;
}

const std::string &http::Header::name() const {
    return m_name;
}

const std::string &http::Header::value() const {
    return m_value;
}
