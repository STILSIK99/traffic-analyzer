#pragma once

#include <exception>
#include <string>

namespace EXCEPTIONS
{

    class Parameter : public std::exception
    {
            std::string message;
            std::string prefix = "Wrong parameter: ";

        public:
            const char *what() const noexcept override
            {
                return message.c_str();
            }

            Parameter (std::string _m)
            {
                message = prefix + _m;
            }
    };

    class Access : public std::exception
    {
            std::string message;
            std::string prefix = "Access denied: ";

        public:
            const char *what() const noexcept override
            {
                return message.c_str();
            }

            Access (std::string _m)
            {
                message = prefix + _m;
            }
    };

}

