#pragma once
#include "iWindowMsgListen.h"
#include "ntPlug.h"

class ntPlugFactory;

class ntScene: public iWindowMsgListen
{
public:
    ntScene(void);
    ~ntScene(void);

    static ntScene* getIns();

    bool create();
    bool onMsg(UINT message, WPARAM wParam, LPARAM lParam);
    void update(float fDeltaTime);
    void render();

    ntPlugPtr addPlug(const std::wstring& rkPlugType, const std::wstring& rkPlugName);
    bool removePlug(const std::wstring& rkPlugName);
	ntPlugPtr getPlug(const std::wstring& rkPlugName);

    void setDefaultCamera();
    void setCamera(NiCameraPtr spCamera);

    unsigned int draw(NiNodePtr node);

protected:
    void renderPlugs();
    void updatePlugs(float fDeltaTime);

protected:
    NiRendererPtr m_spRenderer;
    NiCameraPtr m_spDefaultCamera;
    NiCameraPtr m_spCurrentCamera;

    typedef std::vector<ntPlugPtr> ntPlugs;
    ntPlugs m_plugs;

    ntPlugFactory* m_pPlugFactory;

    NiVisibleArray* m_kVisible;
    NiCullingProcessPtr m_spCuller;
};
