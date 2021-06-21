//
// Created by aleksey on 21.06.2021.
//

#include "Context.h"
#include <stdexcept>
#include <sstream>

namespace {


    template <typename Iterator>
    std::pair<std::string, std::string> splitKeyValue(Iterator begin,
                                                      Iterator end) {
        for (auto itr = begin; itr != end; itr++) {
            if (*itr == http::KEY_VALUE_SEPARATOR[0]) {
                std::pair<std::string, std::string> ret;
                ret.first = std::string(begin, itr); // str.substr(0, std::distance(begin, itr));
                ret.second = std::string(itr, end); // str.substr(std::distance(str.begin(), itr)-1, end);
                return ret;
            }
        }
        return {};
    }

    enum HttpArea {
     HTTP_HEADER, HTTP_BODY, NONE,
   };

    template <typename Iterator>
    HttpArea isStartedByHeaderSeparator(Iterator begin, Iterator end) {
        if (std::distance(begin, end) < 2) {
            return NONE;
        }
        Iterator itr = begin;
        if (*itr == http::HEADER_SEPARATOR[0] ) {
            itr++;
            if (*itr == http::HEADER_SEPARATOR[1]) {
                return HTTP_HEADER;
            }
        }
        return NONE;
    }

    template <typename Iterator>
    HttpArea checkArea(Iterator begin, Iterator end) {
        if (std::distance(begin, end) < 2) {
            return NONE;
        }

        Iterator itr = begin;
        if (isStartedByHeaderSeparator(itr, end) == HTTP_HEADER) {
            itr += 2;
            if (isStartedByHeaderSeparator(itr, end) == HTTP_HEADER) {
                return HTTP_BODY;
            }
            return HTTP_HEADER;
        }
        return NONE;
    }

    template <typename Iterator>
    http::Header makeHeader(Iterator beginHeader, Iterator endHeader) {
        http::Header header;
        auto keyValue = splitKeyValue(beginHeader, endHeader);
        header.name() = std::move(keyValue.first);
        header.value() = std::move(keyValue.second);
        return header;
    }

    template <typename Iterator>
    Iterator skipSpace(Iterator begin, Iterator end) {
        while ((*begin == ' ' || *begin == '\t') && (begin != end)) {begin++;}
        return begin;
    }

    template <typename Iterator>
    void parseMethodLine(http::Context &context, Iterator begin, Iterator end) {
        Iterator itr = begin;
        while (*itr != ' ') {itr++;}
        http::Method method = http::Method::fromStr(std::string(begin, itr));
        itr = skipSpace(itr, end);
        auto beginPathItr = itr;
        while (*itr != ' ') {itr++;}
        std::string httpPath(beginPathItr, itr);

    }

} // namespace

http::Context http::Context::parse(const std::vector<char> &buffer) {
    Context context;

    auto beforeSymbolItr = buffer.begin();
    auto itr = buffer.begin();

    parseMethodLine(context, itr, buffer.end());

    for (; itr != buffer.end()--; itr++) {
        HttpArea area = checkArea(itr, buffer.end());
        if (area == HTTP_HEADER) {
            Header header = makeHeader(beforeSymbolItr, itr);
            context.m_headers.push_back(std::move(header));
            beforeSymbolItr = itr;
        } else if (area == HTTP_BODY) {
            break;
        }
    }

    context.m_body.write(std::vector<char>(itr, buffer.end()));

    return context;
}

http::Header &http::Context::operator[](const std::string &value) {
    for (auto &header : m_headers) {
        if (header.name() == value) {
            return header;
        }
    }
    std::stringstream  msg;
    msg << "http header " << value << "not found";
    throw std::runtime_error(msg.str());
}

const http::Header &http::Context::operator[](const std::string &name) const {
    return const_cast<Context*>(this)->operator[](name);
}

http::Body &http::Context::body() {
    return m_body;
}

const http::Body &http::Context::body() const {
    return m_body;
}

std::vector<char> http::Context::toBuffer() const {
    return std::vector<char>();
}
