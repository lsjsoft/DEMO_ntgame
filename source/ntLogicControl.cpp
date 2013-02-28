#include "stdafx.h"
#include "ntLogicControl.h"
#include "ntScene.h"

ntLogicControl::ntLogicControl(void)
{
}

ntLogicControl::~ntLogicControl(void)
{
}

bool ntLogicControl::onMsg( UINT message, WPARAM wParam, LPARAM lParam )
{
    if (message == WM_KEYDOWN)
    {
        if (wParam== K_F1)
        {
            ntScene::getIns()->addPlug(L"", L"Macro");
        }
        else if (wParam == K_F2)
        {
            ntScene::getIns()->removePlug(L"Macro");
        }
    }

    return true;
}
