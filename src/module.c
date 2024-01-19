#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include "contorno.h"
#include "symbolvisibility.h"

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
	ret->file = strdup(file);
	
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
		
	return strdup(module->file);
}


CONTORNO_EXPORT void Contorno_Module_Close(ContornoModule* module)  {
	if (!module) {
		return;
	}
	
	if (module->module) {
		dlclose(module->module);
	}	

	if (module->file) {
		free(module->file);
	}		
	
	free(module);
}

CONTORNO_EXPORT void* Contorno_Module_LoadSymbol(ContornoModule* module, char* name) {
	char* error;
	void* ret;

	if (!module) {
		return NULL;
	}
	
	if (!module->module) {
		return NULL;
	}	
	
	ret = dlsym(module->module, name);
	error = dlerror();
    if (error) {
        return NULL;
    }
    
    return ret;
}




