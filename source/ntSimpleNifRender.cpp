#include "stdafx.h"
#include "ntSimpleNifRender.h"
#include "ntCodeConvert.h"
#include "ntScene.h"

static void getTimeLine(NiAVObject* pkObject, float& minTime, float& maxTime)
{
    if (!pkObject)
    {
        return;
    }

    NiTimeController* pkController = pkObject->GetControllers();
    while(pkController)
    {
        if(pkController->GetBeginKeyTime() < minTime)
        {
            minTime = pkController->GetBeginKeyTime();
        }

        if(pkController->GetEndKeyTime() > maxTime)
        {
            maxTime = pkController->GetEndKeyTime();
        }

        pkController = pkController->GetNext();
    }

    if (NiIsKindOf(NiNode, pkObject))
    {
        NiNode* pkNode = (NiNode*)pkObject;
        for (unsigned int ui = 0; ui < pkNode->GetArrayCount(); ui++)
        {
            getTimeLine(pkNode->GetAt(ui), minTime, maxTime);
        }
    }
}

/*
static NiCamera* findCamera(NiAVObject* pkObject)
{
    if (NiIsKindOf(NiCamera, pkObject))
    {
        return (NiCamera*)pkObject;
    }
    else if (NiIsKindOf(NiNode, pkObject))
    {
        NiNode* pkNode = (NiNode*)pkObject;

        for (unsigned int ui = 0; ui < pkNode->GetArrayCount(); ui++)
        {
            NiCamera* pCamear= findCamera(pkNode->GetAt(ui));
            if (pCamear)
            {
                return pCamear;
            }
        }
    }

    return NULL;
}

*/

ntSimpleNifRender::ntSimpleNifRender(const std::wstring& rkName)
: ntPlug(rkName)
, fTime(0.0f)
{
}

ntSimpleNifRender::~ntSimpleNifRender(void)
{
}

void ntSimpleNifRender::render()
{
    if (m_spRootNode)
    {
        ntScene::getIns()->draw(m_spRootNode);
    }
}

void ntSimpleNifRender::update( float fDeltaTime )
{
    fTime+= fDeltaTime;
    if (m_spRootNode)
    {
        m_spRootNode->Update(fTime);
    }
}

bool ntSimpleNifRender::load()
{
    m_strPathname = L"../data/effect/BUFF_FX042.nif";

    NiStream Stream;
    if (! Stream.Load( ntwtos(m_strPathname).c_str()))
    {
        return false;
    }

    if (Stream.GetObjectCount() == 0)
    {
        return false;
    }

    m_spRootNode= (NiNode*)Stream.GetObjectAt(0);
    if (!m_spRootNode)
    {
        return false;
    }

    m_spRootNode->UpdateProperties();
    m_spRootNode->UpdateEffects();
    m_spRootNode->Update(0.0f);

    //float minTime=0.0f, maxTime=0.0f;
    //getTimeLine(m_spRootNode, minTime, maxTime);

    m_spRootNode->UpdateNodeBound();
    m_spRootNode->UpdateWorldBound();
    m_spRootNode->SetScale(1.0f);
    m_spRootNode->SetTranslate(NiPoint3(0.0f, 0.0f, 0.0f));
    m_spRootNode->Update(0.0f);

    NiTimeController::StartAnimations(m_spRootNode, 0.0f);

    return true;
}

void ntSimpleNifRender::unload()
{
    m_spRootNode= NULL;
}
