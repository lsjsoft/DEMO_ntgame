#pragma once
#include "ntPlug.h"

class ntSimpleNifRender: public ntPlug
{
public:
    ntSimpleNifRender(const std::wstring& rkName);
    ~ntSimpleNifRender(void);

    virtual bool load();
    virtual void unload();
    virtual void render();
    virtual void update(float fDeltaTime);

protected:
    float fTime;
    NiNodePtr m_spRootNode;
    NiCameraPtr m_spCamera;
    std::wstring m_strPathname;
};

NiSmartPointer(ntSimpleNifRender);
