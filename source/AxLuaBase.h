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
    class AutoBlock
    {
    public:

        AutoBlock(lua_State* state)
            : m_pState(state)
            , m_iStackTop(lua_gettop(m_pState))
        {

        }

        ~AutoBlock()
        {
            lua_settop(m_pState, m_iStackTop);
        }

    private:

        AutoBlock(const AutoBlock& );                         // ����Ҫʵ��
        const AutoBlock& operator = (const AutoBlock& );      // ����Ҫʵ��

    private:

        lua_State* m_pState;
        int m_iStackTop;
    };

    /** �������͵õ���Ӧ�ķ���ֵ���ͺͲ������� */
    template<typename _Type>
    struct TypeTraits
    {
        typedef _Type ReturnType;
        typedef _Type ParamType;
    };

    /** ���ͷ�װ����ͨ����������ű���ѹ��ĳ�����͵�ֵ
     *  �ʹӽű�����ȡ��ĳ�����͵�ֵ����������Լ���߸����͵�Ĭ��ֵ
     */
    template<typename _Type>
    struct TypeWrapper;

    /** ����ֵ���ͷ�װ�����ṩ�����ķ���ֵ���ͺͶ�Ӧ�����ͷ�װ�� */
    template<typename _Type >
    struct ReturnWrapper
    {
        typedef typename TypeTraits<_Type >::ReturnType RT;
        typedef typename TypeWrapper<RT > RW; 
    };

    /** �������ͷ�װ�����ṩ�����Ĳ������ͺͶ�Ӧ�����ͷ�װ�� */
    template<typename _Type >
    struct ParamWrapper
    {
        typedef typename TypeTraits<_Type >::ParamType PT;
        typedef typename TypeWrapper<PT > PW; 
    };

    /** ���ṩ�κη�װ�����ͷ�װ��ʵ�� */
    #define TypeWrapper_NoneImpl(_Type)\
    template<>\
    struct TypeWrapper<_Type >\
    {\
    }

    /** Number���ͷ�װ��ʵ�� */
    #define TypeWrapper_NumberImpl(_Type)\
    template<>\
    struct TypeWrapper<_Type >\
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

    /** Boolean���ͷ�װ��ʵ�� */
    template<>
    struct TypeWrapper<bool >
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
    
    /** const char*���ͷ�װ��ʵ�� */
    template<>
    struct TypeWrapper<const char* >
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


    /** char*���ͷ�װ��ʵ�֣����ṩ��Ϊ����ֵ�ķ�װ */
    template<>
    struct TypeWrapper<char* >
    {
        inline static void Push(lua_State* L, const char* value)             
        {
            lua_pushstring(L,value); 
        }
    };

    TypeWrapper_NumberImpl(char);
    TypeWrapper_NumberImpl(unsigned char);
    TypeWrapper_NumberImpl(short);
    TypeWrapper_NumberImpl(unsigned short);
    TypeWrapper_NumberImpl(long);
    TypeWrapper_NumberImpl(unsigned long);
    TypeWrapper_NumberImpl(int);
    TypeWrapper_NumberImpl(unsigned int);
    TypeWrapper_NumberImpl(long long);
    TypeWrapper_NumberImpl(float);
    TypeWrapper_NumberImpl(double);
    TypeWrapper_NoneImpl(unsigned long long);
}