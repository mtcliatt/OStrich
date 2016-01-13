

// main
extern unsigned char *memcpy(void *dest, void *src, int kount);
extern unsigned char *memset(unsigned char *dest, unsigned char val, int kount);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, int kount);
extern int strlen(char *str);
extern unsigned char inportb (unsigned short _port);
extern void outportb (unsigned short _port, unsigned char _data);
extern void main_call();
// screen
extern void cls();
extern void putchar(char c);
extern void puts(char *str);
extern void settextcolor(unsigned char forecolor, unsigned char backcolor);
extern void init_video();
//gdt
extern void gdt_install();
//idt
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
extern void idt_install();
//isr
struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};

extern void isr_install();
//irq
extern void irq_install();
extern void irq_handler(struct regs *r);
extern void irq_install_handler(int irq, void (*handler)(struct regs *r));
void irq_uninstall_handler(int irq);

//keyboard
extern void keyboard_install();
