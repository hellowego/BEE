//
//BeeServer.h
//
#ifndef BEESERVER_H_
#define BEESERVER_H_

#include "task/BeeTask.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/TaskManager.h"
#include "Poco/SharedMemory.h"
#include <iostream>

using Poco::Util::Application;
using Poco::Util::ServerApplication;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;
using Poco::TaskManager;
using Poco::SharedMemory;

class BeeServer : public ServerApplication
{
public:

	enum ServerState
	{
		SERVER_IDLE,
		SERVER_STARTING,
		SERVER_RUNNING,
		SERVER_CANCELLING,
		SERVER_QUERY,
		SERVER_FINISHED
	};

	BeeServer();	

	~BeeServer();
	
	void setServerState(ServerState serverState){ _serverState = serverState;}
	
	std::string getProcessName(){return _processName;}
	
	ServerState getState()
	{
		readMemory();
		return _serverState;
	}

protected:
	void initialize(Application& self);
	void uninitialize();
	void defineOptions(OptionSet& options);
	void handleHelp(const std::string& name, const std::string& value);
	void displayHelp();
	int main(const std::vector<std::string>& args);
	
	//stop process example windows: Bee.exe /stop . linux : ./Bee --stop
	void stop(const std::string& name, const std::string& value);

	//start process example windows: Bee.exe /start . linux : ./Bee --start
	void start(const std::string& name, const std::string& value);

	//query process state example windows: Bee.exe /query . linux : ./Bee --query
	void query(const std::string& name, const std::string& value);
	
	virtual void task();

	//write process state to shared memory
	void writeMemory(ServerState serverState);

	//get share memory, if share memory is not exist create it;
	void readMemory();

private:

	Poco::Thread    _exThread;

	SharedMemory* _pMem;

	ServerState _serverState;

	std::string _processName;

	std::string _chalNo;

	bool _serverFlag;
};

#endif
