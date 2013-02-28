#pragma once

#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
	#define DEBUGNEW   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
	#define DEBUGNEW   new
#endif

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

namespace Lua
{
    class ntAutoBlock
    {
    public:

        ntAutoBlock(lua_State* state)
            : m_pState(state)
            , m_iStackTop(lua_gettop(m_pState))
        {

        }

        ~ntAutoBlock()
        {
            lua_settop(m_pState, m_iStackTop);
        }

    private:
        ntAutoBlock(const ntAutoBlock& );                   
        const ntAutoBlock& operator = (const ntAutoBlock& );

    private:

        lua_State* m_pState;
        int m_iStackTop;
    };

    template<typename _Type>
    struct ntTypeTraits
    {
        typedef _Type ReturnType;
        typedef _Type ParamType;
    };

    template<typename _Type>
    struct ntTpWrapper;

    template<typename _Type >
    struct ntReturnWrapper
    {
        typedef typename ntTypeTraits<_Type >::ReturnType RT;
        typedef typename ntTpWrapper<RT > RW; 
    };

    template<typename _Type >
    struct ParamWrapper
    {
        typedef typename ntTypeTraits<_Type >::ParamType PT;
        typedef typename ntTpWrapper<PT > PW; 
    };

    #define ntTypeWrapper_NoneImpl(_Type)\
    template<>\
    struct ntTpWrapper<_Type >\
    {\
    }

    #define ntTypeWrapper_NumberImpl(_Type)\
    template<>\
    struct ntTpWrapper<_Type >\
    {\
        inline static void Push(lua_State* L, _Type value)             \
        {\
            lua_pushnumber(L, (LUA_NUMBER)value); \
        }\
        inline static bool Match(lua_State* L, int idx)\
        {\
            return lua_type(L, idx) == LUA_TNUMBER;  \
        }\
        inline static _Type Get(lua_State* L, int idx)\
        {\
            return static_cast<_Type>(lua_tonumber(L, idx));\
        }\
        inline static _Type Default()\
        {\
            return static_cast<_Type>(0);\
        }\
    }

    template<>
    struct ntTpWrapper<bool >
    {
        inline static void Push(lua_State* L, bool value) 
        { 
            lua_pushboolean(L,value); 
        }

        inline static bool Match(lua_State* L, int idx)
        {
            return lua_type(L, idx) == LUA_TBOOLEAN;  
        }

        inline static bool Get(lua_State* L, int idx)
        {
            return lua_toboolean(L, idx) != 0;
        }

        inline static bool Default()
        {
            return false;
        }
    };    
    
    template<>
    struct ntTpWrapper<const char* >
    {
        inline static void Push(lua_State* L, const char* value)             
        {
            lua_pushstring(L,value); 
        }

        inline static bool Match(lua_State* L, int idx)
        {
            return lua_type(L, idx) == LUA_TSTRING;  
        }

        inline static const char* Get(lua_State* L, int idx)
        {
            const char* pszResult = lua_tostring(L, idx);

            return pszResult != NULL ? pszResult : "";
        }

        inline static const char* Default()
        {
            return "";
        }
    };


    template<>
    struct ntTpWrapper<char* >
    {
        inline static void Push(lua_State* L, const char* value)             
        {
            lua_pushstring(L,value); 
        }
    };

    ntTypeWrapper_NumberImpl(char);
    ntTypeWrapper_NumberImpl(unsigned char);
    ntTypeWrapper_NumberImpl(short);
    ntTypeWrapper_NumberImpl(unsigned short);
    ntTypeWrapper_NumberImpl(long);
    ntTypeWrapper_NumberImpl(unsigned long);
    ntTypeWrapper_NumberImpl(int);
    ntTypeWrapper_NumberImpl(unsigned int);
    ntTypeWrapper_NumberImpl(long long);
    ntTypeWrapper_NumberImpl(float);
    ntTypeWrapper_NumberImpl(double);
    ntTypeWrapper_NoneImpl(unsigned long long);
}