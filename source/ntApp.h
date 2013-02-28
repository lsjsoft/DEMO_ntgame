#pragma once

class ntScene;
class iWindowMsgListen;
class ntScriptMgr;
class ntConsole;

class ntApp
{
public:
    ntApp(void);
    ~ntApp(void);

    void clearListen();
    static ntApp* getIns();

    void addMsgListen(iWindowMsgListen* pListen, bool bDeposit);
    void removeMsgListen(iWindowMsgListen* pListen);
    bool onMsg(UINT message, WPARAM wParam, LPARAM lParam);
    bool init(HINSTANCE, HWND);
    void idle();

    HWND getHandle() const { return m_hWnd; }
    HINSTANCE getInstance() const { return m_hInstance; }

    void output(const ntString& rkInfo);
protected:
    void update(float fDeltaTime);
    void render();

protected:
    struct Listen
    {
        Listen(iWindowMsgListen* p, bool b)
        : pListen(p)
        , bDeposit(b)
        {
        }

        iWindowMsgListen* pListen;
        bool bDeposit;
    };
    typedef std::vector<Listen> MsgListenVkt;
    MsgListenVkt m_MsgListen;
    HINSTANCE m_hInstance;
    HWND m_hWnd;
    ntScene* m_pScene;
    DWORD m_dwLastTime;
    ntScriptMgr* m_pScriptMgr;
    ntConsole* m_pConsole;
};
