#pragma once

class ntPlug: public NiRefObject
{
public:
    ntPlug(const std::wstring& rkName): m_kName(rkName) {}
    virtual ~ntPlug(void) {}

    virtual bool load() = 0;
    virtual void unload() = 0;
    virtual void update(float fDeltaTime)= 0;
    virtual void render() =0;

    const std::wstring& getName() const 
    {
        return m_kName;
    }

protected:
    std::wstring m_kName;
};

NiSmartPointer(ntPlug);
