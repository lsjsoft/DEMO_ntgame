#include "stdafx.h"
#include "ntCodeConvert.h"

#define CP_GBK 936

ntString ntstow(const std::string& rkText)
{
    int iTextLength = MultiByteToWideChar(CP_GBK, 0, rkText.c_str(), 
        (int)rkText.length(), NULL, 0);

    wchar_t * pkTargetText 
        = (wchar_t *)_malloca( (iTextLength + 1) * sizeof(wchar_t));

    if (!pkTargetText)
    {
        return L"";
    }

    MultiByteToWideChar(CP_GBK, 0, rkText.c_str(), 
        (int)rkText.length(), pkTargetText, iTextLength);
    pkTargetText[iTextLength] = L'\0';	
    std::wstring rkWText(pkTargetText);
    _freea(pkTargetText);

    return rkWText;
}

std::string ntwtos(const ntString& rkWText)
{
    int iTextLength = WideCharToMultiByte(CP_GBK, 0, rkWText.c_str(), 
        (int)rkWText.length(), NULL, 0, NULL, NULL);
    char* pkTargetText 
        = (char *)_malloca((iTextLength + 1) * sizeof(char));
    if (!pkTargetText)
    {
        return "";
    }

    WideCharToMultiByte(CP_GBK, 0, rkWText.c_str(), 
        (int)rkWText.length(), pkTargetText, iTextLength, NULL, NULL);
    pkTargetText[iTextLength] = '\0';	
    std::string rkText(pkTargetText);
    _freea(pkTargetText);
    return rkText;
}

