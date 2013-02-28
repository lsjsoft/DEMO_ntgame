#pragma once

struct lua_State;
class ntScriptMgr
{
public:
    ntScriptMgr(void);
    ~ntScriptMgr(void);

    void load();
    void update(float fTime);

    bool excute(const ntString& rkString);
    bool excute(const std::string& rkString);

    lua_State* getState() const { return m_pLuaState; }
public:
    static ntScriptMgr* getIns();

protected:
    lua_State* m_pLuaState;
};
