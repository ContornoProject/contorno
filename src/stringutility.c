#include <stdlib.h>
#include <string.h>

#include "contorno.h"

CONTORNO_EXPORT ContornoBool Contorno_StringUtility_StartsWith(char* string, char* prefix) {
	if(!strncmp(string, prefix, strlen(prefix))) {
		return CONTORNO_TRUE;
	} else {
		return CONTORNO_FALSE;
	}
}

CONTORNO_EXPORT ContornoBool Contorno_StringUtility_EndsWith(char* string, char* suffix) {
	ContornoSize string_length;
	ContornoSize suffix_length;
	
	string_length = strlen(string);
	suffix_length =	strlen(suffix);
	
	if ((string_length >= suffix_length) && (!strcmp(string + (string_length-suffix_length), suffix))) {
		return CONTORNO_TRUE;
	} else {
		return CONTORNO_FALSE;
	}
}

CONTORNO_EXPORT char *Contorno_StringUtility_Strdup(ContornoMemoryManager* manager, char *string) {
	char *ret;
	
	ret = Contorno_MemoryManager_Malloc(manager, strlen(string) + 1);
	if (ret) {
		strcpy(ret, string);
 	}
	
	return ret;
}



