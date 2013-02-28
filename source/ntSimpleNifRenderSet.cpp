#include "stdafx.h"
#include "ntSimpleNifRenderSet.h"
#include "ntSimpleNifRender.h"

ntSimpleNifRenderSet::ntSimpleNifRenderSet(const ntString& rkName)
: ntPlug(rkName)
{
}

ntSimpleNifRenderSet::~ntSimpleNifRenderSet(void)
{
}

void ntSimpleNifRenderSet::addNif( const ntString& rkNifPathname )
{
	ntSimpleNifRender* obj= new ntSimpleNifRender();
	obj->setNif(rkNifPathname);
	obj->load();
	m_nifs.push_back(obj);
}

bool ntSimpleNifRenderSet::load()
{
	for each (ntSimpleNifRender* obj in m_nifs)
	{
		obj->load();
	}

	return true;
}

void ntSimpleNifRenderSet::unload()
{
	for each (ntSimpleNifRender* obj in m_nifs)
	{
		obj->unload();
	}
}

void ntSimpleNifRenderSet::render()
{
	for each (ntSimpleNifRender* obj in m_nifs)
	{
		obj->render();
	}
}

void ntSimpleNifRenderSet::update( float fDeltaTime )
{
	for each (ntSimpleNifRender* obj in m_nifs)
	{
		obj->update(fDeltaTime);
	}
}

void ntSimpleNifRenderSet::reload()
{
	unload();
	load();
}

void ntSimpleNifRenderSet::removeAll()
{
	for each (ntSimpleNifRender* obj in m_nifs)
	{
		delete obj;
	}

	m_nifs.clear();
}
