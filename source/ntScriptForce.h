#pragma once

#include "ntScriptBase.h"

namespace Lua
{
    template<typename T>
    struct Force
    {
    };

    template<typename _Type>
    struct ntTypeTraits<Force<_Type > >
    {
        typedef _Type ReturnType;
        typedef _Type ParamType;
    };

    template<>
    struct ntTypeTraits<const char* >
    {
        typedef const char* ParamType;
    };
}
