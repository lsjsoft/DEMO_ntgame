#pragma once

class ntRenderer;
NiSmartPointer(ntRenderer);

class ntRenderer: public NiDX9Renderer
{
    NiDeclareRTTI;

public:
    ntRenderer(void);
    ~ntRenderer(void);

    static ntRendererPtr create(unsigned int uiWidth, unsigned int uiHeight,
        unsigned int uiUseFlags, NiWindowRef kWndDevice);
};
