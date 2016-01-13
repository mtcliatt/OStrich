#ifndef KERNEL_H
#define KERNEL_H

#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>
#include "io.h"
#include "stdlib.h"
#include "malloc.h"

#define SYSCALL_SIZE	6

#define SYSCALL_SYS_SETUP	0
#define SYSCALL_EXIT		1
#define SYSCALL_FORK		2
#define SYSCALL_READ		3
#define SYSCALL_WRITE		4
#define SYSCALL_CLEAR		5

int syscall(int, void *, void *, void *, void *, void *, void *);
int undefined_syscall(void *, void *, void *, void *, void *, void *);
 
void * giveMemory	();
void   testStuff	();
void   syscallTest	();
void   mallocTest	();
void   stdlibTest	();
void   asciiTest	();

/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

#endif
