//
// Created by aleksey on 21.06.2021.
//

#ifndef CONAN_EXAMPLE_HEADER_H
#define CONAN_EXAMPLE_HEADER_H

#include <string>

namespace http {
    class Header {
    public:
        Header() = default;
        std::string& name();
        std::string& value();

        const std::string& name() const;
        const std::string& value() const;

    private:
        std::string m_name;
        std::string m_value;
    };
} // namespace http



#endif //CONAN_EXAMPLE_HEADER_H
