# ITStep_WinAPI
Files for Windows API lections and practical

1) Uni - UNICODE support;
2) CWnd.h; CWnd.cpp; Timer.cpp; Timer.rc; resource.h - WinAPI application (example of timer);

stdafx.h - for timer:

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// TODO: reference additional headers your program requires here
