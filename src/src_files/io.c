#include "../inc_files/io.h"


	/**************************************************************************************
	*				Initializing 					      *
	***************************************************************************************/


static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
enum vga_color
{
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
};

void terminal_initialize()
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for ( size_t y = 0; y < VGA_HEIGHT; y++ )
	{
		for ( size_t x = 0; x < VGA_WIDTH; x++ )
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
}

	/*******************End Initializing**********************************************/
 




	/********************************************************************************************
	*											    *
	*			Terminal functions						    *
	*											    *
	*********************************************************************************************/

	/*
	 *
	 *	How printing to terminal works:
	 *		Calls to terminal_writestring pass a char*, writestring then
	 *		gets strlen of char*, iterates through and passes each char to 
	 *		putchar(char). Putchar interprets char and decides where the char
	 *		needs to be placed with terminal_row and terminal_column. After
	 *		finding right place for char, putchar passes char to putentryat(),
	 *		which places value in terminal_buffer. Value is uint16_t which 8
	 *		bits of color then 8 bits of char value.
	 *		The screen automatically reads from address where terminal_buffer
	 *		is located.
	 *
	 */

uint8_t make_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}
 
void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

uint8_t terminal_getcolor()
{
	return terminal_color;
}

uint16_t make_vgaentry(char c, uint8_t color)
{
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}

void terminal_putchar(char c)
{
	
	if(c == '\n') {
		for(unsigned int i = terminal_column; i < VGA_WIDTH; i++)
		{
			terminal_putentryat(' ', terminal_color, i, terminal_row);
		}
		terminal_column = 0;
		if(++terminal_row >= VGA_HEIGHT)
		{
			terminal_row = VGA_HEIGHT - 1;
			scroll();
		}
		return;
	}

	if(c == '\t')
	{
		for(int i = 0; i < 4; i++)
		{
			terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
			if(++terminal_column >= VGA_WIDTH)
			{
				terminal_column = 0;
				if(++terminal_row >= VGA_HEIGHT)
				{
					terminal_row = VGA_HEIGHT - 1;
					scroll();
				}
			}
		}
		return;
	}
		
			
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if ( ++terminal_column >= VGA_WIDTH )
	{
		terminal_column = 0;
		if ( ++terminal_row >= VGA_HEIGHT )
		{
			terminal_row = VGA_HEIGHT - 1;
			scroll();
		}
	}
}

void printColor(char * text, unsigned int tcolor, unsigned int bg)
{

	uint8_t orig = terminal_color;
	terminal_setcolor(make_color(tcolor, bg));
	terminal_writestring(text, NULL, NULL, NULL, NULL, NULL);
	terminal_setcolor(orig);

}

void printDivider(char * str)
{

	char * ret = malloc(sizeof(char) * 83);
	ret[0] = '\n';

	for(unsigned int i = 1; i < 81; i++)
		ret[i] = '=';
	ret[81] = '\n';
	ret[82] = '\0';

	unsigned int strlength = strlen_2(str);
	int start = 40 - strlength/2;

	for(unsigned int i = 0; i < strlength; i++)
		ret[start + i] = str[i];

	uint8_t orig = terminal_color;
	uint8_t gonb = make_color(COLOR_RED, COLOR_BLACK);
	terminal_setcolor(gonb);
	terminal_writestring(ret, NULL, NULL, NULL, NULL, NULL);
	terminal_setcolor(orig);

}


void start_screen(int len)
{
	uint8_t gonb = make_color(COLOR_GREEN, COLOR_BLACK);
	uint8_t bong = make_color(COLOR_BLACK, COLOR_GREEN);
	terminal_setcolor(bong);
	
	terminal_writestring("\n\n\n\t\t\t\t\t\t  ", NULL, NULL, NULL, NULL, NULL);

	terminal_setcolor(gonb);
	terminal_writestring("OStrich --- Version 0.0.1", NULL, NULL, NULL, NULL, NULL);
	terminal_setcolor(bong);

	terminal_writestring("\n\n", NULL, NULL, NULL, NULL, NULL);

	int spinrow = terminal_row;
	char * chars = "|/-\\";
	for(int i = 0; i < 80; i++)
	{
		terminal_putentryat(' ', terminal_color, i, spinrow);
	}


	terminal_setcolor(gonb);
	terminal_writestring("\n\n\n", NULL, NULL, NULL, NULL, NULL);

	char * art1 = "            _.-~~-.\n";
	char * art2 = "          .'       '-.\n";
	char * art3 = "         /_/    -.    `>\n";
	char * art4 = "             OStrich   \n";
	char * art5 = "        {__}\\  -.~`   /\n";
	char * art6 = "         ||  '-.  /.-'\n";
	char * art7 = "         ||    |||\n";
	char * art8 = "'`\"`\"\"`\"\"||\"`\"`|||\"\"`\"\"`\"\"'`'`\"`\"\"``\"\"`\"\"'`'`\"`\"\"`'`'\"`\"''`'\"`\"'`'\"\"`\"\"`\"\"'`'`\"\n";
	char * art9 = "         ||  __|||_\n";
	char * art10 ="        _||_  /||\\\n";
	char * art11 ="       `\"\"\"\"`\n";

	char * arts[11] = {art1, art2, art3, art4, art5, art6, art7, art8, art9, art10, art11};
	char * tArts = concat(arts, 11);
	terminal_writestring(tArts, NULL, NULL, NULL, NULL, NULL);

	int waittime = len;
	int ch = 0;
	while(waittime > 0)
	{
		for(int i = 0; i <= 80; i += 20)
		{
			if(i == 80)
				i = 79;
			terminal_putentryat(chars[(ch + i / 20) % 4], terminal_color, i, spinrow);
		}
		ch++;
		wait(5000);	
		waittime--;
	}

	terminal_setcolor(make_color(COLOR_WHITE, COLOR_BLACK));
	monitor_clear(NULL, NULL, NULL, NULL, NULL, NULL);

}
 
	/***********************END OF TERMINAL FUNCTIONS*******************************************/





	/********************************************************************************************
	*											    *
	*			SYSTEM CALLS							    *
	*											    *
	*********************************************************************************************/

int terminal_writestring(void * param1, void * param2, void * param3, void * param4, void * param5, void * param6)
{
	param2 = param3 = param4 = param5 = param6 = NULL;
	param3 = param2;
	const char * data = (const char *) param1;

	size_t datalen = strlen_2(data);
	for ( size_t i = 0; i < datalen; i++ )
		terminal_putchar(data[i]);

	return 0;
}

int monitor_clear(void * param1, void * param2, void * param3, void * param4, void * param5, void * param6)
{
	param1 = param2 = param3 = param4 = param5 = param6 = NULL;
	param2 = param1;

	for(unsigned int i = 0; i < VGA_HEIGHT; i++)
	{
		terminal_writestring("\n", NULL, NULL, NULL, NULL, NULL);
	}

	terminal_row = 0;
	terminal_column = 0;

	return 0;	
}

void scroll()
{

	for (size_t y = 0; y < VGA_HEIGHT * (VGA_WIDTH - 1); y++)
	{
		terminal_buffer[y] = terminal_buffer[y + VGA_WIDTH];
	}

	wait(3000);

}

	/*****************************END OF SYSTEM CALLS******************************************/
