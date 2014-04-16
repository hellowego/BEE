#include "ServerArgv.h"

#include "Poco/Process.h"
#include "Poco/NumberParser.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>


ServerArgv::ServerArgv(BeeServer& app)
:_app(app)
{

}

ServerArgv::~ServerArgv()
{

}

void ServerArgv::run()
{	

	try
	{
		while (!oneLoop())
		{
			Poco::Thread::sleep(5500);
		}

	}
	catch (Poco::Exception& ex)
	{
		std::cout << "MPCFrame Poco exception:" << ex.what() << std::endl;
	}
	catch (std::exception& ex)
	{
		std::cout << "MPCFrame Std exception:" << ex.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "MPCFrame Unknown exception:" << std::endl;
	}
}


bool ServerArgv::oneLoop()
{
	bool stop(false);

	BeeServer::ServerState state = _app.getState();

	std::cout<<"state1: ";
	printf("%i \n", state);

	if (state == BeeServer::SERVER_FINISHED)
	{
		_app.terminate();
		stop = true;
	}
	
	return stop;
}
