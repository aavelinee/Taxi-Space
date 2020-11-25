#include "Universe.h"

class Galaxy;

Planet :: Planet (string nm) {name = nm;}
string Planet :: get_name() {return name;}
vector <Planet*> Planet :: get_neighbours() {return neighbour_planets;}
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


Galaxy :: Galaxy (string nm) {name = nm;}
vector <Planet*> Galaxy :: get_palnets () {return planets;}
string Galaxy :: get_name() {return name;}
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
}

vector <Galaxy*> World :: get_galaxies() {return galaxies;}
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
