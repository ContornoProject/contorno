#include <stdlib.h>
#include <string.h>

#include "contorno.h"

CONTORNO_EXPORT void Contorno_RefCountable_Ref(ContornoRefCountable* refcountable) {
	if (refcountable) {
		__sync_add_and_fetch(&refcountable->ref_count, 1);		
	}
}

CONTORNO_EXPORT void Contorno_RefCountable_Unref(ContornoRefCountable* refcountable) {
	if (refcountable) {
		if (!__sync_sub_and_fetch(&refcountable->ref_count, 1)) {
			if (refcountable->ref_free_func) {
				refcountable->ref_free_func(refcountable);
			} else {
				free(refcountable);
			}
		}
	}
}

void FreeObject(void* obj) {
	ContornoObject* object;
	
	if (object) {
		if (object->object_type) {
			free(object->object_type);
		}
		
		if (object->object_implements) {
			int i;
			
			i = 0;
			while (object->object_implements[i]) {
				free(object->object_implements[i]);
				i++;
			}
			Contorno_MemoryManager_Free(NULL, object->object_implements);
		}
		
		Contorno_MemoryManager_Free(NULL, object);
	}
}

CONTORNO_EXPORT ContornoObject* Contorno_Object_Create(char* type) {
	ContornoObject* ret;
	
	ret = Contorno_MemoryManager_Malloc(NULL, sizeof(ContornoObject));
	memset(ret, 0, sizeof(ContornoObject));
	
	ret->object_type = strdup(type);
	ret->ref_free_func = FreeObject;
	
	return ret;
}
