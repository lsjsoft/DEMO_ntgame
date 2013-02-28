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

    /** Ĭ��const char* ֻ֧����Ϊ�������� */
    template<>
    struct TypeTraits<const char* >
    {
        typedef const char* ParamType;
    };
}
