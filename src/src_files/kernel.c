#include "../inc_files/kernel.h"
#include "../inc_files/system.h"

void * memLocation = (void *) 0x30D40;
void * memLimit = (void *) 0x7f000000;


int (*calls[SYSCALL_SIZE]) (void *, void *, void *, void *, void *, void *) = 
	{
		undefined_syscall,
		undefined_syscall,
		undefined_syscall,
		undefined_syscall,
		terminal_writestring,
		monitor_clear
	};


void testStuff()
{
/*		
	printDivider("Syscall testing");
	syscallTest();
	printDivider("End Syscall testing");
	wait(150000);
	

	
	printDivider("Malloc testing");
	mallocTest();
	printDivider("End Malloc testing");
	wait(150000);
	printDivider("stdlib testing");
	stdlibTest();
	printDivider("End stdlib testing");
	wait(150000);
	
	printDivider("Ascii and Color testing");
	asciiTest();
	printDivider("End ascii and Color testing");
	wait(100000);

*/

/*	syscall(SYSCALL_WRITE, "divide by 0!\n", NULL, NULL, NULL, NULL, NULL);
	int x = 5 / 0;
*/
}

void syscallTest()
{

	syscall(SYSCALL_WRITE, "OStrich>>> SYSCALL_WRITE working!\n", NULL, NULL, NULL, NULL, NULL);
	wait(100000);

	syscall(SYSCALL_WRITE, "OStrich>>> Calling a bad system call:", NULL, NULL, NULL, NULL, NULL);
	syscall(2, NULL, NULL, NULL, NULL, NULL, NULL);
	wait(100000);

	syscall(SYSCALL_WRITE, "Calling syscall_clear shortly...\n", NULL, NULL, NULL, NULL, NULL);
	wait(100000);
	syscall(SYSCALL_CLEAR, NULL, NULL, NULL, NULL, NULL, NULL);

	syscall(SYSCALL_WRITE, "Clear worked!\n", NULL, NULL, NULL, NULL, NULL);

}

void mallocTest()
{

	char * string1 = malloc(sizeof(char) * 8);
	char * string2 = malloc(sizeof(char) * 7);

	string1[0] = 'M';
	string1[1] = 'a';
	string1[2] = 't';
	string1[3] = 't';
	string1[4] = 'h';
	string1[5] = 'e';
	string1[6] = 'w';
	string1[7] = '\0';

	string2[0] = 'C';
	string2[1] = 'l';
	string2[2] = 'i';
	string2[3] = 'a';
	string2[4] = 't';
	string2[5] = 't';
	string2[6] = '\0';

	char s1loc[18];
	int s1int = (int) string1;
	itoa(s1int, s1loc, 16);
	s1loc[17] = '\0';

	char s2loc[18];
	int s2int = (int) string2;
	itoa(s2int, s2loc, 16);
	s2loc[17] = '\0';

	syscall(SYSCALL_WRITE, "Made string1 with value \"Matthew\"\n", NULL, NULL, NULL, NULL, NULL);
	
	syscall(SYSCALL_WRITE, "Value of string1: '", NULL, NULL, NULL, NULL, NULL);
	syscall(SYSCALL_WRITE, string1, NULL, NULL, NULL, NULL, NULL);
	syscall(SYSCALL_WRITE, "'\tAddress of string1: '", NULL, NULL, NULL, NULL, NULL);
	syscall(SYSCALL_WRITE, s1loc, NULL, NULL, NULL, NULL, NULL);
	syscall(SYSCALL_WRITE, "'\n\n", NULL, NULL, NULL, NULL, NULL);
	
	syscall(SYSCALL_WRITE, "Made string2 with value \"Cliatt\"\n", NULL, NULL, NULL, NULL, NULL);

	syscall(SYSCALL_WRITE, "Value of string2: '", NULL, NULL, NULL, NULL, NULL);
	syscall(SYSCALL_WRITE, string2, NULL, NULL, NULL, NULL, NULL);
	syscall(SYSCALL_WRITE, "'\tAddress of string2: '", NULL, NULL, NULL, NULL, NULL);
	syscall(SYSCALL_WRITE, s2loc, NULL, NULL, NULL, NULL, NULL);
	syscall(SYSCALL_WRITE, "'\n\n", NULL, NULL, NULL, NULL, NULL);

	syscall(SYSCALL_WRITE, "Made string3 from strcat(string1, \" \")\n", NULL, NULL, NULL, NULL, NULL);
	char * string3 = strcat(string1, " ");

	char s3loc[18];
	int s3int = (int) string3;
	itoa(s3int, s3loc, 16);
	s3loc[17] = '\0';
	
	syscall(SYSCALL_WRITE, "Value of string3: '", NULL, NULL, NULL, NULL, NULL);
	syscall(SYSCALL_WRITE, string3, NULL, NULL, NULL, NULL, NULL);
	syscall(SYSCALL_WRITE, "'\tAddress of string3: '", NULL, NULL, NULL, NULL, NULL);
	syscall(SYSCALL_WRITE, s3loc, NULL, NULL, NULL, NULL, NULL);
	syscall(SYSCALL_WRITE, "'\n\n", NULL, NULL, NULL, NULL, NULL);
	

	syscall(SYSCALL_WRITE, "Made string4 from strcat(string3, string2)\n", NULL, NULL, NULL, NULL, NULL);
	char * string4 = strcat(string3, string2);

	char s4loc[18];
	int s4int = (int) string4;
	itoa(s4int, s4loc, 16);
	s4loc[17] = '\0';
	
	syscall(SYSCALL_WRITE, "Value of string4: '", NULL, NULL, NULL, NULL, NULL);
	syscall(SYSCALL_WRITE, string4, NULL, NULL, NULL, NULL, NULL);
	syscall(SYSCALL_WRITE, "'\tAddress of string4: '", NULL, NULL, NULL, NULL, NULL);
	syscall(SYSCALL_WRITE, s4loc, NULL, NULL, NULL, NULL, NULL);
	syscall(SYSCALL_WRITE, "'\n\n", NULL, NULL, NULL, NULL, NULL);

	syscall(SYSCALL_WRITE, "Made string5 from strcat(string4, \" is teh c00lest!\")\n", NULL, NULL, NULL, NULL, NULL);
	char * string5 = strcat(string4, " is teh c00lest!");

	char s5loc[18];
	int s5int = (int) string5;
	itoa(s5int, s5loc, 16);
	s5loc[17] = '\0';
	
	syscall(SYSCALL_WRITE, "Value of string5: '", NULL, NULL, NULL, NULL, NULL);
	syscall(SYSCALL_WRITE, string5, NULL, NULL, NULL, NULL, NULL);
	syscall(SYSCALL_WRITE, "'\nAddress of string5: '", NULL, NULL, NULL, NULL, NULL);
	syscall(SYSCALL_WRITE, s5loc, NULL, NULL, NULL, NULL, NULL);
	syscall(SYSCALL_WRITE, "'\n", NULL, NULL, NULL, NULL, NULL);

	syscall(SYSCALL_WRITE, "\nTesting malloc with variables of size >= 4096.\n", NULL, NULL, NULL, NULL, NULL);

	char * t1 = malloc(sizeof(char) * 4096);
	int t1l = (int) t1;
	char t1ls[18];
	itoa(t1l, t1ls, 16);
	t1ls[17] = '\0';
	syscall(SYSCALL_WRITE, strcat("Address of testString: ", t1ls), NULL, NULL, NULL, NULL, NULL);


	char * t2 = malloc(sizeof(char) * 4100);
	int t2l = (int) t2;
	char t2ls[18];
	itoa(t2l, t2ls, 16);
	t2ls[17] = '\0';
	syscall(SYSCALL_WRITE, strcat("\nAddress of testString2 ", t2ls), NULL, NULL, NULL, NULL, NULL);

	syscall(SYSCALL_WRITE, "\n", NULL, NULL, NULL, NULL, NULL);

}

void stdlibTest()
{

	char * torf = "true";

	if(!contains("Matthew", "Matt"))
		torf = "false";

	syscall(SYSCALL_WRITE, strcat("\nMatthew contains Matt == ", torf), NULL, NULL, NULL, NULL, NULL);

	torf = "true";

	if(!contains("Matthew", "tthe"))
		torf = "false";

	syscall(SYSCALL_WRITE, strcat("\nMatthew contains tthe == ", torf), NULL, NULL, NULL, NULL, NULL);

	torf = "true";

	if(!contains("Matthew", "Cliatt"))
		torf = "false";

	syscall(SYSCALL_WRITE, strcat("\nMatthew contains Cliatt == ", torf), NULL, NULL, NULL, NULL, NULL);

	char * test1 = "YOLO";
	char * test2 = strdup(test1);

	syscall(SYSCALL_WRITE, strcat("\nYOLO will be here if strdup works: ", strcat(test2, "\n")), NULL, NULL, NULL, NULL, NULL);

}

void asciiTest()
{

	for(int i = 0; i < 16; i++)
	{
		char * a = malloc(sizeof(int) * 18);
		itoa(i, a, 10);
		if(i > 9)
			printColor(strcat(strcat("BG = ", a), "  "), i+1, i);
		else
			printColor(strcat(strcat("BG = ", a), "   "), i+1, i);
		for(int j = 0; j < 16; j++)
		{
			char * b = malloc(sizeof(int) * 18);
			itoa(j, b, 10);
			printColor(strcat(strcat("T", b), "  "), j, i);
		}
		syscall(SYSCALL_WRITE, "\n", NULL, NULL, NULL, NULL, NULL);
	}
	syscall(SYSCALL_WRITE, "\n", NULL, NULL, NULL, NULL, NULL);

	wait(150000);
	wait(150000);
	wait(150000);
	
	syscall(SYSCALL_WRITE, "\n\n", NULL, NULL, NULL, NULL, NULL);

	for(int i = 0; i < 25; i++)
	{
		for(int j = 0; j < 11; j++)
		{
			if(j*25 + i >= 255)	break;
			char * c = malloc(sizeof(int) * 18);
			c[itoa(j*25 + i, c, 16)] = '\0';

			char ascii = (char)(j*25 + i);
			if(ascii == '\t' || ascii == '\n')
				ascii = 'N';
			char as[] = {ascii, '\0'};


			char * str = strcat(c, "-");
			str = strcat(str, as);
			str = strcat(str, " | ");

			syscall(SYSCALL_WRITE, str, NULL, NULL, NULL, NULL, NULL);
		}
		if(i < 24) syscall(SYSCALL_WRITE, "\n", NULL, NULL, NULL, NULL, NULL);
	}

	wait(150000);
	syscall(SYSCALL_WRITE, "\n", NULL, NULL, NULL, NULL, NULL); 
}

void kernel_main()
{
	terminal_initialize();

	start_screen(20);

	testStuff();
	
	//runs other main to init everything else, sloppy but short on time
	main_call();
}

int syscall(int syscall, void * arg1, void * arg2, void * arg3, void * arg4, void * arg5, void * arg6)
{

	return (*calls[syscall]) (arg1, arg2, arg3, arg4, arg5, arg6);

}

int undefined_syscall(void * arg1, void * arg2, void * arg3, void * arg4, void * arg5, void * arg6)
{
	arg1 = arg1;
	(*calls[SYSCALL_WRITE]) ("\nUndefined system call\n", arg2, arg3, arg4, arg5, arg6 );
	return -2;
}

void * giveMemory()
{

	if(memLocation + 4096 > memLimit)
		return NULL;
	
	void * retMem = memLocation;
	memLocation += 4096;
	return retMem;
}
