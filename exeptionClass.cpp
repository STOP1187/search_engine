#include "exeptionClass.h"

const char *Exept::what() const noexcept
{
    return "missing file <config.json> ";
}
