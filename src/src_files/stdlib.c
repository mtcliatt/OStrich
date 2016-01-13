#include "../inc_files/stdlib.h"

void wait(long time)
{
	long volatile counter = time * 10000;	
	while( counter >= 0)
	{
		counter--;
	}
}

	/***************************************************************************************
	*										       *
	*			String functions					       *
	*										       *
	***************************************************************************************/

char * concat(char ** sources, int items)
{

	char * ret = sources[0];

	for(int i = 1; i < items; i++)
	{
		ret = strcat(ret, sources[i]);
	}

	return ret;

}

char * strcat(char * str1, char * str2)
{
	int l1 = strlen_2(str1);
	int l2 = strlen_2(str2);
	char * ret = malloc(l1+l2+1);

	for(int i = 0; i < l1+l2; i++)
	{
		if(i < l1)
			ret[i] = str1[i];
		else
			ret[i] = str2[i - l1];
	}

	ret[l1+l2] = '\0';

	return ret;
}


size_t strlen_2(const char* str)
{
	size_t ret = 0;
	while ( str[ret] != 0 )
		ret++;
	return ret;
}

int atoi(char * value)
{

	int ret = 0;
	int sign = 1;
	int i = 0;
	
	if(value[0] == '-')
	{
		sign = -1;
		i++;
	}
	else
	{
		if(value[0] == '\0')
			return 0;
	}

	while(value[i] != '\0')
	{
		if(value[i] >= '0' && value[i] <= '9')
		{
			ret = ret * 10 + value[i] - '0';
		}
		else
		{
			ret = ret * 10;
		}
		
		i++;
	}

	return sign*ret;
}

int itoa(int value, char *sp, int radix)
{
    char tmp[16];
    char *tp = tmp;
    int i;
    unsigned v;

    int sign = (radix == 10 && value < 0);    
    if (sign)
        v = -value;
    else
        v = (unsigned)value;

    while (v || tp == tmp)
    {
        i = v % radix;
        v /= radix; 
        if (i < 10)
          *tp++ = i+'0';
        else
          *tp++ = i + 'a' - 10;
    }

    int len = tp - tmp;

    if (sign) 
    {
        *sp++ = '-';
        len++;
    }

    while (tp > tmp)
        *sp++ = *--tp;

	*sp = '\0';
    return len;
}

int contains(char * string1, char * string2)
{

	int s1l = strlen_2(string1);
	int s2l = strlen_2(string2);

	if(s1l < s2l)
	{
		return 0;
	}

	for(int i = 0; i <= s1l - s2l; i++)
	{

		if(s1l - i < s2l)
			break;

		if(string1[i] == string2[0])
		{
		
			for(int j = 0; j < s2l; j++)
			{
			
				if(! string1[i + j] == string2[j])
					break;

				if(j == s2l -1)
					return 1;
			
			}

		}

	}

	return 0;
}


char * strdup(char * source)
{

	int len = strlen_2(source);
	char * dest = malloc(sizeof(char) * (len + 1));

	for(int i = 0; i < len; i++)
	{
		dest[i] = source[i];
	}

	dest[len] = '\0';

	return dest;
}

	/************************End of String Functions*******************************/
