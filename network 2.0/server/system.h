#ifndef _system_
#define _system_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Few_Arguments_Error {};
class Invalid_Username {};
class Invalid_SpaceShipModel {};
class Invalid_SpaceShipNumber {};
class Invalid_PhoneNumber {};
class Invalid_Command{};
class No_Discount_Code_Found{};
class Not_Enough_Count{};
class Not_Logged_In{};
class Uncorrect_Username{};
class Wrong_Username_Or_Password{};
class Illegal_Access{};
class Waiting_For_Acception{};
class Wrong_Address{};
class Not_Rated{};
class Not_Enough_Credit{};
class Invalid_Address{};
class No_Waiting_Driver{};

class Trip;
class Driver;
class Galaxy;

class Utility
{
	public:
		static int stringTOascii(string username);
		static string intTOstring(int integer);
		static int stringTOint(string str);
};

class Planet
{
	public:
		Planet(string nm);
		string get_name();
		vector <Planet*> get_neighbours();
		void construct_neighbour_planets(ifstream& topology, Galaxy* glxy);
		void set_is_seen (bool seen);
		bool get_is_seen();

	private:
		vector <Planet*> neighbour_planets;
		string name;
		bool is_seen;
};

class Galaxy
{
	public:
		Galaxy (string nm);
		void construct_planets(ifstream& topology);
		vector <Planet*> get_palnets ();
		string get_name();
		Planet* planet_finding(string planet_name);
		bool planet_exists(string planet_name);
		void calculate_distance(Planet* begin, Planet* end, int &distance);
		Planet* gate_finding();
		void unmark();

	private:
		string name;
		vector <Planet*> planets;
};

class World
{
	public :
		void read_topology();
		World () {}
		void construct_galaxies(ifstream &topology);
		vector <Galaxy*> get_galaxies();
		bool address_is_available (string galaxy, string planet);
		Galaxy* galaxy_finding(string username);
		int estimate_distance (string source_galaxy, string source_planet, string dest_galaxy, string dest_planet);

	private:
		vector <Galaxy*> galaxies;
};

class Time
{
	public:
		Time(string dtime);
		string get_time();
		void set_dtime(string dt);
	private:
		string date_time;
};

class SpaceShip
{
	public:
		SpaceShip (string number, string model, string year, string color);
		string get_model();
		string get_number();
		string get_year_production();
		string get_color();
	private:
		string spaceship_number;
		string spaceship_model;
		string spaceship_color;
		string production_date;
};

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
		long int get_passenger_credit();
		string get_passenger_username();
		bool get_can_request();
		bool get_is_on_trip();
		Passenger* get_passenger();
		bool get_isaccepted();
		Driver* get_driver();
		string get_source_address();
		vector <string> get_destinations();
		bool get_is_ended();
		bool get_has_rated();
		int get_rate();
		vector <Driver*> get_proper_drivers();

		void set_is_ended(bool ended);
		void set_driver(Driver* drvr);
		void set_isaccepted (bool isaccepted);
		void set_has_rate(bool rated);
		void set_rate(int rt);


		void charge_account(int credit);
		void subtract_account(int sub);
		void set_available_count(int count);
		void set_can_request(bool canRequest);
		
	private:
		string phone_number;
		long long discount_code;
		long int passenger_credit;
		int available_count;
		bool is_on_trip;
		bool can_request;
};


class Driver : public User
{
	public :
		Driver(string usrnm, string pass, SpaceShip *spcship);
		SpaceShip* get_spaceship_information();
		bool get_is_VIP();
		string get_status();
		string get_current_address ();
		int get_driver_rate();

		void set_VIP(bool v_i_p);
		void set_status(string sts);
		void set_current_address(string cur_add);
		void set_finished_trip(Trip* trp);
		void set_driver_rate(int rate);

	private:
		SpaceShip* spaceship;

		vector <Trip*> finished_trips;
		vector <Trip*> trip_requests;
		
		string status;
		string current_address;

		long int driver_credit;
		int driver_rate;

		bool VIP;
};

class Trip
{
	public:
		Trip (Passenger* pssngr, string srce_add, vector <string> destinations, Time* time, bool isVIP);
		Passenger* get_passenger ();
		bool get_isaccepted();
		Driver* get_driver();
		string get_source_address();
		vector <string> get_destinations();
		bool get_is_ended();
		bool get_has_rated();
		int get_rate();
		vector <Driver*> get_proper_drivers();

		void set_is_ended(bool ended);
		void set_driver(Driver* drvr);
		void set_isaccepted (bool isaccepted);
		void set_has_rate(bool rated);
		void set_rate(int rt);

	private:
		Driver* driver;
		Passenger* passenger;
		Time* dtime;
		vector <Driver*> proper_drivers;
		string source_address;
		vector <string> destinations;
		long int cost;
		int rate;
		bool is_accepted;
		bool is_vip;
		bool is_ended;
		bool has_rated;
};

class SyStem
{
	public:
		SyStem(Admin* adm, World* wrd);

		vector <Driver*> get_all_drivers();
		vector <Driver*> get_waiting_drivers();
		vector <Passenger*> get_passengers();
		vector <Trip*> get_trips();
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
		void set_status (vector <string> information);
		void charge_account (vector <string> information);
		void cancel_trip (vector <string> information);
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
		void findind_proper_drivers(vector <string> information);
		void findind_proper_drivers(string source_address, bool isvip);


		int get_credit (vector <string> information);
		long int passenger_report(vector <string> information);

		bool is_login(string username);
		bool if_cost_is_available(long int passenger_credit,long int cost);
		bool is_on_trip(string username);
		bool can_request(string username);


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
		World* world;
};

class Command
{
	public:
		Command(string commands);
		string run(SyStem* Sys);
		void set_key (string ky);
		void set_arguments (vector <string> arg);
		string get_key();
		vector <string> get_argument ();
	private:
		string key;
		vector <string> arguments;
};

#endif