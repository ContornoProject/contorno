#include <stdlib.h>
#include <string.h>

#include "contorno.h"

CONTORNO_EXPORT void Contorno_RefCountable_Ref(ContornoRefCountable* refcountable) {
	if (refcountable) {
		Contorno_Atomic_Increment(&refcountable->ref_count);		
	}
}

CONTORNO_EXPORT void Contorno_RefCountable_Unref(ContornoRefCountable* refcountable) {
	if (refcountable) {
		if (!Contorno_Atomic_Decrement(&refcountable->ref_count)) {
			if (refcountable->ref_free_func) {
				refcountable->ref_free_func(refcountable);
			} else {
				free(refcountable);
			}
		}
	}
}

CONTORNO_EXPORT void Contorno_RefCountable_SetFreeFunc(ContornoRefCountable* refcountable, ContornoRefCountableFree func) {
	if (refcountable && func) {
		refcountable->ref_free_func = func;
	}	
}

void FreeObject(void* obj) {
	ContornoObject* object;
	
	object = (ContornoObject*)obj;
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
	if (!ret) {
		return NULL;
	}
	
	memset(ret, 0, sizeof(ContornoObject));
	
	ret->object_type = strdup(type);
	ret->ref_free_func = FreeObject;
	
	return ret;
}
