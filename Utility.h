#ifndef _Utility_
#define _Utility_

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Utility
{
	public:
		static int stringTOascii(string username);
		static string intTOstring(int integer);
		static int stringTOint(string str);
};

#endif