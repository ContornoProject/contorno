#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "contorno.h"

void DefaultErrorHandler(ContornoSize size) {
	printf("Failed to allocate %u bytes of memory, exiting.\n", (unsigned int)size);
	exit(1);
}

CONTORNO_EXPORT void Contorno_MemoryManager_Init(ContornoMemoryManager* manager) {
	if (!manager) {
		return;
	}
	
	manager->malloc = &malloc;
	manager->calloc = &calloc;
	manager->realloc = &realloc;
	manager->free = &free;
	manager->error_handler = &DefaultErrorHandler;	
}

CONTORNO_EXPORT void* Contorno_MemoryManager_Malloc(ContornoMemoryManager* manager, ContornoSize size) {
	void* allocation;
	
	if (!manager) {
		return malloc(size);
	}
	
	allocation = manager->malloc(size);
	if (!allocation) {
		if(manager->error_handler) {
			manager->error_handler(size);
		} else {
			return allocation;
		}
	}
	
	return allocation;
}

CONTORNO_EXPORT void* Contorno_MemoryManager_Calloc(ContornoMemoryManager* manager, ContornoSize count, ContornoSize size) {
	void* allocation;
	
	if (!manager) {
		return calloc(count, size);
	}
	
	allocation = manager->calloc(count, size);
	if (!allocation) {
		if(manager->error_handler) {
			manager->error_handler(count*size);
		} else {
			return allocation;
		}
	}
	return allocation;
}

CONTORNO_EXPORT void* Contorno_MemoryManager_Realloc(ContornoMemoryManager* manager, void* allocation, ContornoSize size) {
	void* new_allocation;
	
	if (!manager) {
		return realloc(allocation, size);
	}
	
	new_allocation = manager->realloc(allocation, size);
	if (!allocation) {
		if(manager->error_handler) {
			manager->error_handler(size);
		} else {
			return allocation;
		}
	}
	
	return allocation;
}

CONTORNO_EXPORT void Contorno_MemoryManager_Free(ContornoMemoryManager* manager, void* allocation) {
	if (manager) {
		manager->free(allocation);
	} else {
		free(allocation);
	}
}


CONTORNO_EXPORT void* Contorno_MemoryManager_Memdup(ContornoMemoryManager* manager, void* data, ContornoSize size) { 
	void* allocation;
   
	allocation = Contorno_MemoryManager_Malloc(manager, size);
	if (!allocation) {
		return NULL;
	}
	
	memcpy(allocation, data, size);
	return allocation;
}
