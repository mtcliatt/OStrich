#include "system.h"
#include "keyboard.h"

int caps = 0;
int called = 0;
void keyboard_handler(struct regs *r)//handles keys and caps lock ran out of time for making shift happy
{
	unsigned char scan;
	int shift = 0;
	unsigned char key;
	scan = inportb(0x60);
	switch(scan) {
        case 0x2a: 
            shift = 1; 
            break;
 
        case 0xaa: 
            shift = 0;
            break;
		
		default:
			if(scan & 0x80)
			{
				key = kbdus[scan];
				called = 0;
			}
			else
			{
				if(called == 0)
				{
					if(kbdus[scan]==30)
					{
						caps = ~caps;
					}
					else
					{
						key = kbdus[scan];
						
						if(caps && key >=97 && key < 123 )
						{
							if(!shift)
								key = key - 32;	
						}
						else if(key >=97 && key < 123)
						{
							if(shift)
								key = key - 32;
						}
						
						putchar( key );
					}
					called = 1;
				}		
			}
		}
}

void keyboard_install()
{
	irq_install_handler(1, keyboard_handler);
}
