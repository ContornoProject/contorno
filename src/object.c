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

CONTORNO_EXPORT void Contorno_RefCountable_SetFreeFunc(ContornoRefCountable* refcountable, ContornoRefCountableFreeFunc func) {
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
				Contorno_MemoryManager_Free(NULL, object->object_implements[i]);
				i++;
			}
			Contorno_MemoryManager_Free(NULL, object->object_implements);
		}
		
		Contorno_MemoryManager_Free(NULL, object);
	}
}

CONTORNO_EXPORT void Contorno_Object_Fill(ContornoObject* object, char* type, ContornoRefCountableFreeFunc* fillers, ContornoBool dont_fill) {
	int i;
	if (!object || !type || !fillers) {
		return;
	}
	
	i = 0;
	while (fillers[i]) {
		i++;
	}
	
	object->object_implements = NULL;
	object->object_type = Contorno_StringUtility_Strdup(NULL, type);
	object->object_fillers = Contorno_MemoryManager_Memdup(NULL, fillers, sizeof(ContornoRefCountableFreeFunc)*i);
	object->ref_free_func = FreeObject;
	object->ref_count = 1;
	
	if (!dont_fill) {
		i = 0;
		while (object->object_fillers[i]) {
			object->object_fillers[i](object);
			i++;
		}		
	}
}
