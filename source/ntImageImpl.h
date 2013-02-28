#pragma once
#include "ntImage.h"

class ntImageImpl: public ntImage
{
public:
    ntImageImpl(void);
    ~ntImageImpl(void);

    void create();
protected:
    NiScreenElementsPtr m_spScreenElements;
};
