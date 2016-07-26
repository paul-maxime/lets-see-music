#ifndef H_LSM_STRINGS
#define H_LSM_STRINGS

#include <iostream>

namespace Strings
{
	int					Length(char * str);
	int					IndexOf(char * str, char c);
	int					LastIndexOf(char * str, char c);
	char *				Copy(char * str);
	char *				Substring(char * str, int start, int length);
}

#endif
