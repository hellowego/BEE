#include "dbi/MysqlSessionFactory.h"
#include "Poco/Data/MySQL/Connector.h"
#include "Poco/Exception.h"
#include "Poco/Data/MySQL/MySQLException.h"
#include "Poco/ThreadPool.h"
#include "Poco/ThreadTarget.h"
#include "dbi/MysqlSessionFactory.h"

//#include <unistd.h>

using Poco::Data::MySQL::ConnectionException;
MysqlSessionFactory* MysqlSessionFactory::_mysqlSessionFactory(NULL);

MysqlSessionFactory::MysqlSessionFactory()
:_connectionString(""),_pool(NULL),_janitorTimer(15000, 15000),
_min(2),_max(50),_idleTime(60),_hasAttemptTimes(0),_isInitialized(false)
{
	MySQL::Connector::registerConnector();
}

MysqlSessionFactory::~MysqlSessionFactory()
{

	if(_pool != NULL)
	{	
		//������������������
		/*if(_pool->used() > 0)
			_pool->dispose();*/
		//������������������
		while(_pool->idle() > 0)
		{
			try
			{
				Session session(_pool->get());
				session.close();
			}
			catch(...)
			{
				//��������������������������������������������������������������
				//������������
			}
		}
		_janitorTimer.stop();
		delete _pool;
		_pool = NULL;
		MySQL::Connector::unregisterConnector();
	}
}


void MysqlSessionFactory::create(const std::string& dbName,const std::string& userName,const std::string& password,const int& min /* = 10 */,const int& max /* = 50 */,const int& idleTime /* = 60 */)
{
	if(_pool == NULL)
	{
		_connectionString = Poco::format("db=%s;user=%s;password=%s",dbName,userName,password);
		_min = min;
		_max = max;
		_idleTime = idleTime;

		if(_pool == NULL)
		{
			_pool = new Poco::Data::SessionPool(MySQL::Connector::KEY,_connectionString,_min,_max,_idleTime);
			//������
			initialize();
			//������������������������������
			Poco::TimerCallback<MysqlSessionFactory> callback(*this, &MysqlSessionFactory::onJudgeSession);
			_janitorTimer.start(callback);
		}
	}
}


void MysqlSessionFactory::initialize()
{
	while(1)
	{
		try
		{
			//��������������������������������������������
			Session session(_pool->get());
			_hasAttemptTimes ++;
			_isInitialized = true;
			break;
		}
		catch(ConnectionException &ex)
		{
			//����������������������������������������������������������
			//����������������������������
			if(!_hasAttemptTimes)
			{
				throw ex;
			}

			//����������������������������������������������������������������
			//��������������
			//Sleep(60000);
		}

	}
	//������������������
	Poco::ThreadPool threadPool(2,_min);
	//������������������
	std::vector<Poco::ThreadTarget*> targets;
	for(int i = 0;i < _min; i++)
	{
		Poco::ThreadTarget* target = new Poco::ThreadTarget(&MysqlSessionFactory::generateMinSession);
		threadPool.start(*target);
		targets.push_back(target);
	}
	//��������������������������������������������������������
	threadPool.joinAll();
	for(std::vector<Poco::ThreadTarget*>::iterator iter = targets.begin(); iter != targets.end(); iter ++)
	{
		delete *iter;
	}	
}

void MysqlSessionFactory::generateMinSession()
{
	Session session(MysqlSessionFactory::instance().getSession());
	//Sleep(100);
}

void MysqlSessionFactory::onJudgeSession(Poco::Timer&)
{
	//��������������
	if(!_isInitialized) return;
	try
	{
		Session session(MysqlSessionFactory::instance().getSession());
		session.commit();
	}
	catch(ConnectionException &ex)
	{
		//����������������
		_isInitialized = false;
		//��������
		//if(ex.isConnectError())
		{
			try
			{
				//��������������������
				while(_pool->used() > 0)
				{
					Sleep(1000);
				}

				//������������������
				while(_pool->idle() > 0)
				{
					try
					{
						Session session(_pool->get());
						session.close();
					}
					catch(...)
					{
						//��������������������������������������������������������������
						//������������
					}
				}
				//����������
				initialize();
			}
			catch(ConnectionException &)
			{
				//std::cout << "Step-3:" + oe.message() << std::endl;
			}
			catch(Poco::Exception &)
			{
				//std::cout << "Step-4:" + ex.message() << std::endl;
			}
		}
	}
}

Session MysqlSessionFactory::getSession()
{
	if(_pool&&_isInitialized)
	{
		//������������������������
		if(!_pool->available())
		{
			Poco::Timestamp lastUsed;
			//��������������������������������������
			while(!_pool->available())
			{
				if((int) (lastUsed.elapsed()/Poco::Timestamp::resolution()) > 60)
					throw MySQL::MySQLException("No more sessions available from the session pool");
				Sleep(100);
			}
		}
	}
	else
	{
		
		throw MySQL::MySQLException("The session pool should be initialized before use it. Throws the exception may be the database is unavailable.");
	}
	return Session(_pool->get());	
}

int MysqlSessionFactory::getUsed() const
{
	return _pool->used();
}

MysqlSessionFactory&  MysqlSessionFactory::instance()
{ 
	if(!_mysqlSessionFactory) 
		_mysqlSessionFactory = new  MysqlSessionFactory(); 
	return *_mysqlSessionFactory;
}

void MysqlSessionFactory::close()
{
	if(_mysqlSessionFactory)
	{
		delete _mysqlSessionFactory;
		_mysqlSessionFactory = NULL;
	}
}

