#ifndef _UTIL_H
#define _UTIL_H

#include <stdlib.h>
#include <stdio.h>

#define ALLOC(_type) check_null_malloc(malloc(sizeof(_type)))

static inline __attribute__((always_inline)) void *check_null_malloc(void *ptr) {
    if (!ptr) {
	puts("malloc failed");
	exit(1);
    }
    return ptr;
}

#endif

