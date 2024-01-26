#include <stdlib.h>
#include <string.h>

#include "contorno.h"

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


