#include "stdafx.h"
#include "ntScene.h"
#include "ntRenderer.h"
#include "ntApp.h"
#include "ntPlug.h"
#include "ntPlugFactory.h"

ntScene* g_pScene;

ntScene* ntScene::getIns()
{
    return g_pScene;
}

ntScene::ntScene(void)
{
    g_pScene= this;
    m_pPlugFactory= new ntPlugFactory;
}

ntScene::~ntScene(void)
{
    m_spDefaultCamera= NULL;
    m_spCurrentCamera= NULL;
    m_spCuller= NULL;
    delete m_kVisible;
    delete m_pPlugFactory;
    g_pScene= NULL;
}

bool ntScene::onMsg( UINT message, WPARAM wParam, LPARAM lParam )
{
    if (message== WM_SIZE)
    {
        NiDX9Renderer* pkDX9Renderer = NiSmartPointerCast(
            NiDX9Renderer, m_spRenderer);

        pkDX9Renderer->Recreate(0, 0, (NiDX9Renderer::FlagType)
            (NiDX9Renderer::USE_MULTITHREADED | 
            NiDX9Renderer::USE_STENCIL));
    }
    return false;
}

bool ntScene::create()
{
    HWND hWnd= ntApp::getIns()->getHandle();

    m_spRenderer= ntRenderer::create(0, 0, (NiDX9Renderer::FlagType)
        (NiDX9Renderer::USE_MULTITHREADED | NiDX9Renderer::USE_STENCIL),
        hWnd);

    m_spRenderer->SetBackgroundColor( NiColorA(0.0f, 0.0f, 0.0f, 0.0f));

    m_kVisible= NiNew NiVisibleArray;
    m_spCuller= NiNew NiCullingProcess(m_kVisible);

    m_spDefaultCamera= NiNew NiCamera();
    NiFrustum Frustum= m_spDefaultCamera->GetViewFrustum();
    Frustum.m_fNear= 1.0f;
    Frustum.m_fFar = 10000.0f;
    m_spDefaultCamera->SetViewFrustum(Frustum);
    m_spDefaultCamera->SetTranslate( NiPoint3(0.0f, 1000, 1000));
    m_spDefaultCamera->Update(0.0f);
    m_spDefaultCamera->LookAtWorldPoint( NiPoint3(0.0f, 0.0f, 0.0f), NiPoint3::UNIT_Z);
    m_spDefaultCamera->SetMaxFarNearRatio(10000.0f);
    m_spDefaultCamera->SetMinNearPlaneDist(0.0001f);
    m_spDefaultCamera->Update(0.0f);
    
    setDefaultCamera();

    return true;
}

void ntScene::update( float fDeltaTime )
{
    updatePlugs(fDeltaTime);
}

void ntScene::render()
{
    NiDX9Renderer* pRender = static_cast<NiDX9Renderer*>(
        NiRenderer::GetRenderer());

    m_spRenderer->BeginFrame();
    m_spRenderer->BeginUsingDefaultRenderTargetGroup(NiRenderer::CLEAR_ALL);

    renderPlugs();

    m_spRenderer->EndUsingRenderTargetGroup();
    m_spRenderer->EndFrame();
    m_spRenderer->DisplayFrame();
}

void ntScene::renderPlugs()
{
    for each (ntPlugPtr p in m_plugs)
    {
        p->render();
    }
}

void ntScene::updatePlugs( float fDeltaTime )
{
    for each (ntPlugPtr p in m_plugs)
    {
        p->update(fDeltaTime);
    }
}

ntPlugPtr ntScene::addPlug( const std::wstring& rkPlugType, const std::wstring& rkPlugName )
{
    ntPlugPtr plug= m_pPlugFactory->createPlug(rkPlugType, rkPlugName);
    if (plug->load())
    {
        m_plugs.push_back(plug);
    }
    else
    {
        plug= NULL;
    }
    return plug;
}

bool ntScene::removePlug( const std::wstring& rkPlugName )
{
    ntPlugs::iterator it = m_plugs.begin();
    while(it!= m_plugs.end())
    {
        if ( (*it)->getName()== rkPlugName)
        {
            (*it)->unload();
            m_plugs.erase(it);
            return true;
        }
        it++;
    }

    return false;
}

unsigned int ntScene::draw( NiNodePtr node )
{
    m_spRenderer->SetCameraData(m_spCurrentCamera);
    m_spCuller->Process(m_spCurrentCamera, node, m_kVisible);
    unsigned int uiCount= NiDrawVisibleArray(m_spCurrentCamera, *m_kVisible);
    m_kVisible->RemoveAll();
    return uiCount;
}

void ntScene::setDefaultCamera()
{
    setCamera(m_spDefaultCamera);
}

void ntScene::setCamera( NiCameraPtr spCamera )
{
    m_spCurrentCamera= spCamera;
}
