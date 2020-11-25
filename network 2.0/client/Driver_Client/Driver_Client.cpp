#include "Driver_Client.h"
#include "client_exception.h"

Driver_Client :: Driver_Client(char* argv1, char* argv2)
{
	socket = new ClientSocket(string(argv1), Tools::mystoi(argv2));
	cout << "# connection established\n";
	is_login = false;
	is_registered = false;
}

void Driver_Client :: set_key(string command)
{
	string temp;
	vector <string> arguments;
	stringstream info (command);
	while (info >> temp)
		arguments.push_back(temp);
	key = arguments[0];
}

string Driver_Client :: find_username(string command)
{
	string temp;
	vector <string> arguments;
	stringstream info (command);
	while (info >> temp)
		arguments.push_back(temp);
	return arguments[1];
}

void Driver_Client :: send(string command)
{
	command = username + " " + command;
	cerr <<command << "  " << endl;
	socket->send(command);
	receive();
}

void Driver_Client :: check_command(string command)
{
		
	if(key == "register")	
	{
		is_registered = true;
		command.insert(8,"_driver");
		string temp = find_username(command);
		command = command.erase(15,temp.size()+1);
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
	else if(key == "set_status" && is_login == true && is_registered == true)
	{
		command = command.erase(10,username.size()+1);
		send(command);
	}
	else if(key == "estimate_trip" && is_login == true && is_registered == true)
	{
		command = command.erase(13,username.size()+1);
		send(command);
	}
	else if(key == "show_trip_requests" && is_login == true && is_registered == true)
	{
		command = command.erase(18,username.size()+1);
		send(command);
	}
	else if(key == "accept_trip_request" && is_login == true && is_registered == true)
	{
		command = command.erase(19,username.size()+1);
		send(command);
	}
	else if(key == "arrived" && is_login == true && is_registered == true)
	{
		command = command.erase(7,username.size()+1);
		send(command);
	}
	else if(key == "end_trip" && is_login == true && is_registered == true)
	{
		command = command.erase(8,username.size()+1);
		send(command);
	}
	else
		cout << "Invalid_Command" << endl;
}

void Driver_Client :: receive()
{
	cout << socket->receive();
}