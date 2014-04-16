#ifndef WORKERSERVER_H_
#define WORKERSERVER_H_

#include "BeeServer.h"
#include "Poco/Data/SessionPool.h"
#include "dbi/DBConnectInfoInitializer.h"
#include <vector>

class WorkerServer : public BeeServer
{
public:
	WorkerServer();
	~WorkerServer();

	void task();
protected:
	void initialize(Application& self);
	void uninitialize();

	string getUrlResponse(const string& hostName, const string& url);
	void extractCmb(const string& s1, const string& begin, const string& end, const int& type);
	void extract(const string& str, std::vector<string>& subs);
private:

	Poco::Data::SessionPool* _pSessionPool;

	/**
	 * 数据库连接信息
	 */
	DBConnectInfo _dbInfo;

	Poco::SharedPtr<Poco::Data::Session> _pSession;

	//task params

	std::vector<BeeTask*> _taskVec;

	TaskManager _tm;

};

#endif