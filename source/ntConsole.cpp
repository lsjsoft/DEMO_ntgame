#include "stdafx.h"
#include "ntConsole.h"
#include "ntApp.h"
#include "ntScriptMgr.h"
#include "ntCodeConvert.h"

#pragma warning(disable: 4311)
#pragma warning(disable: 4312)

static ntConsole* g_pIns= NULL;

ntConsole* ntConsole::getIns()
{
    return g_pIns;
}

ntConsole::ntConsole()
: m_handle(0)
, m_fpStd(0)
, m_fpErr(0)
, m_inputHandle(0)
, m_bBlock(false)
{
    g_pIns= this;

    m_inputBuff= new ntStrings;
    m_excuteBuff= new ntStrings;
}

ntConsole::~ntConsole()
{
    delete m_inputBuff;
    delete m_excuteBuff;
    unload();
    g_pIns= NULL;
}


DWORD WINAPI inputThread(LPVOID Data)
{
    HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);

    static const unsigned int maxSize = 1024;
    wchar_t buff[maxSize];  

    while(1)
    {
        DWORD num;
        memset(buff, 0, maxSize);
        ReadConsole(hin, buff, maxSize, &num, NULL);

        if (num>0)
        {
            ntConsole* pConsole= ntConsole::getIns();
            if (!pConsole)
            {
                return 0;
            }

            pConsole->putCmd(ntString(buff));
        }
    }

    return 0;
}

void ntConsole::load()
{
    AllocConsole();

    freopen("CONOUT$", "wb", stdout);
    freopen("CONOUT$", "wb", stderr);

    DWORD dwThreadId= 0;
    m_inputHandle = CreateThread(
        NULL,
        0,
        inputThread,
        0,
        0,
        &dwThreadId);
}

void ntConsole::unload()
{
    fclose(stdout);
    fclose(stderr);

    TerminateThread(m_inputHandle, 0);
    CloseHandle(m_inputHandle);
    m_inputHandle= 0;

    FreeConsole();
}

void ntConsole::output( const ntString& str )
{
    output(ntwtos(str).c_str());
}

void ntConsole::output( const char* szText )
{
    if (szText)
    {
        printf(szText);
        printf("\n");
    }
}


void ntConsole::excute(const ntString& cmd)
{
    ntScriptMgr::getIns()->excute(cmd);
}

void ntConsole::update(float fDeltaTime)
{
    if (m_excuteBuff->empty() && m_inputBuff->empty())
    {
        return;
    }

    if (!m_excuteBuff->empty())
    {
        for each(const ntString& s in *m_excuteBuff)
        {
            excute(s);
        }
        m_excuteBuff->clear();
    }

    swapBuff();
}

void ntConsole::putCmd( const ntString& cmd )
{
    while(m_bBlock);
    m_inputBuff->push_back(cmd);
}

void ntConsole::swapBuff()
{
    m_bBlock= true;
    std::swap(m_excuteBuff, m_inputBuff);
    m_bBlock= false;
}
