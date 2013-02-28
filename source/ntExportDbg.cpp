#include "stdafx.h"
#include "ntExportDbg.h"
#include "ntApp.h"
#include "ntCodeConvert.h"
#include "ntConsole.h"
#include "ntScene.h"
#include "ntSimpleNifRenderSet.h"

void print( const char* str )
{
    if (str)
    {
        ntConsole::getIns()->output(str);
    }
}

void addPlug(const char* plugType, const char* plugName)
{
    if (plugType && plugName)
    {
        ntScene::getIns()->addPlug(ntstow(plugType), ntstow(plugName));
    }
}

void removePlug( const char* plugName )
{
    ntScene::getIns()->removePlug(ntstow(plugName));
}


/** 
设 A' = T1 * A，T1为相机1的变换矩阵。
现在 B' = A' = T2 * (B +　T)，T2为相机2的变换矩阵。
那么T = T1 * A * inv(T2) - B

T1*A = T2*(B+T)
inv(T2)*T1*A= iniv(T2)*T2*(B+T)
*/

void calc(NiCamera* pSrc, const NiPoint3& rkSrcPos, 
          NiCamera* pDst, const NiPoint3& rkDstPos,
          NiPoint3& rTrans)
{
    const NiTransform& srcTransform= pSrc->GetWorldTransform();
    NiTransform invDstTransform;
    pDst->GetWorldTransform().Invert(invDstTransform);
    NiPoint3 v= invDstTransform * srcTransform * rkSrcPos - rkDstPos;  
}

void addNif( const char* plugName, const char* nifName )
{
	if (!plugName || !nifName)
	{
		return;
	}

	ntPlug* plug= ntScene::getIns()->getPlug(ntstow(plugName));
	ntSimpleNifRenderSet* nifRender= dynamic_cast<ntSimpleNifRenderSet*>(plug);
	if (!nifRender)
	{
		return;
	}

	nifRender->addNif( ntstow(nifName));
}

void clearNif( const char* plugName )
{
	if (!plugName)
	{
		return;
	}

	ntPlug* plug= ntScene::getIns()->getPlug(ntstow(plugName));
	ntSimpleNifRenderSet* nifRender= dynamic_cast<ntSimpleNifRenderSet*>(plug);
	if (!nifRender)
	{
		return;
	}

	nifRender->removeAll();
}

