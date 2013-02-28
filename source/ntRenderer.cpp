#include "stdafx.h"
#include "ntRenderer.h"

NiImplementRTTI(ntRenderer,NiDX9Renderer);

ntRenderer::ntRenderer(void){
}

ntRenderer::~ntRenderer(void){
}


static bool findPerfHUD(unsigned int& ruiAdapterIndex, 
                        NiDX9Renderer::DeviceDesc& rDesc)
{
    const NiDX9SystemDesc* pkDX9SystemDesc = NiDX9Renderer::GetSystemDesc();
    if (!pkDX9SystemDesc)
    {
        return false;
    }

    unsigned int uiAdapterCount = pkDX9SystemDesc->GetAdapterCount();
    for (unsigned int i = 0; i<uiAdapterCount; i++)
    {
        const NiDX9AdapterDesc* pkAdapter= pkDX9SystemDesc->GetAdapter(i);
        if (pkAdapter)
        {
            const char* pcAdapterName = pkAdapter->GetStringDescription();
            if (strstr(pcAdapterName, "PerfHUD"))
            {
                ruiAdapterIndex = i;
                rDesc = NiDX9Renderer::DEVDESC_REF_MIXEDVERTEX;
                return true;
            }
        }
    }

    return false;
}

ntRendererPtr ntRenderer::create(unsigned int uiWidth, unsigned int uiHeight, 
                                 unsigned int uiUseFlags, NiWindowRef kWndDevice )
{
    unsigned int uiAdapter = D3DADAPTER_DEFAULT;
    NiDX9Renderer::DeviceDesc eDevType = NiDX9Renderer::DEVDESC_PURE;

    unsigned int perfHudAdapter= D3DADAPTER_DEFAULT;
    NiDX9Renderer::DeviceDesc perfHudDevType = NiDX9Renderer::DEVDESC_PURE;
    if (findPerfHUD(perfHudAdapter, perfHudDevType))
    {
        uiAdapter= perfHudAdapter;
        eDevType= perfHudDevType;
    }

    ntRendererPtr renderObj= NiNew ntRenderer();

    ms_kD3DCriticalSection.Lock();

    renderObj->Initialize(uiWidth, uiHeight, uiUseFlags, kWndDevice, NULL,
        uiAdapter, eDevType, FBFMT_UNKNOWN, DSFMT_UNKNOWN, PRESENT_INTERVAL_ONE,
        SWAPEFFECT_DEFAULT, FBMODE_DEFAULT, 1, REFRESHRATE_DEFAULT);

    ms_kD3DCriticalSection.Unlock();

    return renderObj;
}
