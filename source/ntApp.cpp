#include "stdafx.h"
#include "ntApp.h"
#include "iWindowMsgListen.h"
#include "ntScene.h"
#include "ntLogicControl.h"
#include "ntScriptMgr.h"
#include "ntConsole.h"

static ntApp* g_pApp= NULL;
static const std::wstring appClassName= L"ntApp";
static const std::wstring appTitle= L"ntApp";

ntApp::ntApp(void)
: m_hWnd(0)
, m_pScene(0)
, m_dwLastTime(0)
, m_pConsole(0)
, m_hInstance(0)
{
    NiInit();
    NiImageConverter::SetImageConverter(NiNew NiDevImageConverter);
    NiTexture::SetMipmapByDefault(true);
    NiSourceTexture::SetUseMipmapping(true);
}

ntApp::~ntApp(void)
{
    clearListen();

    delete m_pScene;
    NiShutdown();

    delete m_pConsole;
    delete m_pScriptMgr;
}

void ntApp::addMsgListen(iWindowMsgListen* pListen, bool bDeposit)
{
    m_MsgListen.push_back( Listen(pListen, bDeposit) );
}

void ntApp::removeMsgListen(iWindowMsgListen* pListen)
{
    MsgListenVkt::iterator it= m_MsgListen.begin();
    while( it!= m_MsgListen.end())
    {
        if (it->pListen== pListen)
        {
            m_MsgListen.erase(it);
        }
        ++it;
    }
}

bool ntApp::onMsg(UINT message, WPARAM wParam, LPARAM lParam)
{
    for each (const Listen& p in m_MsgListen)
    {
        if (p.pListen->onMsg(message, wParam, lParam))
        {
            return true;
        }
    }
    return false;
}

INT_PTR CALLBACK DialogProcX(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    return DefWindowProc(hWnd, msg, wp, lp);
}

bool ntApp::init(HINSTANCE hInstance, HWND hWnd)
{
    m_hInstance= hInstance;
    m_hWnd= hWnd;
    m_dwLastTime= timeGetTime();

    m_pConsole= new ntConsole;
    m_pConsole->load();
    m_pConsole->output(L"ntGame startup...");

    m_pScriptMgr= new ntScriptMgr;
    m_pScriptMgr->load();

    m_pScene= new ntScene();
    if (!m_pScene->create())
    {
        return false;
    }
    addMsgListen(m_pScene, false);

    addMsgListen( new ntLogicControl(), true);

    return true;
}

void ntApp::idle()
{
    DWORD dwCurrTime= timeGetTime();
    DWORD dwTime= dwCurrTime- m_dwLastTime;
    m_dwLastTime= dwCurrTime;
    float fDeltaTime= dwTime/ 1000.0f;
    update(fDeltaTime);
    render();
    Sleep(5);
}

ntApp* ntApp::getIns()
{
    return g_pApp;
}

void ntApp::update( float fDeltaTime )
{
    m_pScene->update(fDeltaTime);

    if (m_pConsole)
    {
        m_pConsole->update(fDeltaTime);
    }

    ntScriptMgr::getIns()->update(fDeltaTime);
}

void ntApp::render()
{
    m_pScene->render();
}

void ntApp::clearListen()
{
    MsgListenVkt::iterator it= m_MsgListen.begin();
    while( it!= m_MsgListen.end())
    {
        if (it->bDeposit)
        {
            delete it->pListen;
        }
        ++it;
    }
    m_MsgListen.clear();
}

void ntApp::output( const ntString& rkInfo )
{
    m_pConsole->output(rkInfo);
}

static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (WM_DESTROY== message)
    {
        PostQuitMessage(0);
        return 0;
    }

    if (g_pApp)
    {
        g_pApp->onMsg(message, wParam, lParam);
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}


static ATOM registerAppClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style			= CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc	= wndProc;
    wcex.cbClsExtra		= 0;
    wcex.cbWndExtra		= 0;
    wcex.hInstance		= hInstance;
    wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(NULL));
    wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName	= MAKEINTRESOURCE(NULL);
    wcex.lpszClassName	= appClassName.c_str();
    wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(NULL));
    return RegisterClassEx(&wcex);
}

HWND createAppWindow(HINSTANCE hInstance)
{
    HWND hWnd;
    hWnd = CreateWindow(appClassName.c_str(), appTitle.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        return 0;
    }

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    return hWnd;
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                       LPTSTR lpCmdLine, int nCmdShow )
{

    registerAppClass(hInstance);
    HWND hWnd= createAppWindow(hInstance);

    if (!hWnd)
    {
        return 0;
    }

    g_pApp= new ntApp();
    g_pApp->init(hInstance, hWnd);

    MSG msg= {0};
    while (msg.message != WM_QUIT)
    {
        if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }else
        {
            g_pApp->idle();
        }
    }

    delete g_pApp;
    return 0;
}
