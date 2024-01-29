#ifndef _WIN32
#define _GNU_SOURCE
#endif
#include <stdlib.h>
#include <string.h>

#include "contorno.h"

#if defined(_WIN32)
#include <libloaderapi.h>

CONTORNO_EXPORT ContornoModule* Contorno_Module_Open(char* file, ContornoModuleLoadFlags flags) {
	ContornoModule* ret;

	if (!file) { 
		return NULL;
	}

	ret = Contorno_MemoryManager_Malloc(NULL, sizeof(ContornoModule));
	if (!ret) {
		return NULL;
	}

	ret->file = Contorno_StringUtility_Strdup(NULL, file);
	ret->module = LoadLibrary(file);
	
	return ret;
} 

CONTORNO_EXPORT char* Contorno_Module_GetFileName(ContornoModule* module) {
	if (!module) {
		return NULL;
	}

	if (!module->file) {
		return NULL;
	}

	return  Contorno_StringUtility_Strdup(NULL, module->file);
}

CONTORNO_EXPORT void Contorno_Module_Close(ContornoModule* module) {
	if (!module) {
		return;
	}
	
	if (module->module) {
		FreeLibrary((HMODULE)module->module);
	}	

	if (module->file) {
		Contorno_MemoryManager_Free(NULL, module->file);
	}		
	
	free(module);	
}

CONTORNO_EXPORT void* Contorno_Module_LoadSymbol(ContornoModule* module, char* name) {
	if (!module) {
		return NULL;
	}

    return GetProcAddress((HMODULE)module->module, name);
}

CONTORNO_EXPORT char* Contorno_Module_GetCurrentPath(void* func) {
	char* filename;
	HMODULE cmodule;

	filename = Contorno_MemoryManager_Calloc(NULL, MAX_PATH, sizeof(char));
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |  GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)func, &cmodule)
	GetModuleFileName(cmodule, filename, sizeof(filename))
	
    return filename;
}

#else

#include <dlfcn.h>

CONTORNO_EXPORT ContornoModule* Contorno_Module_Open(char* file, ContornoModuleLoadFlags flags) {
	ContornoModule* ret;
	int dl_flags;
	
	if (!file) {
		return NULL;
	}
	
	ret = Contorno_MemoryManager_Malloc(NULL, sizeof(ContornoModule));
	if (!ret) {
		return NULL;
	}
	ret->file = Contorno_StringUtility_Strdup(NULL, file);
	
	dl_flags = 0;
	if (flags & CONTORNO_MODULE_LOAD_BIND_LAZY) {
		dl_flags |= RTLD_LAZY;
	} else {
		dl_flags |= RTLD_NOW;
	}
	if (flags & CONTORNO_MODULE_LOAD_BIND_LOCAL) {
		dl_flags |= RTLD_LOCAL;
	}
	
	ret->module = dlopen(file, dl_flags);
	return ret;
}

CONTORNO_EXPORT char* Contorno_Module_GetFileName(ContornoModule* module) {
	if (!module) {
		return NULL;
	}

	if (!module->file) {
		return NULL;
	}
		
	return Contorno_StringUtility_Strdup(NULL, module->file);
}


CONTORNO_EXPORT void Contorno_Module_Close(ContornoModule* module)  {
	if (!module) {
		return;
	}
	
	if (module->module) {
		dlclose(module->module);
	}	

	if (module->file) {
		Contorno_MemoryManager_Free(NULL, module->file);
	}		
	
	free(module);
}

CONTORNO_EXPORT char* Contorno_Module_GetCurrentPath(void* func) {
    Dl_info info;
    
    dladdr(func, &info);
    
    return Contorno_StringUtility_Strdup(NULL, (char*)info.dli_fname);
}

#endif
