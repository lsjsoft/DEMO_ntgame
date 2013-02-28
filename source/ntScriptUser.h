#pragma once

#include "ntScriptBase.h"

bool PushPointer(lua_State* L, void* ptr, const char* type_name, int owned);

bool PopPointer(lua_State* L, void** ptr, const char* type_name, int idx);

void ErrorFunction(const char* pszFunctionName);

void ErrorCall(const char* pszFunctionName, const char* pszErrorMsg);

void ErrorParameter(const char* pszTypeName);

void ErrorReturn(const char* pszTypeName);

#define NT_LUAERRORFUNC(name)                ErrorFunction(name)
#define NT_LUAERRORCALL(name, errorMsg)          ErrorCall(name, errorMsg)
#define NT_LUAERRORARGS(name)               ErrorParameter(name)
#define NT_LUAERRORRT(name)

namespace Lua
{
    template<typename TValue>
    struct ntTpWrapper
    {
        inline static void Push(lua_State* L, const TValue& e)
        {
            TValue* pValue = DEBUGNEW TValue(e);

            const char* pszTypeName = typeid(pValue).name();
            if(!PushPointer(L, pValue, pszTypeName, 1))
            {
                NT_LUAERRORARGS(pszTypeName);
            }
        }

        inline static TValue Get(lua_State* L, int idx)
        {
            TValue* pValue = NULL; 
            const char* pszTypeName = typeid(pValue).name();
            PopPointer(L, (void** )&pValue, pszTypeName, idx);
            return *pValue;
        }

        inline static bool Match(lua_State* L, int idx)
        {
            TValue* pValue = NULL; 
            const char* pszTypeName = typeid(pValue).name();
            return PopPointer(L, (void** )&pValue, pszTypeName, idx);
        }

        inline static TValue Default()
        {
            return TValue();
        }
    };

    template<typename TValue>
    struct ntTpWrapper<TValue *>
    {
    };

    template<typename TValue>
    struct ntTpWrapper<const TValue *>
    {
    };

    template<typename TValue>
    struct ntTpWrapper<TValue &>
    {
        inline static void Push(lua_State* L, TValue& e)
        {
            TValue* pValue = DEBUGNEW TValue(e);

            const char* pszTypeName = typeid(pValue).name();
            if(!PushPointer(L, pValue, pszTypeName, 1))
            {
                NT_LUAERRORARGS(pszTypeName);
            }
        }
    };

    template<typename TValue>
    struct ntTpWrapper<const TValue &>
    {
        inline static void Push(lua_State* L, const TValue& e)
        {
            TValue* pValue = DEBUGNEW TValue(e);

            const char* pszTypeName = typeid(pValue).name();
            if(!PushPointer(L, pValue, pszTypeName, 1))
            {
                NT_LUAERRORARGS(pszTypeName);
            }
        }
    };


    template<>
    struct ntTpWrapper<std::string >
    {
        inline static void Push(lua_State* L, const std::string& value)             
        {
            lua_pushstring(L,value.c_str()); 
        }

        inline static bool Match(lua_State* L, int idx)
        {
            return lua_type(L, idx) == LUA_TSTRING;  
        }

        inline static std::string Get(lua_State* L, int idx)
        {
            const char* pszResult = lua_tostring(L, idx);

            return pszResult != NULL ? pszResult : "";
        }

        inline static std::string Default()
        {
            return "";
        }
    };

    template<>
    struct ntTpWrapper<const std::string& >
    {
        inline static void Push(lua_State* L, const std::string& value)             
        {
            lua_pushstring(L,value.c_str()); 
        }
    };
}