#pragma once
#include <exception>

class ConfigNotFoundExeption: public std::exception
{
public:
    const char* what() const noexcept override;
};
