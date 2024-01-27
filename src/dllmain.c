#include <stdio.h>

#include "contorno.h"

#if defined(_WIN32) 
BOOL WINAPI DLLMain(HMODULE hModule, DWORD ul_reason_to_call, LPVOID lpReserved) {
    switch (ul_reason_to_call) {
        case DLL_PROCESS_ATTACH:
            break;
        case DLL_THREAD_ATTACH:
		    break;
	    case DLL_THREAD_DETACH:            
		    break;
	    case DLL_PROCESS_DETACH:
		    break;
    }
    
    return TRUE;
}
#endif
