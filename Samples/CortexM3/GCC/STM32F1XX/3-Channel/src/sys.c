// This file is to avoid linkage of exception handling and other BIG stuff like
// malloc and RTTI when using pure virtual functions.
// Thanks to Terminator for this great idea.
// (http://electronix.ru/forum/index.php?showtopic=42167&view=findpost&p=643815)
#ifdef __cplusplus
extern "C" {
#endif


void * __dso_handle = 0;

__extension__ typedef int __guard __attribute__((mode (__DI__)));

int __cxa_guard_acquire(__guard *);
void __cxa_guard_release (__guard *);
void __cxa_guard_abort (__guard *);

int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);}
void __cxa_guard_release (__guard *g) {*(char *)g = 1;}
void __cxa_guard_abort (__guard *g) {(void)g;}

void __cxa_pure_virtual(void);
void __cxa_pure_virtual(void) {}
#ifdef __cplusplus
}
#endif
