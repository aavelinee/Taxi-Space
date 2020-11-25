#include "system.h"

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

Planet :: Planet (string nm) {name = nm; is_seen = false;}
string Planet :: get_name() {return name;}
vector <Planet*> Planet ::  get_neighbours() {return neighbour_planets;}
void Planet :: set_is_seen (bool seen) {is_seen = seen;}
bool Planet :: get_is_seen() {return is_seen;}

Galaxy :: Galaxy (string nm) {name = nm;}
vector <Planet*> Galaxy :: get_palnets () {return planets;}
string Galaxy :: get_name() {return name;}

void Galaxy :: unmark()
{
	for(int j=0; j<planets.size(); j++)
		planets[j]->set_is_seen(false);
}

void Galaxy :: calculate_distance(Planet* begin, Planet* end, int &distance)
{
	begin->set_is_seen(true);
	if(begin->get_name() == end->get_name())
		return;
	for(int i=0 ; i<begin->get_neighbours().size(); i++)
	{
		if(begin->get_neighbours()[i]->get_is_seen() == false)
		{
			distance++;
			return calculate_distance (begin->get_neighbours()[i], end, distance);
		}
	}
	distance--;
}

vector <Galaxy*> World :: get_galaxies() {return galaxies;}

void World :: read_topology()
{
	ifstream ifs;
	string temp;
	int galaxy_number;
	ifs.open ("topology.cfg");

	ifs >> temp;

	galaxy_number = Utility :: stringTOint(temp);
	for(int i=0; i<galaxy_number; i++)
		construct_galaxies(ifs);
	ifs.close();
}

void World :: construct_galaxies(ifstream &topology)
{
	string galaxy_name, plnt_num;
	int planet_number;

	topology >> galaxy_name;
	topology >> plnt_num;
	planet_number = Utility :: stringTOint(plnt_num);
	Galaxy* glxy = new Galaxy(galaxy_name);
	galaxies.push_back(glxy);
	for(int i=0; i<planet_number; i++)
		glxy->construct_planets(topology);

	return;
}

bool World :: address_is_available (string galaxy, string planet)
{
	for(int i=0; i<galaxies.size(); i++)
	{
		if(galaxy == galaxies[i]->get_name())
			for(int j=0; j<galaxies[i]->get_palnets().size(); j++)
				if(planet == galaxies[i]->get_palnets()[j]->get_name())
					return true;
	}
	return false;
}

Galaxy* World :: galaxy_finding(string username)
{
	for(int i=0; i<galaxies.size(); i++)
		if(username == galaxies[i]->get_name())
			return galaxies[i];
}

int World :: estimate_distance (string source_galaxy, string source_planet, string dest_galaxy, string dest_planet)
{
	int distance = 0;
	if(source_galaxy == dest_galaxy)
	{
		galaxy_finding(source_galaxy)->calculate_distance(galaxy_finding(source_galaxy)->planet_finding(source_planet)
			,galaxy_finding(dest_galaxy)->planet_finding(dest_planet),distance);
		galaxy_finding(dest_galaxy)->unmark();
		return distance;
	}
	else
	{
		galaxy_finding(source_galaxy)->calculate_distance(galaxy_finding(source_galaxy)->planet_finding(source_planet)
			,galaxy_finding(source_galaxy)->gate_finding(),distance);
		galaxy_finding(dest_galaxy)->calculate_distance(galaxy_finding(dest_galaxy)->gate_finding()
			,galaxy_finding(dest_galaxy)->planet_finding(dest_planet),distance);
		galaxy_finding(source_galaxy)->unmark();
		galaxy_finding(dest_galaxy)->unmark();
		return distance;
	}
}

bool Galaxy :: planet_exists(string planet_name)
{
	for(int i=0; i<planets.size(); i++)
	{
		if(planet_name == planets[i]->get_name())
			return true;
		else
			for(int j=0; j<planets[i]->get_neighbours().size(); j++)
				if(planet_name == planets[i]->get_neighbours()[j]->get_name())
					return true;
	}
	return false;
}

Planet* Galaxy :: planet_finding(string planet_name)
{
	for(int i=0; i<planets.size(); i++)
		if(planet_name == planets[i]->get_name())
			return planets[i];

	for(int i=0; i<planets.size(); i++)
		for(int k=0; k<planets[i]->get_neighbours().size(); k++)
			if(planet_name == planets[i]->get_neighbours()[k]->get_name())
				return planets[i]->get_neighbours()[k];
}

void Galaxy :: construct_planets(ifstream& topology)
{
	string name_of_planet;
	int neighbour_number;

	topology >> name_of_planet;
	topology >> neighbour_number;

	if(planet_exists(name_of_planet) == true)
		planets.push_back(planet_finding(name_of_planet));
	else
	{
		Planet* p = new Planet(name_of_planet);
		planets.push_back(p);
	}
	
	for(int i=0; i<neighbour_number; i++)
		planets.back()->construct_neighbour_planets (topology, this);
}

Planet* Galaxy :: gate_finding()
{

	return planets[0];
}

void Planet :: construct_neighbour_planets(ifstream& topology, Galaxy* glxy)
{
	string neighbour_name;
	topology >> neighbour_name;

	if(glxy->planet_exists(neighbour_name))
		neighbour_planets.push_back(glxy-> planet_finding(neighbour_name));
	else
	{
		Planet* plnt = new Planet(neighbour_name);
		neighbour_planets.push_back(plnt);
	}
}

Time :: Time (string dtime){date_time = dtime;}
string Time :: get_time() {return date_time;}
void Time :: set_dtime(string dt) {date_time = dt;}
	
string SpaceShip :: get_model() {return spaceship_model;}
string SpaceShip :: get_number() {return spaceship_number;}
string SpaceShip :: get_year_production() {return production_date;}
string SpaceShip :: get_color() {return spaceship_color;}

SpaceShip :: SpaceShip (string number, string model, string year, string color)
{
	spaceship_number = number;
	spaceship_model = model;
	production_date = year;
	spaceship_color = color;
}

bool User :: get_is_login() {return login;}
string User :: get_username() {return username;}
string User :: get_password() {return password;}
void User :: set_is_login(bool lg) {login = lg;}

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
bool Passenger :: get_can_request() {return can_request;}
bool Passenger :: get_is_on_trip() {return is_on_trip;}

void Passenger :: charge_account(int credit) {passenger_credit += credit;}
void Passenger :: subtract_account(int sub) {passenger_credit -= sub;}
void Passenger :: set_available_count(int count) {available_count -= count;}
void Passenger :: set_can_request(bool canRequest) {can_request = canRequest;}

Passenger :: Passenger (string usrnm, string pass, string phnum) : User(usrnm, pass, false)
{
	phone_number = phnum;
	discount_code = Utility :: stringTOascii(usrnm);
	passenger_credit = 0;
	available_count = 5;
	is_on_trip = false;
	can_request = true;
}

SpaceShip* Driver :: get_spaceship_information()
{
	return spaceship;
}

bool Driver :: get_is_VIP() {return VIP;}
string Driver :: get_status() {return status;}
string Driver :: get_current_address () {return current_address;}
int Driver :: get_driver_rate() {return driver_rate;}

void Driver :: set_VIP(bool v_i_p) {VIP = v_i_p;}
void Driver :: set_status(string sts) {status = sts;}
void Driver :: set_current_address(string cur_add) {current_address = cur_add;}
void Driver :: set_finished_trip(Trip* trp) {finished_trips.push_back(trp);}
void Driver :: set_driver_rate(int rate) {driver_rate = rate;}


Driver :: Driver (string usrnm, string pass, SpaceShip *spcship) : User (usrnm, pass, false)
{
	spaceship = spcship;
	status = "unavailable";
	VIP = false;
}

Passenger* Trip :: get_passenger()
{
	return passenger;
}

bool Trip :: get_isaccepted() {return is_accepted;}
Driver* Trip :: get_driver(){return driver;}
string Trip :: get_source_address() {return source_address;}
vector <string> Trip :: get_destinations() {return destinations;}
bool Trip :: get_is_ended() {return is_ended;}
bool Trip :: get_has_rated() {return has_rated;}
int Trip :: get_rate() {return rate;}
vector <Driver*> Trip :: get_proper_drivers() {return proper_drivers;}

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

vector <Driver*> SyStem :: get_all_drivers () {return drivers;}
vector <Driver*> SyStem :: get_waiting_drivers () {return waiting_drivers;}
vector <Passenger*> SyStem :: get_passengers () {return passengers;}
vector <Trip*> SyStem :: get_trips () {return trips;}
Admin* SyStem :: get_admin() {return admin;}
Time* SyStem :: get_dtime() {return datetime;}

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


SyStem :: SyStem (Admin* adm, World* wrd)
{
	admin = adm;
	world = wrd;
	Time* t = new Time("1-00:00:00");
	datetime = t;
	this->read_models(spaceShipModels);
}

Passenger* SyStem :: finding_the_passenger (string username)
{
	for(int i=0; i<passengers.size(); i++)
		if(username == passengers[i]->get_username())
			return passengers[i];
	throw Uncorrect_Username();
}

bool SyStem :: is_login(string username)
{
	if(username == "admin" && admin->get_is_login() == true)
		return true;
	else
	{
		for(int i=0; i<passengers.size(); i++)
			if(username == passengers[i]->get_username())
				if(passengers[i]->get_is_login())
					return true;
		for(int i=0; i<drivers.size(); i++)
			if(username == drivers[i]->get_username())
				if(drivers[i]->get_is_login())
					return true;
		for(int i=0; i<waiting_drivers.size(); i++)
			if(username == waiting_drivers[i]->get_username())
				throw Waiting_For_Acception();
	}
	return false;
}

void SyStem :: read_models(vector <string> &spaceShipModels)
{
	ifstream readfile;
	string models;
	readfile.open ("vehicles.cfg");
	while(!readfile.eof())
	{
		readfile >> models;
		spaceShipModels.push_back(models);
	}
	readfile.close();
}

int SyStem :: get_credit(vector <string> information)
{
	int _credit;
	Passenger* p = finding_the_passenger(information[0]);
	if(p->get_is_login())
		{
			_credit = p->get_passenger_credit();
			return _credit;
		}
		else
			throw Not_Logged_In();
	throw Uncorrect_Username();
}

void SyStem :: charge_account(vector <string> information)
{
	Passenger* p =finding_the_passenger(information[0]);
	if(p->get_is_login())
	{
		p->charge_account(Utility :: stringTOint(information[1]));
		return;
	}
	else
		throw Not_Logged_In();
	throw Uncorrect_Username();
}

vector <int> SyStem :: get_discount_code (vector <string> information)
{

	vector <int> temp;
	Passenger* p =finding_the_passenger(information[0]);
	if(p->get_is_login())
	{
		temp.push_back(p->get_discount_code());
		temp.push_back(p->get_available_count());
		return temp;
	}
	else
		throw Not_Logged_In();
	throw Uncorrect_Username();
}

vector <string> SyStem :: separating_address(string address)
{
	vector <string> separated_address;

	for(int i=0; i<address.size(); i++)
	{
		if(address.at(i) == ',')
		{
			separated_address.push_back(address.substr(0,i));
			address = address.substr(i+1);
		}
	}
	return separated_address;
}

void SyStem :: set_status (vector <string> information)
{
	vector <string> address;
	bool galaxy_existance;
	bool planet_existance;
	// vector <Galaxy*> galaxies = wrd.get_galaxies();
	// vector <Planet*> planets = wrd.get_galaxies();
	// for(int i=0; i<wrd.get_galaxies.size(); i++

	for(int i=0; i<drivers.size(); i++)
	{
		if(information[0] == drivers[i]->get_username())
		{
			if(drivers[i]->get_is_login())
			{
				if(information[1] == "available" && drivers[i]->get_status() == "unavailable")
				{
					drivers[i]->set_status("available");
	//========================================================================================
					//check if the address is available
	//========================================================================================
					// address = separating_address(information[2]);
					// for(int i=0; i<galaxies.size(); i++)
					// 	if(address[0] == galaxies[i])
					// 		galaxy_existance = true;
					// for(int i=0; i<planets.size(); i++)
					// 	if(address[1] == planets[i])
					// 		planet_existance = true;
					// if(galaxy_existance == true && planet_existance == true)
						drivers[i]->set_current_address(information[2]);
					// else
					// 	throw Wrong_Address();
				}
				else if(information[1] == "unavailable" && drivers[i]->get_status() == "available")
					drivers[i]->set_status("unavailable");
				else if(information[1] == "on_trip" && drivers[i]->get_status() == "available")
					drivers[i]->set_status("on_trip");
				else if(information[1] == "available" && drivers[i]->get_status() == "on_trip")
					drivers[i]->set_status("available");
				else
					throw Invalid_Command();
			}
			else
				throw Not_Logged_In();
			return;
		}
	}
	throw Uncorrect_Username();
}

void SyStem :: log_in(vector <string> information)
{
	if(information[0] == "admin" && information[1] == "s3cret")
	{
		admin->set_is_login(true);
		return;
	}

	else
	{
		for(int i=0; i<passengers.size(); i++)
			if(information[0] == passengers[i]->get_username() 
				&& information[1] == passengers[i]->get_password())
			{
				passengers[i]->set_is_login(true);
				return;
			}

		for(int i=0; i<drivers.size(); i++)
			if(information[0] == drivers[i]->get_username()
				&& information[1] == drivers[i]->get_password())
			{
				drivers[i]->set_is_login(true);
				return;
			}

		for(int i=0; i<waiting_drivers.size(); i++)
			if(information[0] == waiting_drivers[i]->get_username())
				throw Waiting_For_Acception();

		throw Wrong_Username_Or_Password();
	}
}

void SyStem :: log_out(vector <string> information)
{
	if(is_login(information[0]))
	{
		if(information[0] == "admin")
			admin->set_is_login(false);

		else
		{
			for(int i=0; i<passengers.size(); i++)
				if(information[0] == passengers[i]->get_username())
					passengers[i]->set_is_login(false);

			for(int i=0; i<drivers.size(); i++)
				if(information[0] == drivers[i]->get_username())
					drivers[i]->set_is_login(false);
		}
	}
	else
		throw Not_Logged_In();
}

void SyStem :: accept_registration (vector <string> information)
{
	if(information[0] != "admin")
			throw Illegal_Access();

	else
	{
		if(is_login(information[0]))
			for(int i=0; i<waiting_drivers.size(); i++)
				if(information[1] == waiting_drivers[i]->get_username())
				{
					drivers.push_back(waiting_drivers[i]);
					waiting_drivers.erase(waiting_drivers.begin() + i);
				}

		else
			throw Not_Logged_In();
	}
}

void SyStem :: reject_registration (vector <string> information)
{
	if(information[0] != "admin")
		throw Illegal_Access();

	else
	{
		if(is_login(information[0]))
			for(int i=0; i<waiting_drivers.size(); i++)
				if(information[1] == waiting_drivers[i]->get_username())
					waiting_drivers.erase(waiting_drivers.begin() + i);
		else
			throw Not_Logged_In();
	}
}

vector <vector <string> > SyStem :: show_registration_requests (vector <string> information)
{
	vector <vector <string> > temp(waiting_drivers.size());
	if(information[0] != "admin")
			throw Illegal_Access();

	else
	{
		if(is_login(information[0]))
		{
			if(waiting_drivers.size() == 0)
				throw No_Waiting_Driver();
			for(int i=0; i<waiting_drivers.size(); i++)
			{
					temp[i].push_back(waiting_drivers[i]->get_username());
					temp[i].push_back(waiting_drivers[i]->get_spaceship_information()->get_number());
					temp[i].push_back(waiting_drivers[i]->get_spaceship_information()->get_model());
					temp[i].push_back(waiting_drivers[i]->get_spaceship_information()->get_year_production());
					temp[i].push_back(waiting_drivers[i]->get_spaceship_information()->get_color());
					if(waiting_drivers[i]->get_is_VIP())
						temp[i].push_back("VIP");
			}
			return temp;
		}
		else
			throw Not_Logged_In();
	}	
}

void SyStem :: passenger_registration (vector <string> information)
{
	string username = information[0];
	string phone_number = information[2];
	cerr << "username : " << username << endl;
	for(int i=0; i<passengers.size(); i++)
		if(username == passengers[i]->get_username())
			throw Invalid_Username();

	for(int i=0; i<passengers.size(); i++)
		if(phone_number == passengers[i]->get_phone_number())
			throw Invalid_PhoneNumber();

	for(int i=0; i<drivers.size(); i++)
		if(username == drivers[i]->get_username())
			throw Invalid_Username();

	for (int i=0; i<waiting_drivers.size(); i++)
		if(username == waiting_drivers[i]->get_username())
			throw Invalid_Username();

	Passenger* p =  new Passenger(username, information[1], phone_number);

	if(information.size() == 4)
	{
		long long dis_code = Utility :: stringTOascii(information[3]);

		for(int i=0; i<passengers.size(); i++)
			if(dis_code == passengers[i]->get_discount_code())
			{
				p->charge_account(10);
				if(passengers[i]->get_available_count() > 0)
					passengers[i]->set_available_count(1);
				else
					throw Not_Enough_Count();
			}
			else
				throw No_Discount_Code_Found();
	}

	passengers.push_back(p);
}

void SyStem :: driver_registration (vector <string> information)
{
	bool is_valid = false;
	string username = information[0];
	string carNumber = information[2];
	string model = information[3];

	for(int i=0; i<drivers.size(); i++)
		if(username == drivers[i]->get_username())
			throw Invalid_Username();

	for(int i=0; i<waiting_drivers.size(); i++)
		if(username == waiting_drivers[i]->get_username())
			throw Invalid_Username();

	for(int i=0; i<passengers.size(); i++)
		if(username == passengers[i]->get_username())
			throw Invalid_Username();

	for(int i=0; i<spaceShipNumbers.size(); i++)
		if(carNumber == spaceShipNumbers[i])
			throw Invalid_SpaceShipNumber();

	for(int i=0; i<spaceShipModels.size(); i++)
		if(model == spaceShipModels[i])
			is_valid = true;

	if(is_valid)
	{
		SpaceShip* SP = new SpaceShip(information[2], information[3], information[4], information[5]);
		Driver* d = new Driver(username, information[1], SP);
		spaceShipNumbers.push_back(SP->get_number());
		if(information.size()==7)
			d->set_VIP(true);
		waiting_drivers.push_back(d);
	}
	else
		throw Invalid_SpaceShipModel();	
}

bool SyStem :: if_cost_is_available(long int passenger_credit,long int cost)
{
	if(passenger_credit - cost < 10)
		return false;
	return true;
}

bool SyStem :: can_request(string username)
{
	for(int i=0; i<passengers.size(); i++)
		if(username == passengers[i]->get_username())
			if(passengers[i]->get_can_request())
				return true;
	return false;
}

bool SyStem :: is_on_trip(string username)
{
	for(int i=0; i<passengers.size(); i++)
		if(passengers[i]->get_is_on_trip())
			return true;
	return false;
}

void SyStem :: findind_proper_drivers(string source_address, bool isvip)
{
	int distance = 0;
	int min = 1000;
	vector <Driver*> proper_driver = get_all_drivers();
	vector <Driver*> driver_temp;
	string proper_driver_username;
	int n;
	if(drivers.size() >= 4)
		n = 4;
	else
		n = drivers.size();

	for(int k=0; k<n; k++)
	{
		for(int i=0; i<proper_driver.size(); i++)
		{
			if(isvip)
			{
				if(proper_driver[i]->get_status() == "available")
				{
					if(proper_driver[i]->get_is_VIP())
					{
						int find_comma1 = proper_driver[i]->get_current_address().find(',');
						string driver_galaxy = proper_driver[i]->get_current_address().substr(0,find_comma1);
						string driver_planet = proper_driver[i]->get_current_address().substr(find_comma1 + 1);
						
						int find_comma2 = source_address.find(',');
						string passenger_galaxy = source_address.substr(0,find_comma2);
						string passenger_planet = source_address.substr(find_comma2 + 1);

						distance += world->estimate_distance(driver_galaxy, driver_planet, passenger_galaxy, passenger_planet);
						if(distance < min)
						{
							min = distance;
							driver_temp.push_back(proper_driver[i]);
							proper_driver.erase(proper_driver.begin() + i);
						}
					}
				}
			}
			else
			{
				if(proper_driver[i]->get_is_VIP() == false)
				{
					if(proper_driver[i]->get_is_VIP() == false)
					{
						int find_comma1 = proper_driver[i]->get_current_address().find(',');
						string driver_galaxy = proper_driver[i]->get_current_address().substr(0,find_comma1);
						string driver_planet = proper_driver[i]->get_current_address().substr(find_comma1 + 1);

						int find_comma2 = source_address.find(',');
						string passenger_galaxy = source_address.substr(0,find_comma2);
						string passenger_planet = source_address.substr(find_comma2 + 1);

						distance += world->estimate_distance(driver_galaxy, driver_planet, passenger_galaxy, passenger_planet);
						
						if(distance < min)
						{
							min = distance;
							driver_temp.push_back(proper_driver[i]);

							proper_driver.erase(proper_driver.begin() + i);
						}
					}
				}
			}
		}
	}
	cerr << "driver temp :" << driver_temp.size() << endl;
}

vector <string> SyStem :: request_trip(vector <string> information)
{
	long int pass_credit;
	vector <string> cost_distance;
	vector <string> destinations;
	string source_address;
	bool isvip;
	
	for(int i=0; i<trips.size(); i++)
		if(information[0] == trips[i]->get_passenger()->get_username())
			pass_credit = trips[i]->get_passenger()->get_passenger_credit();

	if(information[1] == "VIP")
	{
		isvip = true;
		source_address = information[2];
		for(int i=3; i<information.size(); i++)
			destinations.push_back(information[i]);
	}
	else
	{
		isvip = false;
		source_address = information[1];
		for(int i=2; i<information.size(); i++)
			destinations.push_back(information[i]);
	}

	if(is_login(information[0]))
	{
		if(can_request(information[0]))
		{
			if(is_on_trip(information[0]) == false)
			{
				cost_distance = estimate_trip(information);
				findind_proper_drivers(source_address, isvip);
				for(int i=0; i<passengers.size(); i++)
					if(information[0] == passengers[i]->get_username())
					{
						Trip* tr = new Trip(passengers[i],source_address, destinations, datetime ,isvip);
						trips.push_back(tr);
						passengers[i]->set_can_request(false);
						return cost_distance;
					}
			}
			else
				throw Invalid_Command();
		}
		else
			throw Not_Rated();
	}
	else
		throw Not_Logged_In();
}

vector <string> SyStem :: estimate_trip(vector <string> information)
{
	int distance = 0;
	bool is_vip;
	vector <string> dests;
	vector <string> infos;
	if(information[1] == "VIP")
	{
		is_vip = true;
		for(int i=2; i<information.size(); i++)
			dests.push_back(information[i]);
	}
	else
	{
		is_vip=false;
		for(int i=1; i<information.size(); i++)
			dests.push_back(information[i]);
	}
	if(is_login(information[0]))
	{
		vector <string> infos;
		bool flag = false;
		for(int i=0; i<passengers.size(); i++)
		{
			if(information[0] == passengers[i]->get_username())
			{
				flag = true;
				for(int j=0 ; j<dests.size()-1; j++)
				{
					int find_comma1 = dests[j].find(',');
					string source_galaxy = dests[j].substr(0,find_comma1);
					string source_planet = dests[j].substr(find_comma1+1);

					int find_comma2 = dests[j].find(',');
					string dest_galaxy = dests[j+1].substr(0,find_comma2);
					string dest_planet = dests[j+1].substr(find_comma2+1);

					if(world->address_is_available(source_galaxy, source_planet) == false)
						throw Invalid_Address();
					if(world->address_is_available(dest_galaxy, dest_planet) == false)
						throw Invalid_Address();

					distance += world->estimate_distance(source_galaxy, source_planet, dest_galaxy, dest_planet);
				}
			}
		}
		if(flag == false)
			throw Uncorrect_Username();
	}
	else
		throw Not_Logged_In();
	if(is_vip == true)
		infos.push_back(Utility :: intTOstring(distance * 2));
	else
		infos.push_back(Utility :: intTOstring(distance));
	infos.push_back(Utility :: intTOstring(distance));
	return infos;
}

void SyStem :: cancel_trip(vector <string> information)
{
	if(is_login(information[0]))
	{
		for(int i=0; i<trips.size(); i++)
			if(information[0] == trips[i]->get_passenger()->get_username())
			{
				if(trips[i]->get_isaccepted() == true)
					throw Invalid_Command();
				else
				{
					trips.erase(trips.begin() + i);
					trips[i]->get_passenger()->set_can_request(true);
				}
			}
	}
	else
		throw Not_Logged_In();
}

//=========================================================================
/*vector <vector <string> > SyStem ::  show_trip_requests(vector <string> information)
{
	vector <vector <string> > temp(trips.size());
	for(int i=0; i<drivers.size(); i++)
	{
		if(information[0] == drivers[i]->get_username())
		{

		}

	}
}*/
//=========================================================================

void SyStem :: accept_trip_request (vector <string> information)
{
	if(is_login(information[0]))
	{
		for(int i=0; i<trips.size(); i++)
		{
			if(information[1] == trips[i]->get_passenger()->get_username())
			{
				trips[i]->set_isaccepted(true);
				for(int i=0; i<drivers.size(); i++)
				{
					if(information[0] == drivers[i]->get_username())
					{
						trips[i]->set_driver(drivers[i]);
						drivers[i]->set_status("on_trip");
						drivers[i]->set_finished_trip(trips[i]);
					}
				}
			}
		}
	}
	else
		throw Not_Logged_In();
}

void SyStem :: arrived(vector <string> information)
{
	if(is_login(information[0]))
	{
		for(int i=0; i<trips.size(); i++)
		{
			if(trips[i]->get_driver()->get_username() == information[0])
			{
				trips[i]->get_driver()->set_current_address(trips[i]->get_source_address());
					return;
			}
		}

		for(int i=0; i<waiting_drivers.size(); i++)
		{
			if(information[0] == waiting_drivers[i]->get_username())
				throw Waiting_For_Acception();
		}
	}
	else
		throw Not_Logged_In();
}

void SyStem :: end_trip(vector <string> information)
{
	if(is_login(information[0]))
	{
		for(int i=0; i<trips.size(); i++)
		{
			if(information[0] == trips[i]->get_driver()->get_username())
			{
				trips[i]->get_driver()->set_current_address(trips[i]->get_destinations().back());
				trips[i]->get_driver()->set_status("available");
				trips[i]->set_is_ended(true);
				//trips[i]->get_passenger()->subtract_account(cost);
				// system_credit += cost;
			}
		}
	}
	else
		throw Not_Logged_In();
}

void SyStem :: rate_driver(vector <string> information)
{
	int rate = Utility :: stringTOint(information[1]);
	for(int i=0; i<trips.size(); i++)
	{
		if(information[0] == trips[i]->get_passenger()->get_username())
			if(trips[i]->get_is_ended())
			{
				trips[i]->set_rate(rate);
				trips[i]->get_passenger()->set_can_request(true);
				trips[i]->get_driver()->set_driver_rate(rate);
				return;
			}
			else
				throw Invalid_Command();
	}
	throw Uncorrect_Username();
}

vector <string> SyStem :: trip_status(vector <string> information)
{
	vector <string> infos;
	if(is_login(information[0]))
	{
		for(int i=0; i<trips.size(); i++)
			if(information[0] == trips[i]->get_passenger()->get_username())
			{
				if(trips[i]->get_is_ended())
					continue;
				else
				{
					if(trips[i]->get_isaccepted() == true)
					{
						infos.push_back("accepted");
						infos.push_back(trips[i]->get_driver()->get_username());
						infos.push_back(trips[i]->get_driver()->get_current_address());
						infos.push_back(trips[i]->get_driver()->get_spaceship_information()->get_model());
						infos.push_back(trips[i]->get_driver()->get_spaceship_information()->get_color());
						return infos;
					}
					else
						infos.push_back("waiting");
				}
			}
	}
	else
		throw Not_Logged_In();
}

void SyStem :: set_time(vector <string> information)
{
	if(is_login(information[0]))
	{
		if(information[0] == "admin")
			datetime->set_dtime(information[1]);
		else
			throw Illegal_Access();
	}
	else
		throw Not_Logged_In();
}

void SyStem :: driver_report(vector <string> information)
{

}

long int SyStem :: passenger_report(vector <string> information)
{
	long int credit;
	if(is_login(information[0]))
	{
		if(information[0] == "admin")
		{
			for(int i=0; i<passengers.size(); i++)
				if(information[1] == passengers[i]->get_username())
				{
					credit = passengers[i]->get_passenger_credit();
					return credit;
				}
		}
		else
			throw Illegal_Access();
	}			
	else
		throw Not_Logged_In();
}

vector <string> SyStem :: system_report(vector <string> information)
{
	if(information.size()==1)
	{
		vector <string> infos;
		if(is_login(information[0]))
		{
			if(information[0] == "admin")
			{
				infos.push_back(Utility :: intTOstring(system_credit));
				infos.push_back(Utility :: intTOstring(trips.size()));
				infos.push_back(Utility :: intTOstring(drivers.size()));
				infos.push_back(Utility :: intTOstring(passengers.size()));
				return infos;
			}
			else
				throw Illegal_Access();
		}
		else
			throw Not_Logged_In();

	}
	else
	{

	}
}


void Command :: set_key (string ky) {key = ky;}
void Command :: set_arguments (vector <string> arg) {arguments = arg;}
string Command :: get_key() {return key;}
vector <string> Command :: get_argument () {return arguments;}
	

Command :: Command (string commands)
{
	string temp;
	stringstream info (commands);
	while (info >> temp)
		arguments.push_back(temp);

	key = arguments[1];
	arguments.erase(arguments.begin() + 1);
}

string Command:: run(SyStem* Sys)
{
	string result = "";
	try
	{
		if(key == "register_passenger")
		{
			// check_arguments(arguments);
			Sys->passenger_registration(arguments);
			return result;

		}

		else if(key == "register_driver")
		{

			Sys->driver_registration(arguments);
			return result;

		}

		else if(key == "accept_registration")
		{

			Sys->accept_registration(arguments);
			return result;
		}

		else if(key == "reject_registration")
		{

			Sys->reject_registration(arguments);
			return result;
		}

		else if(key == "show_registration_requests")
		{
			cerr << "here" << endl;
			vector <vector <string> > requests;
			requests = Sys->show_registration_requests(arguments);
			for(int i=0; i<requests.size(); i++)
			{
				for(int j=0; j<requests[i].size(); j++)
					result += requests[i][j] + " ";
				result += "\n";
			}
			cerr << "oooo" << endl;
			return result;
		}

		else if(key == "get_discount_code")
		{
			vector <int> information;
			information = Sys->get_discount_code(arguments);
			for(int i=0; i<information.size(); i++)
				result += information[i];
			return result;
		}

		else if(key == "login")
		{
			cerr << "sss" << endl;
			Sys->log_in(arguments);
			return result;

		}

		else if(key == "logout")
		{

			Sys->log_out(arguments);
			return result;

		}

		else if(key == "set_status")
		{

			Sys->set_status(arguments);
			return result;

		}

		else if(key == "charge_account")
		{

			Sys->charge_account(arguments);
			return result;

		}

		else if(key == "get_credit")
		{
			int _credit;
			_credit = Sys->get_credit(arguments);
			result = Utility :: intTOstring(_credit);
			return result;

		}

		else if(key == "request_trip")
		{
			vector <string> temp;
			temp = Sys->request_trip(arguments);
			for(int i=0; i<temp.size(); i++)
				result += temp[i];
			return result;

		}

		else if(key == "estimate_trip")
		{
			vector <string> temp;
			temp = Sys->estimate_trip(arguments);
			for(int i=0; i<temp.size(); i++)
				result += temp[i];
			return result;

		}

		else if(key == "cancel_trip_request")
		{

			Sys->cancel_trip(arguments);
			return result;

		}

		/*else if(key == "show_trip_requests")
		{
			vector <vector <string> > requests;
			requests = Sys->show_trip_requests(arguments);
			for(int i=0; i<requests.size(); i++)
			{
				for(int j=0; j<requests[i].size(); j++)
					cout << requests[i][j] << " ";
				cout << endl;
			}
		}*/

		else if(key == "accept_trip_request")
		{
			Sys->accept_trip_request(arguments);
			return result;

		}

		else if(key == "arrived")
		{

			Sys->arrived(arguments);
			return result;

		}

		else if(key == "trip_status")
		{
			vector <string> information;
			information = Sys->trip_status(arguments);
			for(int i=0; i<information.size(); i++)
				result += information[i];
			return result;
		}

		else if(key == "end_trip")
		{

			Sys->end_trip(arguments);
			return result;

		}

		else if(key == "rate_driver")
		{

			Sys->rate_driver(arguments);
			return result;

		}

		else if(key == "set_time")
		{
			Sys->set_time(arguments);
		}

		else if(key == "driver_report")
		{
			Sys->driver_report(arguments);
			return result;

		}

		else if(key == "system_report")
		{
			vector <string> information;
			information = Sys->system_report(arguments);
			for(int i=0; i<information.size(); i++)
				result += information[i];
			return result;
		}

		else 
		{
			cerr << "else" << endl;
		}

	}catch(Invalid_Username ex) {return "Invalid Username\n";
	}catch(Invalid_PhoneNumber ex) {return "Invalid Phone Number\n";
	}catch(Invalid_Command ex){return "Invalid Command\n";
	}catch(Invalid_SpaceShipNumber ex){return "Invalid SpaceShip Number\n";
	}catch(Invalid_SpaceShipModel ex){return "Invalid SpaceShip Model\n";
	}catch(Not_Logged_In ex){return "Not Logged In\n";
	}catch(Not_Enough_Count ex){return "Not Enough Count\n";
	}catch(No_Discount_Code_Found ex){return "Invalid Discount Code\n";
	}catch(Illegal_Access ex){return "Illegal Access\n";
	}catch(Uncorrect_Username ex){return "Uncorrect Username\n";
	}catch(Wrong_Username_Or_Password ex){return "Wrong Username Or Password\n";			
	}catch(Waiting_For_Acception ex){return "Waiting for Acception\n";
	}catch(Wrong_Address ex){return "Wrong Address\n";
	}catch(Not_Rated ex){return "First Rate Your Last Trip\n";
	}catch(Invalid_Address ex){return "Invalid Address\n";
	}catch(No_Waiting_Driver ex){return "There Is No Item To Show\n";
	}
}

/*void check_arguments(string command)
{
	int counter = 0;
	for(int i=0; i<command.size(); i++)
		if(command.at(i) == ' ')
			counter++;
	if(counter < 2)
		throw Few_Arguments_Error();
}*/

/*int main()
{
	Admin adm("admin","s3cret");
	World wrd;
	wrd.read_topology();
	SyStem Sys(&adm, &wrd);
	string com;
	while(getline(cin, com))
	{
		Command command(com);
		command.run(Sys,wrd);
	}
}*/