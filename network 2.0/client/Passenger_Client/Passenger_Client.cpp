#include "Passenger_Client.h"

using namespace std;

Passenger_Client :: Passenger_Client(char* argv1, char* argv2)
{
	socket = new ClientSocket(string(argv1), Tools::mystoi(argv2));
	cout << "# connection established\n";
	is_login = false;
	is_registered = false;
}

void Passenger_Client :: set_key(string command)
{
	string temp;
	vector <string> arguments;
	stringstream info (command);
	while (info >> temp)
		arguments.push_back(temp);
	key = arguments[0];
}

string Passenger_Client :: find_username(string command)
{
	string temp;
	vector <string> arguments;
	stringstream info (command);
	while (info >> temp)
		arguments.push_back(temp);
	return arguments[1];
}

void Passenger_Client :: send(string command)
{
	command = username + " " + command;
	cerr <<command << "  " << endl;
	socket->send(command);
	receive();
}

void Passenger_Client :: check_command(string command)
{	
	if(key == "register")	
	{
		is_registered = true;
		command.insert(8,"_passenger");
		string temp = find_username(command);
		command = command.erase(19,temp.size()+1);
		command = temp + " " + command;
		send(command);
	}
	else if(key == "login" && is_registered == true)
	{
		is_login = true;
		username = find_username(command);
		command = command.erase(5,username.size()+1);
		send(command);
	}
	else if(key == "get_discount_code" && is_login == true && is_registered == true)
	{
		command = command.erase(17,username.size()+1);
		send(command);
	}
	else if(key == "estimate_trip" && is_login == true && is_registered == true)
	{
		command = command.erase(13,username.size()+1);
		send(command);
	}
	else if(key == "request_trip" && is_login == true && is_registered == true)
	{
		command = command.erase(12,username.size()+1);
		send(command);
	}
	else if(key == "cancel_trip" && is_login == true && is_registered == true)
	{
		command = command.erase(11,username.size()+1);
		send(command);
	}
	else if(key == "trip_status" && is_login == true && is_registered == true)
	{
		command = command.erase(10,username.size()+1);
		send(command);
	}
	else if(key == "rate_driver" && is_login == true && is_registered == true)
	{
		command = command.erase(11,username.size()+1);
		send(command);
	}
	else if(key == "charge_account" && is_login == true && is_registered == true)
	{
		command = command.erase(14,username.size()+1);
		send(command);
	}
	else
		cout << "Invalid_Command" << endl;
}

void Passenger_Client :: receive()
{
	cout << socket->receive();
}