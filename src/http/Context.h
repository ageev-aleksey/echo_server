//
// Created by aleksey on 21.06.2021.
//

#ifndef CONAN_EXAMPLE_CONTEXT_H
#define CONAN_EXAMPLE_CONTEXT_H
#include <vector>

#include "http/Header.h"
#include "http/Body.h"
#include "http/Method.h"

/// TODO необходимо избавиться от копирования,
///     Путем использования общего буффера


/// TODO Заменить std::vector<char> на streams

namespace http {
    const std::string HEADER_SEPARATOR = "\r\n";
    const std::string KEY_VALUE_SEPARATOR = ":";

    class Context {
    public:
        static Context parse(const std::vector<char> &buffer);

        Header& operator[](const std::string &value);
        const Header& operator[](const std::string &name) const;

        Body& body();
        const Body& body() const;

        std::vector<char> toBuffer() const;

    private:

    private:
        Method m_method;
        std::string m_path;
        std::list<Header> m_headers;
        Body m_body;
    };
}



#endif //CONAN_EXAMPLE_CONTEXT_H
