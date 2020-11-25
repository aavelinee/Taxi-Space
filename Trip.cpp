#include "Trip.h"
#include "User.h"
using namespace std;

Passenger* Trip :: get_passenger () {return passenger;}
bool Trip :: get_isaccepted() {return is_accepted;}
Driver* Trip :: get_driver(){return driver;}
string Trip :: get_source_address() {return source_address;}
vector <string> Trip :: get_destinations() {return destinations;}
bool Trip :: get_is_ended() {return is_ended;}
bool Trip :: get_has_rated() {return has_rated;}
int Trip :: get_rate() {return rate;}

void Trip :: set_is_ended(bool ended) {is_ended = ended;}
void Trip :: set_driver(Driver* drvr) {driver = drvr;}
void Trip :: set_isaccepted (bool isaccepted) {is_accepted = isaccepted;}
void Trip :: set_has_rate(bool rated) {has_rated = rated;}
void Trip :: set_rate(int rt) {rate = rt;}

Trip :: Trip (Passenger* pssngr, string srce_add, vector <string> dests, Time* time, bool isVIP)
{
	passenger = pssngr;
	source_address = srce_add;
	destinations = dests;
	is_accepted = false;
	is_ended = false;
	has_rated = false;
	dtime = time;
}