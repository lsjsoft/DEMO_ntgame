#include "stdafx.h"
#include "ntPlugFactory.h"
#include "ntSimpleNifRenderSet.h"

ntPlugFactory::ntPlugFactory(void)
{
}

ntPlugFactory::~ntPlugFactory(void)
{
}

ntPlugPtr ntPlugFactory::createPlug(const std::wstring& rkType, 
                                    const std::wstring& rkName)
{
    return NiNew ntSimpleNifRenderSet(rkName);
}
