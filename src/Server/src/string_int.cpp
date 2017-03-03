#include "string_int.h"

string convert_to_string(long long num)
{
	
	long long input = num;

	string s="\0";
	char c;

	while(num!=0)
	{
       c = (char)(num%10 + (int)'0');
       s = c + s;
       num = num/10;
	}

	
	if(s.length()==18)
	{	
		return s;
	}

	else
	{
		s = string( 18-s.length(), '0').append(s);
	}

	return s;
}

long long convert_to_int(string s)
{
	long long out = 0 ;

	for(int i=0;i<s.length();i++)
	{
		out = out*10 + s[i] - '0';
	}

	return out;
}


string word_to_string(char A[],int n)
{

	string out="\0";

	for(int i=0;i<n;i++)
	{
		out = out + A[i];
	}

	return out;
}

bool is_string_zero(string input)
{
	for(int i=0;i<input.length();i++)
	{
		if(input[i]!='0')
			return false;
	}

	return true;
}