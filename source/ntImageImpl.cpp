#include "stdafx.h"
#include "ntImageImpl.h"

ntImageImpl::ntImageImpl(void)
{
}

ntImageImpl::~ntImageImpl(void)
{
}

void ntImageImpl::create()
{
    //NiSourceTexturePtr spTexture= NiSourceTexture::Create("");

    NiScreenElementsDataPtr spData= NiNew NiScreenElementsData(1, 1, 1);
    m_spScreenElements = NiNew NiScreenElements(spData);

}
