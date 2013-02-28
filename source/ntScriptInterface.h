#pragma once

#include "ntScriptUser.h"
#include "ntScriptBase.h"
#include "ntScriptForce.h"

#include <string>

namespace Lua
{
    #define NTLFUNCPRECALL()\
        if(NULL == GetLuaState()) \
            return TReturnWrapper::Default();\
        lua_State* L = m_pState;\
        ntAutoBlock autoBlock(L);\
        lua_pushstring(L, m_sFuncName.c_str());   \
        lua_gettable(L, LUA_GLOBALSINDEX);\
        if (!lua_isfunction(L,-1)) \
        {\
            NT_LUAERRORFUNC(m_sFuncName.c_str());\
            return TReturnWrapper::Default();\
        }

    #define NTLFUNCPOSCALL(args)\
        if(lua_pcall(L, args, 1, 0) != 0)\
        {\
            NT_LUAERRORCALL(m_sFuncName.c_str(), lua_tostring(L, -1));\
            return TReturnWrapper::Default();\
        }\
        if(!TReturnWrapper::Match(L, -1))\
        {\
            NT_LUAERRORRT(typeid(TReturnType).name());\
            return TReturnWrapper::Default();\
        }\
        return TReturnWrapper::Get(L, -1);


    template <typename _RT>
    class ntFunction
    {
        typedef typename ntReturnWrapper<_RT>::RT   TReturnType;
        typedef typename ntReturnWrapper<_RT>::RW   TReturnWrapper;

    public:

        ntFunction(lua_State* pState, const char* pszFuncName)
            : m_pState(pState)
            , m_sFuncName(pszFuncName)
        {

        }

        ntFunction(const char* pszFuncName)
            : m_pState(NULL)
            , m_sFuncName(pszFuncName)
        {

        }

        TReturnType operator()()
        {
            NTLFUNCPRECALL();
            NTLFUNCPOSCALL(0);
        }

        template<typename P1>
        TReturnType operator()(P1 p1)
        {
            NTLFUNCPRECALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            NTLFUNCPOSCALL(1);
        }

        template<typename P1, typename P2>
        TReturnType operator()(P1 p1, P2 p2)
        {
            NTLFUNCPRECALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            ParamWrapper<P2>::PW::Push(L, p2);
            NTLFUNCPOSCALL(2);
        }

        template<typename P1, typename P2, typename P3>
        TReturnType operator()(P1 p1, P2 p2, P3 p3)
        {
            NTLFUNCPRECALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            ParamWrapper<P2>::PW::Push(L, p2);
            ParamWrapper<P3>::PW::Push(L, p3);
            NTLFUNCPOSCALL(3);
        }

        template<typename P1, typename P2, typename P3, typename P4>
        TReturnType operator()(P1 p1, P2 p2, P3 p3, P4 p4)
        {
            NTLFUNCPRECALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            ParamWrapper<P2>::PW::Push(L, p2);
            ParamWrapper<P3>::PW::Push(L, p3);
            ParamWrapper<P4>::PW::Push(L, p4);
            NTLFUNCPOSCALL(4);
        }

        template<typename P1, typename P2, typename P3, typename P4, typename P5>
        TReturnType operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
        {
            NTLFUNCPRECALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            ParamWrapper<P2>::PW::Push(L, p2);
            ParamWrapper<P3>::PW::Push(L, p3);
            ParamWrapper<P4>::PW::Push(L, p4);
            ParamWrapper<P5>::PW::Push(L, p5);
            NTLFUNCPOSCALL(5);
        }

        template<typename P1, typename P2, typename P3, typename P4,
		    typename P5, typename P6>
        TReturnType operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6)
        {
            NTLFUNCPRECALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            ParamWrapper<P2>::PW::Push(L, p2);
            ParamWrapper<P3>::PW::Push(L, p3);
            ParamWrapper<P4>::PW::Push(L, p4);
            ParamWrapper<P5>::PW::Push(L, p5);
            ParamWrapper<P6>::PW::Push(L, p6);
            NTLFUNCPOSCALL(6);
        }

        template<typename P1, typename P2, typename P3, typename P4, 
		    typename P5, typename P6, typename P7>
        TReturnType operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7)
        {
            NTLFUNCPRECALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            ParamWrapper<P2>::PW::Push(L, p2);
            ParamWrapper<P3>::PW::Push(L, p3);
            ParamWrapper<P4>::PW::Push(L, p4);
            ParamWrapper<P5>::PW::Push(L, p5);
            ParamWrapper<P6>::PW::Push(L, p6);
            ParamWrapper<P7>::PW::Push(L, p7);
            NTLFUNCPOSCALL(7);
        }

	    template<typename P1, typename P2, typename P3, typename P4, 
		    typename P5, typename P6, typename P7, typename P8>
	    TReturnType operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8)
	    {
		    NTLFUNCPRECALL();
		    ParamWrapper<P1>::PW::Push(L, p1);
		    ParamWrapper<P2>::PW::Push(L, p2);
		    ParamWrapper<P3>::PW::Push(L, p3);
		    ParamWrapper<P4>::PW::Push(L, p4);
		    ParamWrapper<P5>::PW::Push(L, p5);
		    ParamWrapper<P6>::PW::Push(L, p6);
		    ParamWrapper<P7>::PW::Push(L, p7);
		    ParamWrapper<P8>::PW::Push(L, p8);
		    NTLFUNCPOSCALL(8);
	    }

	    template<typename P1, typename P2, typename P3, typename P4, 
		    typename P5, typename P6, typename P7, typename P8, typename P9>
	    TReturnType operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9)
	    {
		    NTLFUNCPRECALL();
		    ParamWrapper<P1>::PW::Push(L, p1);
		    ParamWrapper<P2>::PW::Push(L, p2);
		    ParamWrapper<P3>::PW::Push(L, p3);
		    ParamWrapper<P4>::PW::Push(L, p4);
		    ParamWrapper<P5>::PW::Push(L, p5);
		    ParamWrapper<P6>::PW::Push(L, p6);
		    ParamWrapper<P7>::PW::Push(L, p7);
		    ParamWrapper<P8>::PW::Push(L, p8);
		    ParamWrapper<P9>::PW::Push(L, p9);
		    NTLFUNCPOSCALL(9);
	    }

        template<typename P1, typename P2, typename P3, typename P4, 
            typename P5, typename P6, typename P7, typename P8, typename P9, typename P10>
            TReturnType operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10)
        {
            NTLFUNCPRECALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            ParamWrapper<P2>::PW::Push(L, p2);
            ParamWrapper<P3>::PW::Push(L, p3);
            ParamWrapper<P4>::PW::Push(L, p4);
            ParamWrapper<P5>::PW::Push(L, p5);
            ParamWrapper<P6>::PW::Push(L, p6);
            ParamWrapper<P7>::PW::Push(L, p7);
            ParamWrapper<P8>::PW::Push(L, p8);
            ParamWrapper<P9>::PW::Push(L, p9);
            ParamWrapper<P10>::PW::Push(L, p10);
            NTLFUNCPOSCALL(10);
        }

        bool operator == (const ntFunction& rFunc)
        {
            return m_sFuncName.compare(rFunc.m_sFuncName) == 0;
        }

    private:

        std::string m_sFuncName;
        lua_State* m_pState;
    };

    #define NTFUNCCALL()\
        if(NULL == GetLuaState()) return;\
        lua_State* L = m_pState;\
        Lua::ntAutoBlock autoBlock(L);\
        lua_pushstring(L, m_sFuncName.c_str());   \
        lua_gettable(L, LUA_GLOBALSINDEX);\
        if (!lua_isfunction(L,-1)) \
        {\
            NT_LUAERRORFUNC(m_sFuncName.c_str());\
            return;\
        }

    #define NTFUNCPCALL(args)\
        if(lua_pcall(L, args, 1, 0) != 0)\
        {\
            NT_LUAERRORCALL(m_sFuncName.c_str(), lua_tostring(L, -1));\
        }


    template <>
    class ntFunction<void>
    {
    public:

        ntFunction(lua_State* pState, const char* pszFuncName)
            : m_pState(pState)
            , m_sFuncName(pszFuncName)
        {

        }

        ntFunction(const char* pszFuncName)
            : m_pState(NULL)
            , m_sFuncName(pszFuncName)
        {
        }

        lua_State* GetLuaState()
        {
            if(m_pState != NULL)
            {
                return m_pState;
            }

            extern lua_State* ntGetLuaState();
            m_pState = ntGetLuaState();
            return m_pState;
        }

        void operator()()
        {
            NTFUNCCALL();
            NTFUNCPCALL(0);
        }

        template<typename P1>
        void operator()(P1 p1)
        {
            NTFUNCCALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            NTFUNCPCALL(1);
        }

        template<typename P1, typename P2>
        void operator()(P1 p1, P2 p2)
        {
            NTFUNCCALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            ParamWrapper<P2>::PW::Push(L, p2);
            NTFUNCPCALL(2);
        }

        template<typename P1, typename P2, typename P3>
        void operator()(P1 p1, P2 p2, P3 p3)
        {
            NTFUNCCALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            ParamWrapper<P2>::PW::Push(L, p2);
            ParamWrapper<P3>::PW::Push(L, p3);
            NTFUNCPCALL(3);
        }

        template<typename P1, typename P2, typename P3, typename P4>
        void operator()(P1 p1, P2 p2, P3 p3, P4 p4)
        {
            NTFUNCCALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            ParamWrapper<P2>::PW::Push(L, p2);
            ParamWrapper<P3>::PW::Push(L, p3);
            ParamWrapper<P4>::PW::Push(L, p4);
            NTFUNCPCALL(4);
        }

        template<typename P1, typename P2, typename P3, typename P4, typename P5>
        void operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
        {
            NTFUNCCALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            ParamWrapper<P2>::PW::Push(L, p2);
            ParamWrapper<P3>::PW::Push(L, p3);
            ParamWrapper<P4>::PW::Push(L, p4);
            ParamWrapper<P5>::PW::Push(L, p5);
            NTFUNCPCALL(5);
        }

        template<typename P1, typename P2, typename P3, typename P4,
		    typename P5, typename P6>
        void operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6)
        {
            NTFUNCCALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            ParamWrapper<P2>::PW::Push(L, p2);
            ParamWrapper<P3>::PW::Push(L, p3);
            ParamWrapper<P4>::PW::Push(L, p4);
            ParamWrapper<P5>::PW::Push(L, p5);
            ParamWrapper<P6>::PW::Push(L, p6);
            NTFUNCPCALL(6);
        }

        template<typename P1, typename P2, typename P3, typename P4, typename P5,
		    typename P6, typename P7>
        void operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7)
        {
            NTFUNCCALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            ParamWrapper<P2>::PW::Push(L, p2);
            ParamWrapper<P3>::PW::Push(L, p3);
            ParamWrapper<P4>::PW::Push(L, p4);
            ParamWrapper<P5>::PW::Push(L, p5);
            ParamWrapper<P6>::PW::Push(L, p6);
            ParamWrapper<P7>::PW::Push(L, p7);
            NTFUNCPCALL(7);
        }

	    template<typename P1, typename P2, typename P3, typename P4, typename P5, 
		    typename P6, typename P7, typename P8>
	    void operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8)
	    {
		    NTFUNCCALL();
		    ParamWrapper<P1>::PW::Push(L, p1);
		    ParamWrapper<P2>::PW::Push(L, p2);
		    ParamWrapper<P3>::PW::Push(L, p3);
		    ParamWrapper<P4>::PW::Push(L, p4);
		    ParamWrapper<P5>::PW::Push(L, p5);
		    ParamWrapper<P6>::PW::Push(L, p6);
		    ParamWrapper<P7>::PW::Push(L, p7);
		    ParamWrapper<P8>::PW::Push(L, p8);
		    NTFUNCPCALL(8);
	    }

	    template<typename P1, typename P2, typename P3, typename P4, typename P5, 
		    typename P6, typename P7, typename P8, typename P9>
	    void operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9)
	    {
		    NTFUNCCALL();
		    ParamWrapper<P1>::PW::Push(L, p1);
		    ParamWrapper<P2>::PW::Push(L, p2);
		    ParamWrapper<P3>::PW::Push(L, p3);
		    ParamWrapper<P4>::PW::Push(L, p4);
		    ParamWrapper<P5>::PW::Push(L, p5);
		    ParamWrapper<P6>::PW::Push(L, p6);
		    ParamWrapper<P7>::PW::Push(L, p7);
		    ParamWrapper<P8>::PW::Push(L, p8);
		    ParamWrapper<P9>::PW::Push(L, p9);
		    NTFUNCPCALL(9);
	    }

        template<typename P1, typename P2, typename P3, typename P4, typename P5, 
            typename P6, typename P7, typename P8, typename P9, typename P10>
            void operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10)
        {
            NTFUNCCALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            ParamWrapper<P2>::PW::Push(L, p2);
            ParamWrapper<P3>::PW::Push(L, p3);
            ParamWrapper<P4>::PW::Push(L, p4);
            ParamWrapper<P5>::PW::Push(L, p5);
            ParamWrapper<P6>::PW::Push(L, p6);
            ParamWrapper<P7>::PW::Push(L, p7);
            ParamWrapper<P8>::PW::Push(L, p8);
            ParamWrapper<P9>::PW::Push(L, p9);
            ParamWrapper<P10>::PW::Push(L, p10);
            NTFUNCPCALL(10);
        }

        bool operator == (const ntFunction& rFunc)
        {
            return m_sFuncName.compare(rFunc.m_sFuncName) == 0;
        }

    private:

        std::string m_sFuncName;
        lua_State* m_pState;
    };
}

#define ntLuaFunc Lua::ntFunction
