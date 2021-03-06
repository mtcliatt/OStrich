#include "system.h"

struct gdt_entry
{
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity;
	unsigned char base_high;
} __attribute__((packed));

struct gdt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct gdt_entry gdt[3];
struct gdt_ptr _gp;

extern void gdt_flush();

/* Sets up a descriptor in the Global Descriptor Table */
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
    /* Sets the descriptor base address */
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    /* Sets the descriptor limits */
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    /* Sets the granularity and access flags */
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

//this gets called in main
void gdt_install()
{
    /* Setup the GDT pointer and limit */
    _gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    _gp.base = (unsigned)&gdt;

    /* NULL descriptor */
    gdt_set_gate(0, 0, 0, 0, 0);

    /*  Code Segment. The base address is 0, the limit is 4GBytes,
	it uses 4KByte granularity, uses 32-bit opcodes, and is a Code Segment descriptor. */
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    /* Data Segment. same as our code segment, but the descriptor type in
    *  this entry's access byte says it's a Data Segment */
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    /* Flush out the old GDT and install the new changes! */
    _gdt_flush();
}

