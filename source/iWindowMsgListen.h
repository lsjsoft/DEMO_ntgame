#pragma once

class iWindowMsgListen
{
public:
    virtual ~iWindowMsgListen() {}
    virtual bool onMsg(UINT message, WPARAM wParam, LPARAM lParam)= 0;
};
