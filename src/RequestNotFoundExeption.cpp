#include "RequestNotFoundExeption.h"

const char *RequestNotFoundExeption::what() const noexcept
{
    return "missing file <request.json> ";
}