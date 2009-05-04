#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <stdio.h>

#ifdef DEBUG
#define PRINT(fmt, ...) fprintf(stderr, "D [%s:%s]: "fmt"\n", __FILE__, __FUNCTION__, ##__VA_ARGS__)
#define WARNING(fmt, ...) fprintf(stderr, "W [%s:%s]: "fmt"\n", __FILE__, __FUNCTION__, ##__VA_ARGS__)
#define ERROR(fmt, ...) fprintf(stderr, "E [%s:%s]: "fmt"\n", __FILE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define PRINT(fmt, ...)
#define WARNING(fmt, ...)
#define ERROR(fmt, ...)
#endif

#endif
