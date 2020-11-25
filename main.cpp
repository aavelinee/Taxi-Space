#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "System.h"
#include "Command.h"
#include "Universe.h"

using namespace std;

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

	while(getline(cin, com))
	{
		Command command(com);
		command.run(Sys,wrd);
	}
}