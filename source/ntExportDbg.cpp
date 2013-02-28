#include "stdafx.h"
#include "ntExportDbg.h"
#include "ntApp.h"
#include "ntCodeConvert.h"
#include "ntConsole.h"
#include "ntScene.h"

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
�� A' = T1 * A��T1Ϊ���1�ı任����
���� B' = A' = T2 * (B +��T)��T2Ϊ���2�ı任����
��ôT = T1 * A * inv(T2) - B

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
