#pragma once
#include <exception>

class Exept: public std::exception
{
    const char* what() const noexcept override;
};
