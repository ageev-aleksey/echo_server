//
// Created by aleksey on 21.06.2021.
//

#ifndef CONAN_EXAMPLE_METHOD_H
#define CONAN_EXAMPLE_METHOD_H

#include <string>
#include <stdexcept>

namespace http {
    class Method {
    public:
        enum Value {
            GET, POST, PUT, PATCH ,OPTION, HEADER, INVALID
        };

        Method () {
            value = Value::INVALID;
        }

        Method (Value v) {
            value = v;
        }

        Method (const Method & method) {
            value = method.value;
        }

        Method& operator=(const Method &method) {
            value = method.value;
            return *this;
        }

        bool operator==(const Method &method) const {
            return value == method.value;
        }

        bool operator==(const Value &method) const {
            return this->value == method;
        }

        std::string str() {
            switch (value) {
                case Value::GET:
                    return "GET";
                case Value::POST:
                    return "POST";
                case Value::PATCH:
                    return "PATCH";
                case Value::OPTION:
                    return "OPTION";
                case Value::HEADER:
                    return "HEADER";
            }
            throw std::runtime_error("Invalid http method");
        }

        static Method fromStr(const std::string &str) {
            Method m(Value::INVALID);

            if (str == "GET") {
                m.value = Value::GET;
            } else if (str == "POST") {
                m.value = Value::POST;
            }  else if (str == "PATCH") {
                m.value = Value::PATCH;
            }   else if (str == "OPTION") {
                m.value = Value::OPTION;
            }    else if (str == "HEADER") {
                m.value = Value::HEADER;
            }
            return m;
        }


    private:
        Value value;
    };
}



#endif //CONAN_EXAMPLE_METHOD_H
