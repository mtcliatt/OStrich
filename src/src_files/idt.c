#include "system.h"

struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;        
    unsigned char always0;     
    unsigned char flags;       
    unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr _idtp;

extern void _idt_load();//start.asm 

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
    /* similar but easier then GDT*/
	idt[num].always0 = 0;
	idt[num].flags = flags;
	idt[num].sel = sel;
	idt[num].base_lo = (base & 0xFFFF);
	idt[num].base_hi = ((base >> 16) & 0xFFFF);
}

/* starts the IDT */
void idt_install()
{
    /* Sets the special IDT pointer up, just like in 'gdt.c' */
    _idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    _idtp.base = (unsigned)&idt;

    /* Clear out the entire IDT, initializing it to zeros */
    memset((unsigned char *)&idt, 0, sizeof(struct idt_entry) * 256);

    /* Add any new ISRs to the IDT here using idt_set_gate */

    /* Points the processor's internal register to the new IDT */
    _idt_load();
}
	
