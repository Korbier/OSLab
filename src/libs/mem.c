#include "mem.h"

//! copies count bytes from src to dest
void *memcpy(void *dest, const void *src, uint32_t count) {
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

//! sets count bytes of dest to val
void *memset(void *dest, char val, uint32_t count) {
  unsigned char *temp = (unsigned char *)dest;
	for( ; count != 0; count--, temp[count] = val);
	return dest;
}
