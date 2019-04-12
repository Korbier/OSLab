#ifndef _MYOS_MEM_
#define _MYOS_MEM_

#include "types.h"

void *memcpy(void *dest, const void *src, uint32_t count);
void *memset(void *dest, char val, uint32_t count);

#endif
