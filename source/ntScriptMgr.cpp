#include "stdafx.h"

extern "C"
{
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

#include "ntScriptMgr.h"
#include "ntscriptexport.h"
#include "ntCodeConvert.h"
#include "ntConsole.h"
#include "ntScriptBase.h"
#include "ntScriptForce.h"
#include "ntScriptUser.h"
#include "ntScriptInterface.h"

#pragma warning(disable: 4996)

ntScriptMgr* g_pIns= NULL;

lua_State* ntGetLuaState()
{
    return g_pIns->getState();
}

ntScriptMgr::ntScriptMgr(void)
: m_pLuaState(NULL)
{
    g_pIns= this;
}

ntScriptMgr::~ntScriptMgr(void)
{
    lua_close(m_pLuaState);
    m_pLuaState= NULL;

    g_pIns= NULL;
}

ntScriptMgr* ntScriptMgr::getIns()
{
    return g_pIns;
}

void ntScriptMgr::load()
{
    m_pLuaState= lua_open();
    luaL_openlibs(m_pLuaState);
    luaopen_gs(m_pLuaState);
    excute("dofile('../data/script/boot.lua')");
    ntLuaFunc<void>("ntInit")();
}

bool ntScriptMgr::excute( const ntString& str )
{
    return excute(ntwtos(str));
}

bool ntScriptMgr::excute(const std::string& rkString)
{
    if (rkString.empty())
    {
        return false;
    }

    int iTop = lua_gettop(m_pLuaState);
    if (luaL_loadbuffer(m_pLuaState, rkString.c_str(), rkString.length(), 
        rkString.c_str()) || lua_pcall(m_pLuaState,0,0,0))
    {
        const char* pcError= lua_tostring(m_pLuaState, -1);
        if (pcError)
        {
            ntConsole::getIns()->output("-------------½Å±¾Ö´ÐÐ´íÎó-------------");
            ntConsole::getIns()->output(pcError);
            ntConsole::getIns()->output("--------------------------------------");
        }
        lua_settop(m_pLuaState, iTop);
        return false;
    }

    return true;
}

void ntScriptMgr::update( float fTime )
{
    ntLuaFunc<void>("ntUpdate")(fTime);
}

void ErrorFunction(const char* pszFunctionName)
{
    printf("Error lua function name: %s\n", pszFunctionName);
}

void ErrorCall(const char* pszFunctionName, const char* pszErrorMsg)
{
    printf("Call lua function(%s) error:%s", pszFunctionName, 
        pszErrorMsg);
}

void ErrorParameter(const char* pszTypeName)
{
    printf("Error lua parameter type: %s\n", pszTypeName);
}

void ErrorReturn(const char* pszTypeName)
{
    printf("Error lua return type: %s\n", pszTypeName);
}

static void adjustName( std::string& sTypeName )
{
    size_t iFind = sTypeName.find(" ");

    if(iFind == sTypeName.npos)
    {
        return;
    }

    sTypeName = sTypeName.substr(iFind + 1);
}

static swig_type_info* querySwigType( const char* pszTypeName )
{
    typedef std::map<std::string, swig_type_info* > AxScriptTypeMap;
    typedef AxScriptTypeMap::iterator AxScriptTypeMapItr;
    
    static AxScriptTypeMap s_typemap;

    if(NULL == pszTypeName)
    {
        return NULL;
    }

    std::string sTypeName = pszTypeName;
    AxScriptTypeMapItr iFind = s_typemap.find(sTypeName);
    if(iFind != s_typemap.end())
    {
        return iFind->second;
    }

    adjustName(sTypeName);

    swig_type_info * pTypeInfo = SWIG_TypeQuery(sTypeName.c_str());
    if(pTypeInfo != NULL)
    {
        s_typemap[pszTypeName] = pTypeInfo;
    }

    return pTypeInfo;
}

bool PushPointer( lua_State* L, void* ptr, const char* type_name, int owned )
{
    swig_type_info * pTypeInfo = querySwigType(type_name);
    if (pTypeInfo == 0)
    {
        return false;   
    }

    SWIG_NewPointerObj(L, ptr, pTypeInfo, owned);
    return true;
}

bool PopPointer(lua_State* L, void** ptr, const char* type_name, int idx)
{
    swig_type_info * pTypeInfo = querySwigType(type_name);
    if (pTypeInfo == 0)
    {
        return false;  
    }

    if(!lua_isuserdata(L,idx))
    {
        return false;
    }

    return SWIG_IsOK(SWIG_ConvertPtr(L, idx, ptr, pTypeInfo, 0));
}

