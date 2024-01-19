#ifndef CONTORNO
#define CONTORNO

/* Types */
typedef size_t ContornoSize;
typedef ssize_t ContornoSSize;
typedef unsigned char ContornoUInt8;
typedef signed char ContornoInt8;
typedef unsigned short ContornoUInt16;
typedef signed short ContornoInt16;
typedef unsigned long ContornoUInt32;
typedef signed long ContornoInt32;
typedef enum {
    CONFLIENT_FALSE,
    CONFLIENT_TRUE
} ContornoBool;

/* Memory Management */
typedef void (*ContornoMemoryManagerErrorHandler)(ContornoSize);
typedef void* (*ContornoMemoryManagerMalloc)(ContornoSize);
typedef void* (*ContornoMemoryManagerCalloc)(ContornoSize, ContornoSize);
typedef void* (*ContornoMemoryManagerRealloc)(void*, ContornoSize);
typedef void (*ContornoMemoryManagerFree)(void*);
typedef struct {
	ContornoMemoryManagerMalloc malloc;
	ContornoMemoryManagerCalloc calloc;
	ContornoMemoryManagerRealloc realloc;
	ContornoMemoryManagerFree free;
	
	ContornoMemoryManagerErrorHandler error_handler;
} ContornoMemoryManager;

extern void Contorno_MemoryManager_Init(ContornoMemoryManager* manager);
extern void* Contorno_MemoryManager_Malloc(ContornoMemoryManager* manager, ContornoSize size);
extern void* Contorno_MemoryManager_Calloc(ContornoMemoryManager* manager, ContornoSize count, ContornoSize size);
extern void* Contorno_MemoryManager_Realloc(ContornoMemoryManager* manager, void* allocation, ContornoSize size);
extern void Contorno_MemoryManager_Free(ContornoMemoryManager* manager, void* allocation);

/* String Utilities */
extern char* Contorno_StringUtility_Strrstr(char* string, char* needle);
extern char* Contorno_StringUtility_Strnfill(ContornoSize size, char filler);
extern ContornoBool Contorno_StringUtility_StartsWith(char* string, char* prefix);
extern ContornoBool Contorno_StringUtility_EndsWith(char* string, char* suffix);

/* Module Loader */
typedef struct {
	void* module;
	char* file;
} ContornoModule;

typedef enum {
    CONTORNO_MODULE_LOAD_BIND_LAZY = 1 << 0,
    CONTORNO_MODULE_LOAD_BIND_LOCAL = 1 << 1
} ContornoModuleLoadFlags;

extern ContornoModule* Contorno_Module_Open(char* file, ContornoModuleLoadFlags flags);
extern void* Contorno_Module_LoadSymbol(ContornoModule* module, char* name);
extern char* Contorno_Module_GetFileName(ContornoModule* module);
extern void Contorno_Module_Close(ContornoModule* module);

/* Character Set Conversions */
/* extern char* Contorno_Convert(char* input, ContornoSize input_length, char* input_codeset, char* output_codeset, ContornoSize* bytes_read, ContornoSize* bytes_written); */

#endif
