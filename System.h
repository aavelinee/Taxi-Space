#ifndef _System_
#define _System_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "User.h"
#include "Time.h"
#include "Exception.h"
#include "Universe.h"

using namespace std;

class SyStem
{
	public:
		SyStem(Admin* adm);

		vector <Driver*> get_all_drivers ();
		vector <Driver*> get_waiting_drivers ();
		vector <Passenger*> get_passengers ();
		vector <Trip*> get_trips ();
		Admin* get_admin();
		Time* get_dtime();
		Passenger* finding_the_passenger (string username);

		vector <string> separating_address(string address);
		vector <vector <string> > show_registration_requests (vector <string> information);
		vector <vector <string> > show_trip_requests (vector <string> information);
		vector <int> get_discount_code (vector <string> information);
		vector <string> trip_status(vector <string> information);
		vector <string> request_trip (vector <string> information);
		vector <string> estimate_trip (vector <string> information);
		vector <string> system_report(vector <string> information);

		void log_in (vector <string> information);
		void log_out (vector <string> information);
		void set_status (vector <string> information, World& wrd);
		void charge_account (vector <string> information);
		void cancle_trip (vector <string> information);
		void accept_trip_request (vector <string> information);
		void arrived(vector <string> information);
		void end_trip(vector <string> information);
		void rate_driver(vector <string> information);
		void set_time(vector <string> information);
		void passenger_registration (vector <string> information);
		void driver_registration (vector <string> information);
		void accept_registration (vector <string> information);
		void reject_registration (vector <string> information);
		void read_models (vector <string> &spaceShipModels);
		void driver_report(vector <string> information);


		int get_credit (vector <string> information);
		long int passenger_report(vector <string> information);

		bool is_login(string username);
		bool if_cost_is_available(long int passenger_credit,long int cost);




	private:
		Admin* admin;
		Time* datetime;
		long int system_credit;
		vector <Driver*> drivers;
		vector <Driver*> waiting_drivers;
		vector <Passenger*> passengers;
		vector <Trip*> trips;
		vector <string> spaceShipModels;
		vector <string> spaceShipNumbers;
};
#endif