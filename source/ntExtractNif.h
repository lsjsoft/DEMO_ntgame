#pragma once

class ntExtractNif
{
public:
    ntExtractNif(void);
    ~ntExtractNif(void);

    bool extractTexture(const ntString& nifFile, ntStrings& textures);
};
