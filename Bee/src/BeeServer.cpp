#include "BeeServer.h"
#include "ServerArgv.h"
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


BeeServer::BeeServer()
{
	_pMem = NULL;
	_serverFlag = false;
	_serverState = SERVER_IDLE;
}

BeeServer::~BeeServer()
{

	if(getState() != SERVER_RUNNING)
	{
		delete _pMem;
		std::cout<<"delete mem"<<std::endl;
	}

	std::cout<<_serverState<<std::endl;
	std::cout<<"~BeeServer"<<std::endl;

}

void BeeServer::initialize(Application& self)
{	
	loadConfiguration(); // load default configuration files, if present
	ServerApplication::initialize(self);
	_processName = Poco::Util::Application::instance().config().getString("app.no");
	
	
}

void BeeServer::uninitialize()
{
	ServerApplication::uninitialize();
}

void BeeServer::defineOptions(OptionSet& options)
{
	ServerApplication::defineOptions(options);

	options.addOption(
		Option("help", "h", "display help information on command line arguments")
		.required(false)
		.repeatable(false)
		.callback(OptionCallback<BeeServer>(this, &BeeServer::handleHelp)));

	options.addOption(
		Option("stop", "stop", "stop process.")
		.required(false)
		.repeatable(false)
		.argument("taskids w/o arguments", false)
		.callback(OptionCallback<BeeServer>(this, &BeeServer::stop)));

	options.addOption(
		Option("start", "start", "start process.")
		.required(false)
		.repeatable(false)
		.argument("taskids w/o arguments", false)
		.callback(OptionCallback<BeeServer>(this, &BeeServer::start)));

	options.addOption(
		Option("query", "q", "query process state.")
		.required(false)
		.repeatable(false)
		.argument("taskids w/o arguments", false)
		.callback(OptionCallback<BeeServer>(this, &BeeServer::query)));
}

void BeeServer::handleHelp(const std::string& name, const std::string& value)
{
	setServerState(SERVER_QUERY);
	displayHelp();
	stopOptionsProcessing();
}

void BeeServer::displayHelp()
{
	HelpFormatter helpFormatter(options());
	helpFormatter.setCommand(commandName());
	helpFormatter.setUsage("OPTIONS");
	helpFormatter.setHeader("A sample server application that demonstrates some of the features of the Util::ServerApplication class.");
	helpFormatter.format(std::cout);
}

void BeeServer::stop(const std::string& name, const std::string& value)
{
	readMemory();
	if (_serverState != SERVER_RUNNING)
	{
		std::cout<<"System is not in running!"<<std::endl;		
	}
	
	setServerState(SERVER_FINISHED);	
	writeMemory(_serverState);	
}

void BeeServer::start(const std::string& name, const std::string& value)
{
	readMemory();
	if (_serverState == SERVER_RUNNING)
	{
		std::cout<<"process already started"<<std::endl;
	}	
}

void BeeServer::query(const std::string& name, const std::string& value)
{
	readMemory();
	switch (_serverState)
	{
	case SERVER_IDLE: 
		std::cout<<"System is not in running!"<<std::endl;
		break;
	case SERVER_RUNNING:
		std::cout<<_chalNo<<":	 running"<<std::endl;
		break;
	default:
		break;
	}

	std::cout<<"query state: "<<_serverState<<std::endl;
	setServerState(SERVER_QUERY);
}

void BeeServer::writeMemory(ServerState serverState)
{	
	char a[2];
	memset(a, 0, 2);
	sprintf(a, "%d", serverState);
	strcpy(_pMem->begin(), a);
}

void BeeServer::readMemory()
{
	if (_pMem == NULL)
	{
		//_chalNo = Application::instance().config().getString("channel");
		_processName = Application::instance().config().getString("application.baseName");
		_pMem = new SharedMemory(_processName, 2, SharedMemory::AM_WRITE);
	}
	_serverState = (ServerState)atoi(_pMem->begin());	
}

void BeeServer::task()
{

}

int BeeServer::main(const std::vector<std::string>& args)
{
		
	if (_serverState == SERVER_IDLE)
	{
		//create shared memory if start with non params
		readMemory();
		_serverFlag = true;
		setServerState(SERVER_RUNNING);
		writeMemory(_serverState);
		ServerArgv* exRun  = new ServerArgv(*this);
		_exThread.start(*exRun);

		//BeeTask* pTask = new BeeTask();
		//string rule = Application::instance().config().getString("rule");
		//pTask->setRule(rule);
		
		//TaskManager tm;
		//tm.start(pTask);
		task();
		waitForTerminationRequest();
		//tm.cancelAll();
		//tm.joinAll();

	}
	return Application::EXIT_OK;
}

//POCO_SERVER_MAIN(BeeServer)
