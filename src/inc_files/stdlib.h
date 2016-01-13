#ifndef STDLIB_H
#define STDLIB_H

#include <stddef.h>
#include <stdint.h>

#include "io.h"
#include "kernel.h"
#include "malloc.h"

void		wait		(long);

char * 		strcat			   (char *, char *);
char *		concat			   (char **, int);
size_t 		strlen_2             	   (const char*);
int 		itoa			   (int, char *, int);
void		scroll			   ();
int		contains		   (char *, char *);
char *		strdup			   (char *);



#endif
