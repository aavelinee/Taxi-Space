#ifndef _Spaceship_
#define _Spaceship_

#include <string>
#include <iostream>

using namespace std;

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

#endif