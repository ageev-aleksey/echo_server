//
// Created by aleksey on 21.06.2021.
//

#ifndef CONAN_EXAMPLE_BODY_H
#define CONAN_EXAMPLE_BODY_H

#include <vector>
#include <list>

namespace http {
    class Body {
    public:
        Body() = default;
        /*
         * Добавление данных в конец буффера тела
         * @param data - добавляемые данные
         */
        void write(std::vector<char> data);
        size_t size() const;
        char operator[](size_t index) const;
        char& operator[](size_t index);
    private:
        std::list<std::vector<char>> m_buffers;
    };
}



#endif //CONAN_EXAMPLE_BODY_H
