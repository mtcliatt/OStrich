#include "../inc_files/malloc.h"
#include "../inc_files/kernel.h"

void * freeMem = (void *) 0x7f000001;
void * limit   = (void *) 0x7f000000;
int flag = 0;

void * malloc(int size)
{
	if(size <= 0)
		return NULL;

	if(freeMem + size > limit)
	{
		getMemory();
		return malloc(size);
	}

	void * ret = freeMem;
	freeMem += size;

	return ret;
}

void * calloc(size_t n, size_t size)
{
	int total = n * size;
	void * p = malloc(total);

	if(!p) return NULL;

	unsigned char * ptr = p;
	while(total--)
		*ptr++ = (unsigned char) 0;
	
	return p;
}

void getMemory()
{

	if(flag == 1)
	{
			//New implementation
		limit = giveMemory() + 4096;
	}
	else
	{
		freeMem = giveMemory();
		limit = freeMem + 4096;
		flag = 1;
	}
}
