#pragma once
#include "ntPlug.h"

class ntSimpleNifRender
{
public:
    ntSimpleNifRender();
    ~ntSimpleNifRender(void);

    void setNif(const ntString& rkPathname);

	void unload();
	bool load();

    void render();
    void update(float fDeltaTime);

protected:
    float m_fTime;
    NiNodePtr m_spRootNode;
	ntString m_strPathname;
};

NiSmartPointer(ntSimpleNifRender);
