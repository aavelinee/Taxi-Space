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

string Driver_Client :: send(string command)
{
    command = username + " " + command;
    socket->send(command);
    string temp = socket->receive();
    if(temp == "Wrong Username Or Password\n")
        is_login = false;
    return temp;
}

string Driver_Client :: check_command(string command)
{
		
	if(key == "register")	
	{
		is_registered = true;
		command.insert(8,"_driver");
		string temp = find_username(command);
		command = command.erase(15,temp.size()+1);
		command = temp + " " + command;
        socket->send(command);
        return socket->receive();
	}
	else if(key == "login" && is_registered == true)
	{
		is_login = true;
		username = find_username(command);
		command = command.erase(5,username.size()+1);
//		send(command);
	}
/*	else if(key == "set_status" && is_login == true && is_registered == true)
        send(command);
	else if(key == "estimate_trip" && is_login == true && is_registered == true)
        send(command);
	else if(key == "show_trip_requests" && is_login == true && is_registered == true)
        send(command);
	else if(key == "accept_trip_request" && is_login == true && is_registered == true)
        send(command);
	else if(key == "arrived" && is_login == true && is_registered == true)
        send(command);
	else if(key == "end_trip" && is_login == true && is_registered == true)
        send(command);*/
    return send(command);
}

//void Driver_Client :: receive()
//{
//	cout << socket->receive();
//}
