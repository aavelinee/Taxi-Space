#include "Utility.h"

using namespace std;

int Utility :: stringTOascii(string username)
{
	long int temp=0;
	for(int i=0; i<username.size(); i++)
		temp += int(username[i]);
	return temp;
}

string Utility :: intTOstring(int integer)
{
	string Result;
	stringstream convert;
	convert << integer;
	Result = convert.str();
	return Result;
}

int Utility :: stringTOint(string str)
{
	int temp = 0;
	for(int i=0; i<str.size(); i++)
	{
		temp += str[i] - '0';
		temp *= 10;
	}
	temp /=10;
	return temp;
}