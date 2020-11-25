#include <cstdlib>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "client_socket.h"
#include "Driver_Client.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cerr << "valid operation: " << argv[0] << " [server address] [server port]\n";
		exit(-1);
	}

	Driver_Client DC(argv[1], argv[2]);

	string line;
	while (getline(cin, line))
	{
		DC.set_key(line);
		DC.check_command(line);
	}

	return 0;
}