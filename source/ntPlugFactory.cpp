#include "stdafx.h"
#include "ntPlugFactory.h"
#include "ntSimpleNifRender.h"

ntPlugFactory::ntPlugFactory(void)
{
}

ntPlugFactory::~ntPlugFactory(void)
{
}

ntPlugPtr ntPlugFactory::createPlug(const std::wstring& rkType, 
                                    const std::wstring& rkName)
{
    ntPlugPtr plug= NULL;
    plug= NiNew ntSimpleNifRender(rkName);
    return plug;
}
