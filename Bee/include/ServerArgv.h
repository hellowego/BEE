#ifndef SERVERARGV_H_
#define SERVERARGV_H_

#include "Poco/Runnable.h"
#include "BeeServer.h"

class ServerArgv : public Poco::Runnable
{
public:

	ServerArgv(BeeServer& app);

	~ServerArgv();

	void run();

	bool oneLoop();
protected:
private:
	bool _stop;

	BeeServer& _app;
};

#endif