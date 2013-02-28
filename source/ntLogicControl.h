#pragma once
#include "iWindowMsgListen.h"

class ntLogicControl: public iWindowMsgListen
{
public:
    ntLogicControl(void);
    ~ntLogicControl(void);

    virtual bool onMsg(UINT message, WPARAM wParam, LPARAM lParam);
};
