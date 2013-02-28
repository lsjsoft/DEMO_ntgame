// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <mmsystem.h>


#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

#include <string>

#ifdef _DEBUG
    #define NIDEBUG
#else
    #define NISHIPPING
#endif

#pragma warning(disable: 4267)
#pragma warning(disable: 4204)

#include "NiBuildConfiguration.h"

#include <NiSystem.h>
#include <NiMain.h>
#include <NiAnimation.h>
#include <NiDX9Renderer.h>
#include <NiStandardAllocator.h>
#include <NiDX9SystemDesc.h>
#include <NiParticle.h>
#include <NiCollision.h>
#include <NiPortal.h>
#include <NiScreenTexture.h>
#include <NiSourceTexture.h>
#include <NiPixelData.h>
#include <NiD3D10Renderer.h>

#pragma comment(lib, "NiMain.lib")
#pragma comment(lib, "NiSystem.lib")
#pragma comment(lib, "NiDX9Renderer.lib")
#pragma comment(lib, "NiAnimation.lib")
#pragma comment(lib, "NiParticle.lib")
#pragma comment(lib, "NiCollision.lib")
#pragma comment(lib, "NiPortal.lib")

typedef std::wstring ntString;
typedef std::vector<ntString> ntStrings;
