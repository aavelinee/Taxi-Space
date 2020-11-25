#include "Spaceship.h"

using namespace std;

SpaceShip :: SpaceShip (string number, string model, string year, string color)
{
	spaceship_number = number;
	spaceship_model = model;
	production_date = year;
	spaceship_color = color;
}
string SpaceShip :: get_model() {return spaceship_model;}
string SpaceShip :: get_number() {return spaceship_number;}
string SpaceShip :: get_year_production() {return production_date;}
string SpaceShip :: get_color() {return spaceship_color;}