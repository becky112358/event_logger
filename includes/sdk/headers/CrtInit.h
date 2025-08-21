#ifndef cppx_h
#define cppx_h

#ifdef __cplusplus
extern "C"
{
#endif

BOOLEAN cppInit( void );
BOOLEAN cppInitLate(void);
void cppShutdown( void );
void cppFreeLazyObjects(void);
int  cppGetNumberHandlerOverflow();

int TcCrtGetMaxNumberAtexitHandler();
int TcCrtGetFreeNumberAtexitHandler();

#ifdef __cplusplus
} // extern "C"
#endif

#endif cppx_h

