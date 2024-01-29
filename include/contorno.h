#ifndef CONTORNO
#define CONTORNO

#if defined(_WIN32)
    #include <windows.h>
    #include <basetsd.h>
    
    typedef SSIZE_T ssize_t;

    #define CONTORNO_EXPORT __declspec(dllexport)
    #define CONTORNO_PATH_SEPARATOR "\\"
#else
    #define CONTORNO_EXPORT __attribute__((visibility("default")))
    #define CONTORNO_PATH_SEPARATOR "/"
#endif

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
    CONTORNO_FALSE,
    CONTORNO_TRUE
} ContornoBool;

/* Atomics */
#ifdef __GNUC__
	#define Contorno_Atomic_Increment(a) __sync_add_and_fetch((a), 1)
#elif defined (_WIN32)
	#define Contorno_Atomic_Increment(a) InterlockedIncrement((a))
#endif

#ifdef __GNUC__
	#define Contorno_Atomic_Decrement(a) __sync_sub_and_fetch((a), 1)
#elif defined (_WIN32)
	#define Contorno_Atomic_Decrement(a) InterlockedDecrement((a))
#endif

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

extern CONTORNO_EXPORT void Contorno_MemoryManager_Init(ContornoMemoryManager* manager);
extern CONTORNO_EXPORT void* Contorno_MemoryManager_Malloc(ContornoMemoryManager* manager, ContornoSize size);
extern CONTORNO_EXPORT void* Contorno_MemoryManager_Calloc(ContornoMemoryManager* manager, ContornoSize count, ContornoSize size);
extern CONTORNO_EXPORT void* Contorno_MemoryManager_Realloc(ContornoMemoryManager* manager, void* allocation, ContornoSize size);
extern CONTORNO_EXPORT void Contorno_MemoryManager_Free(ContornoMemoryManager* manager, void* allocation);
extern CONTORNO_EXPORT void* Contorno_MemoryManager_Memdup(ContornoMemoryManager* manager, void* data, ContornoSize size);

/* String Utilities */
extern CONTORNO_EXPORT ContornoBool Contorno_StringUtility_StartsWith(char* string, char* prefix);
extern CONTORNO_EXPORT ContornoBool Contorno_StringUtility_EndsWith(char* string, char* suffix);
extern CONTORNO_EXPORT char *Contorno_StringUtility_Strdup(ContornoMemoryManager* manager, char *string);

/* Module Loader */
typedef struct {
	void* module;
	char* file;
} ContornoModule;

typedef enum {
    CONTORNO_MODULE_LOAD_BIND_LAZY = 1 << 0,
    CONTORNO_MODULE_LOAD_BIND_LOCAL = 1 << 1
} ContornoModuleLoadFlags;

extern CONTORNO_EXPORT ContornoModule* Contorno_Module_Open(char* file, ContornoModuleLoadFlags flags);
extern CONTORNO_EXPORT void* Contorno_Module_LoadSymbol(ContornoModule* module, char* name);
extern CONTORNO_EXPORT void Contorno_Module_Close(ContornoModule* module);
extern CONTORNO_EXPORT char* Contorno_Module_GetCurrentPath(void* func);

/* Character Set Conversions */
/* extern char* Contorno_Convert(char* input, ContornoSize input_length, char* input_codeset, char* output_codeset, ContornoSize* bytes_read, ContornoSize* bytes_written); */

/* Object System */
typedef void (*ContornoRefCountableFreeFunc)(void*);
typedef struct {
	ContornoRefCountableFreeFunc ref_free_func;
    unsigned int ref_count;
} ContornoRefCountable;

typedef void (*ContornoObjectFillFunc)(void*);
typedef struct {
	/* public */
	ContornoRefCountable;
    char *object_type;
    char **object_implements;
    ContornoObjectFillFunc* object_fillers;
    
    /* padding */
    void *object_pad_1;
    void *object_pad_2;
    void *object_pad_3;
} ContornoObject;

extern CONTORNO_EXPORT void Contorno_RefCountable_Ref(ContornoRefCountable* refcountable);
extern CONTORNO_EXPORT void Contorno_RefCountable_Unref(ContornoRefCountable* refcountable);
extern CONTORNO_EXPORT void Contorno_RefCountable_SetFreeFunc(ContornoRefCountable* refcountable, ContornoRefCountableFreeFunc func);
extern CONTORNO_EXPORT void Contorno_Object_Fill(ContornoObject* object, char* type, ContornoRefCountableFreeFunc* fillers, ContornoBool dont_fill);

/* File Utilities */
extern CONTORNO_EXPORT char* Contorno_FileUtility_Dirname(char* file);

#endif
