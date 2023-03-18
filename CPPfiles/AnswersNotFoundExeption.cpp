#include "AnswersNotFoundExeption.h"

const char *AnswersNotFoundExeption::what() const noexcept
{
    return "missing file <answers.json> ";
}