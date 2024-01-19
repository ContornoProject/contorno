#include <stdio.h>
#include <stdlib.h>
#include <contorno.h>

int main(void) {
	char* buffer;
	
	buffer = Contorno_StringUtility_Strnfill(64, 'b');
	
	puts(buffer);
}
