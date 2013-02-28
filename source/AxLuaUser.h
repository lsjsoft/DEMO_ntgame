#pragma once

#include "AxLuaBase.h"

// this code pushes a C++ pointer as well as the SWIG type onto the Lua stack
bool PushPointer(lua_State* L, void* ptr, const char* type_name, int owned);

// this code pops a C++ pointer as well as the SWIG type from the Lua stack
bool PopPointer(lua_State* L, void** ptr, const char* type_name, int idx);

// 错误的函数调用（Lua函数不存在）
void ErrorFunction(const char* pszFunctionName);

// 错误的函数调用（Lua函数参数问题）
void ErrorCall(const char* pszFunctionName, const char* pszErrorMsg);

// 错误的Lua函数参数传入
void ErrorParameter(const char* pszTypeName);

// 错误的Lua函数参数传出
void ErrorReturn(const char* pszTypeName);

#define LUA_ERROR_FUNCTION(name)                ErrorFunction(name)
#define LUA_ERROR_CALL(name, errorMsg)          ErrorCall(name, errorMsg)
#define LUA_ERROR_PARAMETER(name)               ErrorParameter(name)
#define LUA_ERROR_RETURN(name)

namespace Lua
{
    template<typename TValue>
    struct TypeWrapper
    {
        inline static void Push(lua_State* L, const TValue& e)
        {
            //TValue& rValue = const_cast<TValue& >(e);
            TValue* pValue = DEBUGNEW TValue(e);
            //TValue* pValue = &rValue;

            const char* pszTypeName = typeid(pValue).name();
            if(!PushPointer(L, pValue, pszTypeName, 1))
            {
                LUA_ERROR_PARAMETER(pszTypeName);
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
    struct TypeWrapper<TValue *>
    {
        /*inline static void Push(lua_State* L, TValue* e)
        {
            const char* pszTypeName = typeid(e).name();
            if(!PushPointer(L, e,  pszTypeName, 0))
            {
                LUA_ERROR_PARAMETER(pszTypeName);
            }
        }*/
    };

    template<typename TValue>
    struct TypeWrapper<const TValue *>
    {
        /*inline static void Push(lua_State* L, const TValue* e)
        {
            TValue* pValue = const_cast<TValue*>(e);
            const char* pszTypeName = typeid(e).name();
            if(PushPointer(L, pValue, pszTypeName, 0))
            {
                LUA_ERROR_PARAMETER(pszTypeName);
            }
        }*/
    };

    template<typename TValue>
    struct TypeWrapper<TValue &>
    {
        inline static void Push(lua_State* L, TValue& e)
        {
            TValue* pValue = DEBUGNEW TValue(e);
            //TValue* pValue = &e;

            const char* pszTypeName = typeid(pValue).name();
            if(!PushPointer(L, pValue, pszTypeName, 1))
            {
                LUA_ERROR_PARAMETER(pszTypeName);
            }
        }
    };

    template<typename TValue>
    struct TypeWrapper<const TValue &>
    {
        inline static void Push(lua_State* L, const TValue& e)
        {
            //TValue& rValue = const_cast<TValue& >(e);
            TValue* pValue = DEBUGNEW TValue(e);
            //TValue* pValue = &rValue;

            const char* pszTypeName = typeid(pValue).name();
            if(!PushPointer(L, pValue, pszTypeName, 1))
            {
                LUA_ERROR_PARAMETER(pszTypeName);
            }
        }
    };


    template<>
    struct TypeWrapper<std::string >
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
    struct TypeWrapper<const std::string& >
    {
        inline static void Push(lua_State* L, const std::string& value)             
        {
            lua_pushstring(L,value.c_str()); 
        }
    };
}