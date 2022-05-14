#ifndef __DEBUG_H__
#define __DEBUG_H__

// printf redefinitions for easy debuggings
#if defined(PRINTF_DEBUG)
#define PRINT(x) printf (x);
#define PRINT1(x,a) printf(x,a);
#define PRINT2(x,a,b) printf(x,a,b);
#else
#define PRINT(x)
#define PRINT1(x,a)
#define PRINT2(x,a,b)
#endif

#endif
