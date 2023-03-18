#pragma once
#include <exception>

class AnswersNotFoundExeption: public std::exception
{
public:
    const char* what() const noexcept override;
};
