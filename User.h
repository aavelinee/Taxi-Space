#ifndef _User_
#define _User_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Spaceship.h"
#include "Utility.h"
#include "Trip.h"

using namespace std;

class Trip;

class User
{
	public:
		User(string usrnm, string pass, bool lgin);

		bool get_is_login();
		string get_username();
		string get_password();
		void set_is_login(bool lg);
	protected:
		string username;
		string password;
		bool login;
};

class Admin : public User
{
	public:
		Admin(string usrnm, string pass);
};


class Passenger : public User
{
	public: 
		Passenger(string usrnm, string pass, string phnum);
		string get_phone_number();
		long long get_discount_code();
		int get_available_count();
		long int get_passenger_credit ();
		string get_passenger_username();

		void charge_account(int credit);
		void subtract_account(int sub);
		void set_available_count(int count);
	private:
		string phone_number;
		long long discount_code;
		long int passenger_credit;
		int available_count;
		bool is_on_trip;
};

class Driver : public User
{
	public :
		Driver(string usrnm, string pass, SpaceShip *spcship);
		SpaceShip* get_spaceship_information();
		bool get_is_VIP();
		string get_status();
		string get_current_address();

		void set_VIP(bool v_i_p);
		void set_status(string sts);
		void set_current_address(string cur_add);
		void set_finished_trip(Trip* trp);

	private:
		SpaceShip* spaceship;

		vector <Trip*> finished_trips;
		vector <Trip*> trip_requests;
		
		string status;
		string current_address;

		long int driver_credit;

		bool VIP;
};

#endif