#include "Command.h"

void Command :: set_key (string ky) {key = ky;}
void Command :: set_arguments (vector <string> arg) {arguments = arg;}
string Command :: get_key() {return key;}
vector <string> Command :: get_argument () {return arguments;}

Command :: Command (string commands)
{
	string temp;
	stringstream info (commands);
	while (info >> temp)
		arguments.push_back(temp);

	key = arguments[1];
	arguments.erase(arguments.begin() + 1);
}

void Command:: run(SyStem& Sys, World& wrd)
{
	try
	{
		if(key == "register_passenger")
		{
			// check_arguments(arguments);
			Sys.passenger_registration(arguments);
		}

		else if(key == "register_driver")
		{

			Sys.driver_registration(arguments);
		}

		else if(key == "accept_registration")
		{

			Sys.accept_registration(arguments);
		}

		else if(key == "reject_registration")
		{

			Sys.reject_registration(arguments);
		}

		else if(key == "show_registration_requests")
		{
			vector <vector <string> > requests;
			requests = Sys.show_registration_requests(arguments);
			for(int i=0; i<requests.size(); i++)
			{
				for(int j=0; j<requests[i].size(); j++)
					cout << requests[i][j] << " ";
				cout << endl;
			}
		}

		else if(key == "get_discount_code")
		{
			vector <int> information;
			information = Sys.get_discount_code(arguments);
			for(int i=0; i<information.size(); i++)
				cout << information[i] << " ";
			cout << endl;
		}

		else if(key == "login")
		{

			Sys.log_in(arguments);
		}

		else if(key == "logout")
		{

			Sys.log_out(arguments);
		}

		else if(key == "set_status")
		{

			Sys.set_status(arguments,wrd);
		}

		else if(key == "charge_account")
		{

			Sys.charge_account(arguments);
		}

		else if(key == "get_credit")
		{
			int _credit;
			_credit = Sys.get_credit(arguments);
			cout << _credit << endl;
		}

		else if(key == "request_trip")
		{
			vector <string> temp;
			temp = Sys.request_trip(arguments);
			for(int i=0; i<temp.size(); i++)
				cout << temp[i] << " ";
			cout << endl;
		}

		else if(key == "estimate_trip")
		{
			vector <string> temp;
			temp = Sys.estimate_trip(arguments);
			for(int i=0; i<temp.size(); i++)
				cout << temp[i] << " " ;
			cout << endl;
		}

		else if(key == "cancle_trip_request")
		{

			Sys.cancle_trip(arguments);
		}

		/*else if(key == "show_trip_requests")
		{
			vector <vector <string> > requests;
			requests = Sys.show_trip_requests(arguments);
			for(int i=0; i<requests.size(); i++)
			{
				for(int j=0; j<requests[i].size(); j++)
					cout << requests[i][j] << " ";
				cout << endl;
			}
		}*/

		else if(key == "accept_trip_request")
		{
			Sys.accept_trip_request(arguments);
		}

		else if(key == "arrived")
		{

			Sys.arrived(arguments);
		}

		else if(key == "trip_status")
		{
			vector <string> information;
			information = Sys.trip_status(arguments);
			for(int i=0; i<information.size(); i++)
				cout << information[i] << " ";
			cout << endl;
		}

		else if(key == "end_trip")
		{

			Sys.end_trip(arguments);
		}

		else if(key == "rate_driver")
		{

			Sys.rate_driver(arguments);
		}

		else if(key == "set_time")
		{
			Sys.set_time(arguments);
		}

		else if(key == "driver_report")
		{
			Sys.driver_report(arguments);
		}

		else if(key == "system_report")
		{
			vector <string> information;
			information = Sys.system_report(arguments);
			for(int i=0; i<information.size(); i++)
				cout << information[i] << " ";
			cout << endl;
		}

		else 
		{
			cerr << "else" << endl;
		}

	}catch(Invalid_Username ex) {cout << "Invalid Username" << endl;
	}catch(Invalid_PhoneNumber ex) {cout << "Invalid Phone Number" << endl;
	}catch(Invalid_Command ex){cout << "Invalid Command" << endl;
	}catch(Invalid_SpaceShipNumber ex){cout << "Invalid SpaceShip Number" << endl;
	}catch(Invalid_SpaceShipModel ex){cout << "Invalid SpaceShip Model" << endl;
	}catch(Not_Logged_In ex){cout << "Not Logged In" << endl;
	}catch(Not_Enough_Count ex){cout << "Not Enough Count" << endl;
	}catch(No_Discount_Code_Found ex){cout << "Invalid Discount Code" << endl;
	}catch(Illegal_Access ex){cout << "Illegal Access" << endl;
	}catch(Uncorrect_Username ex){cout << "Uncorrect Username" << endl;
	}catch(Wrong_Username_Or_Password ex){cout << "Wrong Username Or Password" << endl;			
	}catch(Waiting_For_Acception ex){cout << "Waiting for Acception" << endl;
	}catch(Wrong_Address ex){cout << "Wrong Address" << endl;
	}catch(Not_Rated ex){cout << "First Rate Your Last Trip" << endl;
	}
}