#ifndef _Driver_Client_
#define _Driver_Client_

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include "client_socket.h"
#include "client_exception.h"

using namespace std;

class Driver_Client
{
	public:
		Driver_Client(char* argv1, char* argv2);
        string send(string command);
        string check_command(string command);
		void set_key(string command);
		string find_username(string command);


	private:
		ClientSocket* socket;
		string username;
		string key;
		bool is_login;
		bool is_registered;
};

#endif
