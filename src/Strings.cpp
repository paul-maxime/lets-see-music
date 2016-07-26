#include "Strings.hpp"

namespace Strings
{
	int Length(char * str)
	{
		int l = 0;
		while (str[l] != '\0')
			l++;
		return l;
	}
	
	int IndexOf(char * str, char c)
	{
		int l = Length(str);
		int p = 0;
		while (p < l && str[p] != c)
			p++;
		return (p == l ? -1 : p);
	}
	
	int LastIndexOf(char * str, char c)
	{
		int l = Length(str);
		int p = l;
		while (p >= 0 && str[p] != c)
			p--;
		return p;
	}
	
	char * Copy(char * str)
	{
		int l = Length(str);
		char * str2 = new char[l+1];
		for (int i = 0; i <= l; i++)
			str2[i] = str[i];
		return str2;
	}
	
	char * Substring(char * str, int start, int length)
	{
		char * str2 = new char[length+1];
		for (int i = 0; i < length; i++)
			str2[i] = str[i+start];
		str2[length] = '\0';
		return str2;
	}
}
