#include "Log.hpp"
#include <windows.h>

void RaiseDebugBreak()
{
#if NDEBUG
	return;
#else	
	// TODO: Add support for Non-Windows platforms
	if (IsDebuggerPresent()) {
		__debugbreak();
		return;
	}
#endif
}
