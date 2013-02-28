#pragma once

#include "AxLuaBase.h"

namespace Lua
{
    template<typename T>
    struct Force
    {
    };

    template<typename _Type>
    struct TypeTraits<Force<_Type > >
    {
        typedef _Type ReturnType;
        typedef _Type ParamType;
    };

    /** 默认const char* 只支持作为参数传入 */
    template<>
    struct TypeTraits<const char* >
    {
        typedef const char* ParamType;
    };
}
