#ifndef _Universe_
#define _Universe_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Utility.h"

using namespace std;

class Galaxy;

class Planet
{
	public:
		Planet (string nm);
		string get_name ();
		vector <Planet*> get_neighbours ();
		void construct_neighbour_planets (ifstream& topology, Galaxy* glxy);

	private:
		vector <Planet*> neighbour_planets;
		string name;
};

class Galaxy
{
	public:
		Galaxy (string nm);
		void construct_planets (ifstream& topology);
		vector <Planet*> get_palnets ();
		string get_name ();
		Planet* planet_finding (string planet_name);
		bool planet_exists (string planet_name);

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
		vector <Galaxy*> get_galaxies();

	private:
		vector <Galaxy*> galaxies;
};

#endif