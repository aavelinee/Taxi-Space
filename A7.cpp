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

class Trip;

class Galaxy;

class Utility
{
	public:
		static int stringTOascii(string username)
		{
			long int temp=0;
			for(int i=0; i<username.size(); i++)
				temp += int(username[i]);
			return temp;
		}

		static string intTOstring(int integer)
		{
			string Result;
			stringstream convert;
			convert << integer;
			Result = convert.str();
			return Result;
		}

		static int stringTOint(string str)
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
};

class Planet
{
	public:
		Planet(string nm) {name = nm;}
		string get_name() {return name;}
		vector <Planet*> get_neighbours() {return neighbour_planets;}
		void construct_neighbour_planets(ifstream& topology, Galaxy* glxy);

	private:
		vector <Planet*> neighbour_planets;
		string name;
};

class Galaxy
{
	public:
		Galaxy (string nm) {name = nm;}
		void construct_planets(ifstream& topology);
		vector <Planet*> get_palnets () {return planets;}
		string get_name() {return name;}
		Planet* planet_finding(string planet_name);
		bool planet_exists(string planet_name);

	private:
		string name;
		vector <Planet*> planets;
};

class World
{
	public :
		void read_topology();
		World () {};
		void construct_galaxies(ifstream &topology);
		vector <Galaxy*> get_galaxies() {return galaxies;}

	private:
		vector <Galaxy*> galaxies;
};

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
	// for(int i=0; i<galaxies.size(); i++)
	// 	cerr << "galaxy names : " << galaxies[i]->get_name() << endl;
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
				return planets[i];
}

void Galaxy :: construct_planets(ifstream& topology)
{
	bool is_available;
	string name_of_planet;
	int neighbour_number;

	topology >> name_of_planet;
	topology >> neighbour_number;

	if(planet_exists(name_of_planet) == true)
	{
		for(int i=0; i<planets.size(); i++)
			if(name_of_planet == planets[i]->get_name())
				is_available = true;
		if(is_available == false)
			planets.push_back(planet_finding(name_of_planet));
	}
	else
	{
		Planet* p = new Planet(name_of_planet);
		planets.push_back(p);
	}
	
	for(int i=0; i<neighbour_number; i++)
		planets.back()->construct_neighbour_planets (topology, this);
	// for(int i=0; i<planets.size(); i++)
	// 	cerr << "planet names : " << planets[i]->get_name() << endl;
}

void Planet :: construct_neighbour_planets(ifstream& topology, Galaxy* glxy)
{
	string neighbour_name;
	bool flag = false;
	bool is_available;
	topology >> neighbour_name;

	if(glxy->planet_exists(neighbour_name))
	{
		for(int i=0; i<neighbour_planets.size(); i++)
			if(neighbour_name == neighbour_planets[i]->get_name())
				return;
		neighbour_planets.push_back(glxy-> planet_finding(neighbour_name));
	}
	else
	{
		Planet* plnt = new Planet(neighbour_name);
		neighbour_planets.push_back(plnt);
	}
}

class Time
{
	public:
		Time(string dtime){date_time = dtime;}
		string get_time() {return date_time;}
		void set_dtime(string dt) {date_time = dt;}
	private:
		string date_time;
};

class SpaceShip
{
	public:
		SpaceShip (string number, string model, string year, string color);
		string get_model() {return spaceship_model;}
		string get_number() {return spaceship_number;}
		string get_year_production() {return production_date;}
		string get_color() {return spaceship_color;}
	private:
		string spaceship_number;
		string spaceship_model;
		string spaceship_color;
		string production_date;
};

// void Galaxy :: DFS(Planet* begin, Planet* end)

SpaceShip :: SpaceShip (string number, string model, string year, string color)
{
	spaceship_number = number;
	spaceship_model = model;
	production_date = year;
	spaceship_color = color;
}

class User
{
	public:
		User(string usrnm, string pass, bool lgin);

		bool get_is_login() {return login;}
		string get_username() {return username;}
		string get_password() {return password;}
		void set_is_login(bool lg) {login = lg;}
	protected:
		string username;
		string password;
		bool login;
};

User :: User(string usrnm, string pass, bool lgin)
{
	username = usrnm;
	password = pass;
	login =lgin;
}

class Admin : public User
{
	public:
		Admin(string usrnm, string pass);
};

Admin :: Admin (string usrnm, string pass) : User (usrnm, pass, false) {}

class Passenger : public User
{
	public: 
		Passenger(string usrnm, string pass, string phnum);
		string get_phone_number() {return phone_number;}
		long long get_discount_code() {return discount_code;}
		int get_available_count() {return available_count;}
		long int get_passenger_credit () {return passenger_credit;}
		string get_passenger_username() {return username;}

		void charge_account(int credit) {passenger_credit += credit;}
		void subtract_account(int sub) {passenger_credit -= sub;}
		void set_available_count(int count) {available_count -= count;}
	private:
		string phone_number;
		long long discount_code;
		long int passenger_credit;
		int available_count;
		bool is_on_trip;
};

Passenger :: Passenger (string usrnm, string pass, string phnum) : User(usrnm, pass, false)
{
	phone_number = phnum;
	discount_code = Utility :: stringTOascii(usrnm);
	passenger_credit = 0;
	available_count = 5;
	is_on_trip = false;
}

class Driver : public User
{
	public :
		Driver(string usrnm, string pass, SpaceShip *spcship);
		SpaceShip* get_spaceship_information() {return spaceship;}
		bool get_is_VIP() {return VIP;}
		string get_status() {return status;}
		string get_current_address () {return current_address;}

		void set_VIP(bool v_i_p) {VIP = v_i_p;}
		void set_status(string sts) {status = sts;}
		void set_current_address(string cur_add) {current_address = cur_add;}
		void set_finished_trip(Trip* trp) {finished_trips.push_back(trp);}

	private:
		SpaceShip* spaceship;

		vector <Trip*> finished_trips;
		vector <Trip*> trip_requests;
		
		string status;
		string current_address;

		long int driver_credit;

		bool VIP;
};

Driver :: Driver (string usrnm, string pass, SpaceShip *spcship) : User (usrnm, pass, false)
{
	spaceship = spcship;
	status = "unavailable";
	VIP = false;
}

class Trip
{
	public:
		Trip (Passenger* pssngr, string srce_add, vector <string> destinations, Time* time, bool isVIP);
		Passenger* get_passenger () {return passenger;}
		bool get_isaccepted() {return is_accepted;}
		Driver* get_driver(){return driver;}
		string get_source_address() {return source_address;}
		vector <string> get_destinations() {return destinations;}
		bool get_is_ended() {return is_ended;}
		bool get_has_rated() {return has_rated;}
		int get_rate() {return rate;}

		void set_is_ended(bool ended) {is_ended = ended;}
		void set_driver(Driver* drvr) {driver = drvr;}
		void set_isaccepted (bool isaccepted) {is_accepted = isaccepted;}
		void set_has_rate(bool rated) {has_rated = rated;}
		void set_rate(int rt) {rate = rt;}


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

class SyStem
{
	public:
		SyStem(Admin* adm);

		vector <Driver*> get_all_drivers () {return drivers;}
		vector <Driver*> get_waiting_drivers () {return waiting_drivers;}
		vector <Passenger*> get_passengers () {return passengers;}
		vector <Trip*> get_trips () {return trips;}
		Admin* get_admin() {return admin;}
		Time* get_dtime() {return datetime;}
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

SyStem :: SyStem (Admin* adm)
{
	admin = adm;
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
	if(username == "admin" && admin->get_is_login())
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

void SyStem :: set_status (vector <string> information, World& wrd)
{
	vector <string> address;
	bool galaxy_existance;
	bool planet_existance;
	vector <Galaxy*> galaxies = wrd.get_galaxies();
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
		if(admin->get_is_login())
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
		if(admin->get_is_login())
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
		if(admin->get_is_login())
		{
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

vector <string> SyStem :: request_trip(vector <string> information)
{

	long int pass_credit;
	vector <string> cost_distance;
	string source_address;
	vector <string> destinations;
	bool isvip;
	bool flag = false;

	for(int i=0; i<trips.size(); i++)
		if(information[0] == trips[i]->get_passenger()->get_username())
			pass_credit = trips[i]->get_passenger()->get_passenger_credit();

	if(is_login(information[0]))
	{
		for(int i=0; i<trips.size(); i++)
		{
			if(information[0] == trips[i]->get_passenger()->get_username())
			{
				flag = true;
				if(trips[i]->get_has_rated())
				{
					// cost_distance = estimate_trip(information);
					if(if_cost_is_available(pass_credit, Utility :: stringTOint(cost_distance[0])))
					{
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
						for(int i=0; i<passengers.size(); i++)
							if(information[0] == passengers[i]->get_username())
							{
								Trip* tr = new Trip(passengers[i],source_address, destinations, datetime ,isvip);
								trips.push_back(tr);
							}
						
						return cost_distance;
					}
					else
						throw Not_Enough_Credit();
				}
				else
					throw Not_Rated();
			}
		}
		if(flag == false)
		{
			// cost_distance = estimate_trip(information);

			if(if_cost_is_available(pass_credit, Utility :: stringTOint(cost_distance[0])))
			{
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
				for(int i=0; i<passengers.size(); i++)
					if(information[0] == passengers[i]->get_username())
					{
						Trip* tr = new Trip(passengers[i],source_address, destinations, datetime, isvip);
						trips.push_back(tr);
					}
			}
			else
				throw Not_Enough_Credit();

			return cost_distance;
		}
	}
	else
		throw Not_Logged_In();
}

vector <string> SyStem :: estimate_trip(vector <string> information)
{

}

void SyStem :: cancle_trip(vector <string> information)
{
	if(is_login(information[0]))
	{
		for(int i=0; i<trips.size(); i++)
			if(information[0] == trips[i]->get_passenger()->get_username())
			{
				if(trips[i]->get_isaccepted() == true)
					throw Invalid_Command();
				else
					trips.erase(trips.begin() + i);
			}
		for(int i=0; i<trips.size(); i++)
			cerr << "&  " << trips[i]->get_passenger()->get_username() << endl;
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
				trips[i]->set_has_rate(true);
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

class Command
{
	public:
		Command(string commands);
		void run(SyStem& Sys, World& wrd);
		void set_key (string ky) {key = ky;}
		void set_arguments (vector <string> arg) {arguments = arg;}
		string get_key() {return key;}
		vector <string> get_argument () {return arguments;}
	private:
		string key;
		vector <string> arguments;
};

Command :: Command (string commands)
{
	string temp;
	stringstream info (commands);
	while (info >> temp)
		arguments.push_back(temp);

	key = arguments[1];
	arguments.erase(arguments.begin() + 1);
}

void Command:: run(SyStem& Sys, World& wrd)
{
	try
	{
		if(key == "register_passenger")
		{
			// check_arguments(arguments);
			Sys.passenger_registration(arguments);
		}

		else if(key == "register_driver")
		{

			Sys.driver_registration(arguments);
		}

		else if(key == "accept_registration")
		{

			Sys.accept_registration(arguments);
		}

		else if(key == "reject_registration")
		{

			Sys.reject_registration(arguments);
		}

		else if(key == "show_registration_requests")
		{
			vector <vector <string> > requests;
			requests = Sys.show_registration_requests(arguments);
			for(int i=0; i<requests.size(); i++)
			{
				for(int j=0; j<requests[i].size(); j++)
					cout << requests[i][j] << " ";
				cout << endl;
			}
		}

		else if(key == "get_discount_code")
		{
			vector <int> information;
			information = Sys.get_discount_code(arguments);
			for(int i=0; i<information.size(); i++)
				cout << information[i] << " ";
			cout << endl;
		}

		else if(key == "login")
		{

			Sys.log_in(arguments);
		}

		else if(key == "logout")
		{

			Sys.log_out(arguments);
		}

		else if(key == "set_status")
		{

			Sys.set_status(arguments,wrd);
		}

		else if(key == "charge_account")
		{

			Sys.charge_account(arguments);
		}

		else if(key == "get_credit")
		{
			int _credit;
			_credit = Sys.get_credit(arguments);
			cout << _credit << endl;
		}

		else if(key == "request_trip")
		{
			vector <string> temp;
			temp = Sys.request_trip(arguments);
			for(int i=0; i<temp.size(); i++)
				cout << temp[i] << " ";
			cout << endl;
		}

		else if(key == "estimate_trip")
		{
			vector <string> temp;
			temp = Sys.estimate_trip(arguments);
			for(int i=0; i<temp.size(); i++)
				cout << temp[i] << " " ;
			cout << endl;
		}

		else if(key == "cancle_trip_request")
		{

			Sys.cancle_trip(arguments);
		}

		/*else if(key == "show_trip_requests")
		{
			vector <vector <string> > requests;
			requests = Sys.show_trip_requests(arguments);
			for(int i=0; i<requests.size(); i++)
			{
				for(int j=0; j<requests[i].size(); j++)
					cout << requests[i][j] << " ";
				cout << endl;
			}
		}*/

		else if(key == "accept_trip_request")
		{
			Sys.accept_trip_request(arguments);
		}

		else if(key == "arrived")
		{

			Sys.arrived(arguments);
		}

		else if(key == "trip_status")
		{
			vector <string> information;
			information = Sys.trip_status(arguments);
			for(int i=0; i<information.size(); i++)
				cout << information[i] << " ";
			cout << endl;
		}

		else if(key == "end_trip")
		{

			Sys.end_trip(arguments);
		}

		else if(key == "rate_driver")
		{

			Sys.rate_driver(arguments);
		}

		else if(key == "set_time")
		{
			Sys.set_time(arguments);
		}

		else if(key == "driver_report")
		{
			Sys.driver_report(arguments);
		}

		else if(key == "system_report")
		{
			vector <string> information;
			information = Sys.system_report(arguments);
			for(int i=0; i<information.size(); i++)
				cout << information[i] << " ";
			cout << endl;
		}

		else 
		{
			cerr << "else" << endl;
		}

	}catch(Invalid_Username ex) {cout << "Invalid Username" << endl;
	}catch(Invalid_PhoneNumber ex) {cout << "Invalid Phone Number" << endl;
	}catch(Invalid_Command ex){cout << "Invalid Command" << endl;
	}catch(Invalid_SpaceShipNumber ex){cout << "Invalid SpaceShip Number" << endl;
	}catch(Invalid_SpaceShipModel ex){cout << "Invalid SpaceShip Model" << endl;
	}catch(Not_Logged_In ex){cout << "Not Logged In" << endl;
	}catch(Not_Enough_Count ex){cout << "Not Enough Count" << endl;
	}catch(No_Discount_Code_Found ex){cout << "Invalid Discount Code" << endl;
	}catch(Illegal_Access ex){cout << "Illegal Access" << endl;
	}catch(Uncorrect_Username ex){cout << "Uncorrect Username" << endl;
	}catch(Wrong_Username_Or_Password ex){cout << "Wrong Username Or Password" << endl;			
	}catch(Waiting_For_Acception ex){cout << "Waiting for Acception" << endl;
	}catch(Wrong_Address ex){cout << "Wrong Address" << endl;
	}catch(Not_Rated ex){cout << "First Rate Your Last Trip" << endl;
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

int main()
{
	Admin adm("admin","s3cret");
	SyStem Sys(&adm);
	World wrd;
	wrd.read_topology();
	string com;

	/*for(int i=0; i<wrd.get_galaxies().size(); i++)
	{
		cerr << "galaxy name : " <<  wrd.get_galaxies()[i]->get_name() << endl;
		for(int j=0; j<wrd.get_galaxies()[i]->get_palnets().size(); j++)
		{
			cerr << "planet name : " << wrd.get_galaxies()[i]->get_palnets()[j]->get_name() << endl;
			for(int k=0; k<wrd.get_galaxies()[i]->get_palnets()[j]->get_neighbours().size(); k++)
				cerr << "neighbour name : " << wrd.get_galaxies()[i]->get_palnets()[j]->get_neighbours()[k]->get_name() << endl;
		}

	}*/

	while(getline(cin, com))
	{
		Command command(com);
		command.run(Sys,wrd);
	}
}