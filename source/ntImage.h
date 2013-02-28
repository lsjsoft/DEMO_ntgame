#pragma once

class ntImage: NiRefObject
{
public:
    ntImage(void) {}
    virtual ~ntImage(void) {}
    virtual void render() = 0;
};
