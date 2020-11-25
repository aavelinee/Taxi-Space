#include "System.h"
#include "Trip.h"


vector <Driver*> SyStem :: get_all_drivers () {return drivers;}
vector <Driver*> SyStem :: get_waiting_drivers () {return waiting_drivers;}
vector <Passenger*> SyStem :: get_passengers () {return passengers;}
vector <Trip*> SyStem :: get_trips () {return trips;}
Admin* SyStem :: get_admin() {return admin;}
Time* SyStem :: get_dtime() {return datetime;}

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
