#pragma once

class ntConsole
{
public:
    ntConsole();
    ~ntConsole();

    static ntConsole* getIns();

    void output(const ntString& rkText);
    void output(const char* szText);

    void update(float fDeltaTime);

    void swapBuff();
    void putCmd(const ntString& cmd);

    void load();
    void unload();
    void excute(const ntString& cmd);

protected:
    HANDLE m_handle;
    FILE* m_fpStd;
    FILE* m_fpErr;
    HANDLE m_inputHandle;

    ntStrings* m_inputBuff;
    ntStrings* m_excuteBuff;
    volatile bool m_bBlock;
};
