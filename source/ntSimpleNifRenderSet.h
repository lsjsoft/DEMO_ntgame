#pragma once
#include "ntPlug.h"
class ntSimpleNifRender;

class ntSimpleNifRenderSet: public ntPlug
{
public:
	ntSimpleNifRenderSet(const ntString& rkName);
	~ntSimpleNifRenderSet(void);

	void addNif(const ntString& rkNifPathname);
	void removeAll();

	void reload();

	virtual bool load();
	virtual void unload();
	virtual void render();
	virtual void update(float fDeltaTime);

protected:
	typedef std::vector<ntSimpleNifRender*> ntSimpleNifRenderPtrs;
	ntSimpleNifRenderPtrs m_nifs;
};
