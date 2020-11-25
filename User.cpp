#include "User.h"
#include "System.h"

using namespace std;

User :: User(string usrnm, string pass, bool lgin)
{
	username = usrnm;
	password = pass;
	login =lgin;
}

Admin :: Admin (string usrnm, string pass) : User (usrnm, pass, false) {}

string Passenger :: get_phone_number() {return phone_number;}
long long Passenger :: get_discount_code() {return discount_code;}
int Passenger :: get_available_count() {return available_count;}
long int Passenger :: get_passenger_credit () {return passenger_credit;}
string Passenger :: get_passenger_username() {return username;}

void Passenger :: charge_account(int credit) {passenger_credit += credit;}
void Passenger :: subtract_account(int sub) {passenger_credit -= sub;}
void Passenger :: set_available_count(int count) {available_count -= count;}

Passenger :: Passenger (string usrnm, string pass, string phnum) : User(usrnm, pass, false)
{
	phone_number = phnum;
	discount_code = Utility :: stringTOascii(usrnm);
	passenger_credit = 0;
	available_count = 5;
	is_on_trip = false;
}

SpaceShip* Driver :: get_spaceship_information() {return spaceship;}
bool Driver :: get_is_VIP() {return VIP;}
string Driver :: get_status() {return status;}
string Driver :: get_current_address () {return current_address;}

void Driver :: set_VIP(bool v_i_p) {VIP = v_i_p;}
void Driver :: set_status(string sts) {status = sts;}
void Driver :: set_current_address(string cur_add) {current_address = cur_add;}
void Driver :: set_finished_trip(Trip* trp) {finished_trips.push_back(trp);}

Driver :: Driver (string usrnm, string pass, SpaceShip *spcship) : User (usrnm, pass, false)
{
	spaceship = spcship;
	status = "unavailable";
	VIP = false;
}
