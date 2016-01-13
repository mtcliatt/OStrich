#ifndef IO_H
#define IO_H

#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif

#include <stddef.h>
#include <stdint.h>
#include "malloc.h"
#include "stdlib.h"

enum 		vga_color;
uint8_t 	make_color        	   (enum vga_color, enum vga_color);
uint16_t 	make_vgaentry    	   (char, uint8_t);

void	 	terminal_initialize        ();
void 		terminal_setcolor          (uint8_t);
uint8_t		terminal_getcolor	   ();
void 		terminal_putentryat        (char, uint8_t, size_t, size_t);
void 		terminal_putchar      	   (char );

int 		terminal_writestring       (void *, void *, void *, void *, void *, void *);
void		printColor		   (char *, unsigned int, unsigned int);
int 		monitor_clear              (void *, void *, void *, void *, void *, void *);
void 		start_screen		   ();
void 		printDivider		   (char *);


#endif
