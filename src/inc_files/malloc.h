#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h>
#include <stdint.h>
#include "kernel.h"

void * malloc(int);
void * calloc(size_t, size_t);
void getMemory();

#endif
