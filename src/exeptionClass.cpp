#include "exeptionClass.h"

const char *ConfigNotFoundExeption::what() const noexcept
{
    return "missing file <config.json> ";
}
