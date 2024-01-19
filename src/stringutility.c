#include <stdlib.h>
#include <string.h>

#include "contorno.h"

CONTORNO_EXPORT char* Contorno_StringUtility_Strrstr(char* string, char* needle) {
	char *tmp;
	char *tmp2;
	char* tmp_string;
	
	tmp_string = string;
	tmp = NULL;
	if (!needle[0]) {
		return tmp_string + strlen(tmp_string);
	}
	
	for (;;) {
		tmp2 = strstr(tmp_string, needle);
		if (!tmp2) {
			return tmp;
		}
		tmp = tmp2;
		tmp_string = tmp2 + 1;
	}
}

CONTORNO_EXPORT char* Contorno_StringUtility_Strnfill(ContornoSize size, char filler) {
	char* string;
	int i;
	
	string = Contorno_MemoryManager_Malloc(NULL, size+1);
	if (!string) {
		return NULL;
	}
	
	for (i = 0; i < size; i++) {
		string[i] = filler;
	}	
	string[i] = '\0';
		
	return string;
}

CONTORNO_EXPORT ContornoBool Contorno_StringUtility_StartsWith(char* string, char* prefix) {
	if (!string || !prefix) {
		if (string == prefix) {
			return CONFLIENT_TRUE;		
		} else {
			return CONFLIENT_FALSE;			
		}
	}
	
	if(!strncmp(string, prefix, strlen(prefix))) {
		return CONFLIENT_TRUE;
	} else {
		return CONFLIENT_FALSE;
	}
}

CONTORNO_EXPORT ContornoBool Contorno_StringUtility_EndsWith(char* string, char* suffix) {
	ContornoSize string_length;
	ContornoSize suffix_length;
	
	if (!string || !suffix) {
		if (string == suffix) {
			return CONFLIENT_TRUE;		
		} else {
			return CONFLIENT_FALSE;			
		}
	}
		
	string_length = strlen(string);
	suffix_length =	strlen(suffix);
	
	if ((string_length >= suffix_length) && (!strcmp(string + (string_length-suffix_length), suffix))) {
		return CONFLIENT_TRUE;
	} else {
		return CONFLIENT_FALSE;
	}
}


