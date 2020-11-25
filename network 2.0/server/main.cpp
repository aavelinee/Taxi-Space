#include <cstdlib>
#include "server.h"
#include "system.h"

using namespace std;


// 'Server' is an abstract class, so define your own server class inheriting from the 'Server'
class MyServer : public Server 
{
  private:
    SyStem* system;
    string username;

  public:
    MyServer(int port, SyStem* Sys) : Server(port) {system = Sys;}
    void on_standard_input(string line);
    void on_new_connection(int identifier);
    void on_new_message(int identifier, string message);
    void on_terminated_connection(int identifier);

};

void MyServer::on_standard_input(string line)
{
  string result;
  cout << "STDIN: " << line << endl;
  if (line == ":q")
    stop();

  if(line == "login admin s3cret")
  {
    line = line.erase(5,6);
    line = "admin " + line;
    Command com(line);
    cerr << line << endl;
    string result = com.run(system);
  }
  else if(line == "accept_registration")
  {
    line = line.erase(19,6);
    line = "admin " + line;
    Command com(line);
    string result = com.run(system);
  }
  else if(line == "reject_registration")
  {
    line = line.erase(19,6);
    line = "admin " + line;
    Command com(line);
    string result = com.run(system);
  }
  else if(line == "show_registration_requests")
  {
    line = line.erase(26,6);
    line = "admin " + line;
    Command com(line);
    string result = com.run(system);
  }
  else if(line == "set_time")
  {
    line = line.erase(8,6);
    line = "admin " + line;
    Command com(line);
    string result = com.run(system);
  }
  else if(line == "driver_report")
  {
    line = line.erase(13,6);
    line = "admin " + line;
    Command com(line);
    string result = com.run(system);
  }
  else if(line == "passenger_report")
  {
    line = line.erase(16,6);
    line = "admin " + line;
    Command com(line);
    string result = com.run(system);
  }
  else if(line == "system_report")
  {
    line = line.erase(13,6);
    line = "admin " + line;
    Command com(line);
    string result = com.run(system);
  }
  cout << result << endl;
}

void MyServer::on_new_connection(int identifier) 
{
  cout << "NEW CONNECTION: " << identifier << endl;
}

void MyServer::on_new_message(int identifier, string message)
{
  cout << "NEW MESSAGE FROM " << identifier <<": " << message << endl;
  Command com(message);
  string result = com.run(system);
  send(identifier, result);
}

void MyServer::on_terminated_connection(int identifier)
{
  cout << "TERMINATED CONNECTION: " << identifier << endl;
}


int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "valid operation: " << argv[0] << " [port number]\n";
    exit(-1);
  }
  

  Admin adm("admin","s3cret");
  World wrd;
  wrd.read_topology();
  SyStem Sys(&adm, &wrd);
  MyServer server(Tools::mystoi(argv[1]),&Sys);
  server.run();  
  return 0;
}