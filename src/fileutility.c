#include <stdlib.h>
#include <string.h>

#include "contorno.h"

#if defined(_WIN32)
CONTORNO_EXPORT char* Contorno_FileUtility_Dirname(char* file) {
	char* ret;
	
	ret = Contorno_StringUtility_Strdup(NULL, file);
	PathRemoveFileSpecA(ret);
	
	return ret;
}
#else
#include <libgen.h>
#include <unistd.h>
#include <limits.h>

CONTORNO_EXPORT char* Contorno_FileUtility_Dirname(char* file) {
	char* cfile;
	char* ret;
	
	cfile = Contorno_StringUtility_Strdup(NULL, file);
	ret = Contorno_StringUtility_Strdup(NULL, dirname(cfile));
	Contorno_MemoryManager_Free(NULL, cfile);
	
	return ret;
}

CONTORNO_EXPORT char* Contorno_FileUtility_Getcwd() {
	char *cwd;
	
	cwd = Contorno_MemoryManager_Calloc(NULL, PATH_MAX, sizeof(char*));
	getcwd(cwd, PATH_MAX);
	
	return cwd;
}
#endif
