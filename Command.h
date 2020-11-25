#ifndef _Command_
#define _Command_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "System.h"

using namespace std;

class Command
{
	public:
		Command(string commands);
		void run(SyStem& Sys, World& wrd);
		void set_key (string ky);
		void set_arguments (vector <string> arg);
		string get_key();
		vector <string> get_argument ();
		
	private:
		string key;
		vector <string> arguments;
};

#endif