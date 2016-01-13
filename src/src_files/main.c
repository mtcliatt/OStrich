#include "system.h"

unsigned char *memcpy(void *dest,void *src, int kount)
{
     unsigned char *temp = (unsigned char *)src;
     unsigned char *temp2 = (unsigned char *)dest;
     for(;kount!=0;kount--)
		*temp2++ = *temp++;
	return dest;
}

unsigned char *memset(unsigned char *dest, unsigned char val, int kount)
{
    for(;kount!=0;kount--)
		*dest++ = val;
	return dest;
}
unsigned short *memsetw(unsigned short *dest, unsigned short val, int kount)
{
    for(;kount!=0;kount--)
		*dest++ = val;
	return dest;
}
int strlen(char *str)
{
    char *temp = str;
    int i=0;
    while(*temp++ != '\0')
		i++;
	return i;
}
//inportb and outportb given by bran's tutorial
unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}
void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}
void main_call()
{
	//calls
	init_video(); //screen
	gdt_install();//gdt
	idt_install();//idt
	isr_install();//interrupt routines
	irq_install();//interrupt requests
	__asm__ __volatile__ ("sti");//lets IRQs happen
	keyboard_install();//keyboard
	/* for testing division by zero error
	*/
/*	int i = 5;
	putchar(i/0);
*/	
	for(;;);// need the infinite loop
//	return 0;
}
