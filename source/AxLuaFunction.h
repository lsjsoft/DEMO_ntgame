#pragma once

#include "AxLuaBase.h"
#include "AxLuaForce.h"
#include "AxLuaUser.h"

#include <string>

namespace Lua
{
    #define LUAFUNCTION_PRECALL()\
        if(NULL == GetLuaState()) \
            return RW::Default();\
        lua_State* L = m_pState;\
        AutoBlock autoBlock(L);\
        lua_pushstring(L, m_sFuncName.c_str());   \
        lua_gettable(L, LUA_GLOBALSINDEX);\
        if (!lua_isfunction(L,-1)) \
        {\
            LUA_ERROR_FUNCTION(m_sFuncName.c_str());\
            return RW::Default();\
        }

    #define LUAFUNCTION_POSTCALL(args)\
        if(lua_pcall(L, args, 1, 0) != 0)\
        {\
            LUA_ERROR_CALL(m_sFuncName.c_str(), lua_tostring(L, -1));\
            return RW::Default();\
        }\
        if(!RW::Match(L, -1))\
        {\
            LUA_ERROR_RETURN(typeid(RT).name());\
            return RW::Default();\
        }\
        return RW::Get(L, -1);


    template <typename _RT>
    class Function
    {
        /** Return Type */
        typedef typename ReturnWrapper<_RT>::RT   RT;
        /** Return Wrapper */
        typedef typename ReturnWrapper<_RT>::RW   RW;

    public:

        Function(lua_State* pState, const char* pszFuncName)
            : m_pState(pState)
            , m_sFuncName(pszFuncName)
        {

        }

        Function(const char* pszFuncName)
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

            GeScriptModule* pkScriptModule = GeGetModule(GeScriptModule);
            m_pState = pkScriptModule->GetLuaState();
            return m_pState;
        }

        RT operator()()
        {
            LUAFUNCTION_PRECALL();
            LUAFUNCTION_POSTCALL(0);
        }

        template<typename P1>
        RT operator()(P1 p1)
        {
            LUAFUNCTION_PRECALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            LUAFUNCTION_POSTCALL(1);
        }

        template<typename P1, typename P2>
        RT operator()(P1 p1, P2 p2)
        {
            LUAFUNCTION_PRECALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            ParamWrapper<P2>::PW::Push(L, p2);
            LUAFUNCTION_POSTCALL(2);
        }

        template<typename P1, typename P2, typename P3>
        RT operator()(P1 p1, P2 p2, P3 p3)
        {
            LUAFUNCTION_PRECALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            ParamWrapper<P2>::PW::Push(L, p2);
            ParamWrapper<P3>::PW::Push(L, p3);
            LUAFUNCTION_POSTCALL(3);
        }

        template<typename P1, typename P2, typename P3, typename P4>
        RT operator()(P1 p1, P2 p2, P3 p3, P4 p4)
        {
            LUAFUNCTION_PRECALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            ParamWrapper<P2>::PW::Push(L, p2);
            ParamWrapper<P3>::PW::Push(L, p3);
            ParamWrapper<P4>::PW::Push(L, p4);
            LUAFUNCTION_POSTCALL(4);
        }

        template<typename P1, typename P2, typename P3, typename P4, typename P5>
        RT operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
        {
            LUAFUNCTION_PRECALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            ParamWrapper<P2>::PW::Push(L, p2);
            ParamWrapper<P3>::PW::Push(L, p3);
            ParamWrapper<P4>::PW::Push(L, p4);
            ParamWrapper<P5>::PW::Push(L, p5);
            LUAFUNCTION_POSTCALL(5);
        }

        template<typename P1, typename P2, typename P3, typename P4,
		    typename P5, typename P6>
        RT operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6)
        {
            LUAFUNCTION_PRECALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            ParamWrapper<P2>::PW::Push(L, p2);
            ParamWrapper<P3>::PW::Push(L, p3);
            ParamWrapper<P4>::PW::Push(L, p4);
            ParamWrapper<P5>::PW::Push(L, p5);
            ParamWrapper<P6>::PW::Push(L, p6);
            LUAFUNCTION_POSTCALL(6);
        }

        template<typename P1, typename P2, typename P3, typename P4, 
		    typename P5, typename P6, typename P7>
        RT operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7)
        {
            LUAFUNCTION_PRECALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            ParamWrapper<P2>::PW::Push(L, p2);
            ParamWrapper<P3>::PW::Push(L, p3);
            ParamWrapper<P4>::PW::Push(L, p4);
            ParamWrapper<P5>::PW::Push(L, p5);
            ParamWrapper<P6>::PW::Push(L, p6);
            ParamWrapper<P7>::PW::Push(L, p7);
            LUAFUNCTION_POSTCALL(7);
        }

	    template<typename P1, typename P2, typename P3, typename P4, 
		    typename P5, typename P6, typename P7, typename P8>
	    RT operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8)
	    {
		    LUAFUNCTION_PRECALL();
		    ParamWrapper<P1>::PW::Push(L, p1);
		    ParamWrapper<P2>::PW::Push(L, p2);
		    ParamWrapper<P3>::PW::Push(L, p3);
		    ParamWrapper<P4>::PW::Push(L, p4);
		    ParamWrapper<P5>::PW::Push(L, p5);
		    ParamWrapper<P6>::PW::Push(L, p6);
		    ParamWrapper<P7>::PW::Push(L, p7);
		    ParamWrapper<P8>::PW::Push(L, p8);
		    LUAFUNCTION_POSTCALL(8);
	    }

	    template<typename P1, typename P2, typename P3, typename P4, 
		    typename P5, typename P6, typename P7, typename P8, typename P9>
	    RT operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9)
	    {
		    LUAFUNCTION_PRECALL();
		    ParamWrapper<P1>::PW::Push(L, p1);
		    ParamWrapper<P2>::PW::Push(L, p2);
		    ParamWrapper<P3>::PW::Push(L, p3);
		    ParamWrapper<P4>::PW::Push(L, p4);
		    ParamWrapper<P5>::PW::Push(L, p5);
		    ParamWrapper<P6>::PW::Push(L, p6);
		    ParamWrapper<P7>::PW::Push(L, p7);
		    ParamWrapper<P8>::PW::Push(L, p8);
		    ParamWrapper<P9>::PW::Push(L, p9);
		    LUAFUNCTION_POSTCALL(9);
	    }

        template<typename P1, typename P2, typename P3, typename P4, 
            typename P5, typename P6, typename P7, typename P8, typename P9, typename P10>
            RT operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10)
        {
            LUAFUNCTION_PRECALL();
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
            LUAFUNCTION_POSTCALL(10);
        }

        bool operator == (const Function& rFunc)
        {
            return m_sFuncName.compare(rFunc.m_sFuncName) == 0;
        }

    private:

        std::string m_sFuncName;
        lua_State* m_pState;
    };

    #define LUAFUNCTIONVOID_PRECALL()\
        if(NULL == GetLuaState()) return;\
        lua_State* L = m_pState;\
        Lua::AutoBlock autoBlock(L);\
        lua_pushstring(L, m_sFuncName.c_str());   \
        lua_gettable(L, LUA_GLOBALSINDEX);\
        if (!lua_isfunction(L,-1)) \
        {\
            LUA_ERROR_FUNCTION(m_sFuncName.c_str());\
            return;\
        }

    #define LUAFUNCTIONVOID_POSTCALL(args)\
        if(lua_pcall(L, args, 1, 0) != 0)\
        {\
            LUA_ERROR_CALL(m_sFuncName.c_str(), lua_tostring(L, -1));\
        }


    template <>
    class Function<void>
    {
    public:

        Function(lua_State* pState, const char* pszFuncName)
            : m_pState(pState)
            , m_sFuncName(pszFuncName)
        {

        }

        Function(const char* pszFuncName)
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
            LUAFUNCTIONVOID_PRECALL();
            LUAFUNCTIONVOID_POSTCALL(0);
        }

        template<typename P1>
        void operator()(P1 p1)
        {
            LUAFUNCTIONVOID_PRECALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            LUAFUNCTIONVOID_POSTCALL(1);
        }

        template<typename P1, typename P2>
        void operator()(P1 p1, P2 p2)
        {
            LUAFUNCTIONVOID_PRECALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            ParamWrapper<P2>::PW::Push(L, p2);
            LUAFUNCTIONVOID_POSTCALL(2);
        }

        template<typename P1, typename P2, typename P3>
        void operator()(P1 p1, P2 p2, P3 p3)
        {
            LUAFUNCTIONVOID_PRECALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            ParamWrapper<P2>::PW::Push(L, p2);
            ParamWrapper<P3>::PW::Push(L, p3);
            LUAFUNCTIONVOID_POSTCALL(3);
        }

        template<typename P1, typename P2, typename P3, typename P4>
        void operator()(P1 p1, P2 p2, P3 p3, P4 p4)
        {
            LUAFUNCTIONVOID_PRECALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            ParamWrapper<P2>::PW::Push(L, p2);
            ParamWrapper<P3>::PW::Push(L, p3);
            ParamWrapper<P4>::PW::Push(L, p4);
            LUAFUNCTIONVOID_POSTCALL(4);
        }

        template<typename P1, typename P2, typename P3, typename P4, typename P5>
        void operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
        {
            LUAFUNCTIONVOID_PRECALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            ParamWrapper<P2>::PW::Push(L, p2);
            ParamWrapper<P3>::PW::Push(L, p3);
            ParamWrapper<P4>::PW::Push(L, p4);
            ParamWrapper<P5>::PW::Push(L, p5);
            LUAFUNCTIONVOID_POSTCALL(5);
        }

        template<typename P1, typename P2, typename P3, typename P4,
		    typename P5, typename P6>
        void operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6)
        {
            LUAFUNCTIONVOID_PRECALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            ParamWrapper<P2>::PW::Push(L, p2);
            ParamWrapper<P3>::PW::Push(L, p3);
            ParamWrapper<P4>::PW::Push(L, p4);
            ParamWrapper<P5>::PW::Push(L, p5);
            ParamWrapper<P6>::PW::Push(L, p6);
            LUAFUNCTIONVOID_POSTCALL(6);
        }

        template<typename P1, typename P2, typename P3, typename P4, typename P5,
		    typename P6, typename P7>
        void operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7)
        {
            LUAFUNCTIONVOID_PRECALL();
            ParamWrapper<P1>::PW::Push(L, p1);
            ParamWrapper<P2>::PW::Push(L, p2);
            ParamWrapper<P3>::PW::Push(L, p3);
            ParamWrapper<P4>::PW::Push(L, p4);
            ParamWrapper<P5>::PW::Push(L, p5);
            ParamWrapper<P6>::PW::Push(L, p6);
            ParamWrapper<P7>::PW::Push(L, p7);
            LUAFUNCTIONVOID_POSTCALL(7);
        }

	    template<typename P1, typename P2, typename P3, typename P4, typename P5, 
		    typename P6, typename P7, typename P8>
	    void operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8)
	    {
		    LUAFUNCTIONVOID_PRECALL();
		    ParamWrapper<P1>::PW::Push(L, p1);
		    ParamWrapper<P2>::PW::Push(L, p2);
		    ParamWrapper<P3>::PW::Push(L, p3);
		    ParamWrapper<P4>::PW::Push(L, p4);
		    ParamWrapper<P5>::PW::Push(L, p5);
		    ParamWrapper<P6>::PW::Push(L, p6);
		    ParamWrapper<P7>::PW::Push(L, p7);
		    ParamWrapper<P8>::PW::Push(L, p8);
		    LUAFUNCTIONVOID_POSTCALL(8);
	    }

	    template<typename P1, typename P2, typename P3, typename P4, typename P5, 
		    typename P6, typename P7, typename P8, typename P9>
	    void operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9)
	    {
		    LUAFUNCTIONVOID_PRECALL();
		    ParamWrapper<P1>::PW::Push(L, p1);
		    ParamWrapper<P2>::PW::Push(L, p2);
		    ParamWrapper<P3>::PW::Push(L, p3);
		    ParamWrapper<P4>::PW::Push(L, p4);
		    ParamWrapper<P5>::PW::Push(L, p5);
		    ParamWrapper<P6>::PW::Push(L, p6);
		    ParamWrapper<P7>::PW::Push(L, p7);
		    ParamWrapper<P8>::PW::Push(L, p8);
		    ParamWrapper<P9>::PW::Push(L, p9);
		    LUAFUNCTIONVOID_POSTCALL(9);
	    }

        template<typename P1, typename P2, typename P3, typename P4, typename P5, 
            typename P6, typename P7, typename P8, typename P9, typename P10>
            void operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10)
        {
            LUAFUNCTIONVOID_PRECALL();
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
            LUAFUNCTIONVOID_POSTCALL(10);
        }

        bool operator == (const Function& rFunc)
        {
            return m_sFuncName.compare(rFunc.m_sFuncName) == 0;
        }

    private:

        std::string m_sFuncName;
        lua_State* m_pState;
    };
}

#define AxLuaFunction Lua::Function
#define AxLuaViodFunc Lua::Function<void>
