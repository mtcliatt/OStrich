#include "system.h"

unsigned short *textmemptr;
int attribute = 0x0F;
int csr_x = 0;
int csr_y = 0;

//scroll
void screen_scroll(void)
{
	unsigned blank, temp;
	
	blank = 0x20 | (attribute << 8);

	if(csr_y >= 25)// at end need to scroll up
	{
		temp = csr_y - 25 + 1;
		memcpy(textmemptr, textmemptr + temp * 80, (25 - temp) * 80 * 2);
		memsetw(textmemptr + (25 - temp) * 80, blank, 80);
		csr_y = 25 -1;
	}
}
void move_csr(void)
{
	unsigned temp;

	/* The equation for finding the index in a linear
	      chunk of memory can be represented by:
	      Index = [(y * width) + x] */
	temp = csr_y * 80 + csr_x;

    	/* This sends a command to indicies 14 and 15 in the
	    *  CRT Control Register of the VGA controller. These
	    *  are the high and low bytes of the index that show
	    *  where the hardware cursor is to be 'blinking'.*/
	outportb(0x3D4, 14);
	outportb(0x3D5, temp >> 8);
	outportb(0x3D4, 15);
	outportb(0x3D5, temp);
}
/* Clears the screen */
void cls()
{
    unsigned blank;
    int i;

    /* Again, we need the 'short' that will be used to
      represent a space with color */
    blank = 0x20 | (attribute << 8);

    /* Sets the entire screen to spaces in our current
      color */
    for(i = 0; i < 25; i++)
        memsetw (textmemptr + i * 80, blank, 80);

    /* Update out virtual cursor, and then move the
      hardware cursor */
    csr_x = 0;
    csr_y = 0;
    move_csr();
}
void putchar(char c)
{
    unsigned short *where;
    unsigned att = attribute << 8;

    /* backspace moves cursor back 1 */
    if(c == 0x08)
    {
        if(csr_x != 0) csr_x--;
    }
    /* tab increments the cursor, but only
    *  to a point that will make it divisible by 8 */
    else if(c == 0x09)
    {
        csr_x = (csr_x + 8) & ~(8 - 1);
    }
    /* Carriage Return */
    else if(c == '\r')
    {
        csr_x = 0;
    }
    /* newlines, bring the cursor to the margin and we increment the 'y' value */
    else if(c == '\n')
    {
        csr_x = 0;
        csr_y++;
    }
    /* Any character greater than and including a space, is a
    *  printable character. The equation for finding the index
    *  in a linear chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    else if(c >= ' ')
    {
        where = textmemptr + (csr_y * 80 + csr_x);
        *where = c | att;	/* Character AND attributes: color */
        csr_x++;
    }

    /* If the cursor has reached the edge of the screen's width then
    *  insert a new line */
    if(csr_x >= 80)
    {
        csr_x = 0;
        csr_y++;
    }

    /* Scroll the screen if needed, and finally move the cursor */
    screen_scroll();
    move_csr();
}
void puts(char *text)
{
    int i;

    for (i = 0; i < strlen(text); i++)
    {
        putchar(text[i]);
    }
}
void settextcolor(unsigned char forecolor, unsigned char backcolor)
{
    /* Top 4 bytes are the background, bottom 4 bytes
    *  are the foreground color */
    attribute = (backcolor << 4) | (forecolor & 0x0F);
}
/* Sets our text-mode VGA pointer, then clears the screen for us */
void init_video(void)
{
    textmemptr = (unsigned short *)0xB8000;
    cls();
}
