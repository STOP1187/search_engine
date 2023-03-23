#pragma once
#include <exception>

class RequestNotFoundExeption: public std::exception
{
public:
    const char* what() const noexcept override;
};
