#pragma once
#include "ntPlug.h"

class ntPlugFactory
{
public:
    ntPlugFactory(void);
    ~ntPlugFactory(void);

    ntPlugPtr createPlug(const std::wstring& rkType, const std::wstring& rkName);
};
