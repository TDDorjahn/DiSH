#pragma once

#include <iostream>
#include <stdexcept>
#include <source_location>
#include <typeinfo>
#include <utility>


namespace dsh {

    class AssertionFailure : public std::runtime_error {

    public:

        explicit AssertionFailure(const std::string& msg) : std::runtime_error(msg) {}

    };

    template <typename Type>
    inline consteval void dsh_assert(
        bool condition,
        const std::string& msg = "Assertion Failed",
        const std::source_location location = std::source_location::current()
    ) 
    {

        if(!condition) {

            std::cerr << "Assertion failed in object [" << typeid(Type).name() << "]\n"
                    << "Function: " << location.function_name() << ":" << location.line() << '\n'
                    << "File: " << location.file_name() << ":" << location.line() << '\n'
                    << "Msg: " << msg << '\n';

            throw AssertionFailure(message);

        }

    }

    template <typename Function, typename Expected, typename ... FuncArgs>
    inline consteval bool dsh_expected(
        Function func,
        Expected expected_value,
        FuncArgs ... args
    )
    {

        constexpr value = func(std::forward<FuncArgs>(args)...);
        
        if constexpr(value == expected_value)
            return true;
        
        return false;

    }

}