#ifndef _Trip_
#define _Trip_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Time.h"

using namespace std;

class Passenger;
class Driver;

class Trip
{
	public:
		Trip (Passenger* pssngr, string srce_add, vector <string> destinations, Time* time, bool isVIP);
		Passenger* get_passenger ();
		bool get_isaccepted ();
		Driver* get_driver ();
		string get_source_address ();
		vector <string> get_destinations ();
		bool get_is_ended ();
		bool get_has_rated ();
		int get_rate ();

		void set_is_ended (bool ended);
		void set_driver (Driver* drvr);
		void set_isaccepted (bool isaccepted);
		void set_has_rate (bool rated);
		void set_rate (int rt);


	private:
		Driver* driver;
		Passenger* passenger;
		Time* dtime;
		string source_address;
		vector <string> destinations;
		long int cost;
		int rate;
		bool is_accepted;
		bool is_vip;
		bool is_ended;
		bool has_rated;
};

#endif	