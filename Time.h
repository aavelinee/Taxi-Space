#ifndef _Time_
#define _Time_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Time
{
	public:
		Time (string dtime);
		string get_time ();
		void set_dtime (string dt);
	private:
		string date_time;
};

#endif