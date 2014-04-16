#ifndef MYSQLSESSIONFACTORY_H_
#define MYSQLSESSIONFACTORY_H_
#include "Poco/Data/SessionPool.h"

using Poco::Data::Session;
using namespace Poco::Data;

class MysqlSessionFactory
{
public:

	MysqlSessionFactory();

	~MysqlSessionFactory();

	/*
	 * 获取Oracle工厂类
	 */
	static MysqlSessionFactory&  instance();

	/*
	 * 初始化连接池
	 * @dbName		数据库实例名
	 * @userName	数据库用户
	 * @password	数据库密码
	 * @min			最小连接数 默认10个
	 * @max			最大连接数 默认50个
	 * @idleTime	空闲连接自动回收时间	默认1分钟
	 */
	void create(const std::string& dbName,const std::string& userName,const std::string& password,const int& min = 10,const int& max = 50,const int& idleTime = 60);

	/*
	 * 获取数据库Session对象
	 */
	Session getSession();

	int getUsed() const;

	/*
	 * 关闭工厂类，释放连接池
	 */
	static void close();
protected:
private:

	/*
	 * 静态对象
	 */
	static MysqlSessionFactory* _mysqlSessionFactory;

	/*
	 * 生成最小连接数
	 */
	static void generateMinSession();
	/*
	 * 判断会话有效性
	 */
	void onJudgeSession(Poco::Timer&);
	/*
	 * 初始化
	 */
	void initialize();

	/*
	 * 连接字符串
	 */
	std::string	 _connectionString;
	/*
	 * 数据库连接池
	 */
	Poco::Data::SessionPool* _pool;	
	
	/*
	 * 判断连接是否有效
	 */
	Poco::Timer _janitorTimer;

	mutable Poco::FastMutex _mutex;

	int	_min;
	int _max;
	int _idleTime;
	//已经尝试次数
	int _hasAttemptTimes;
	//是否已经初始化
	bool _isInitialized;
};


#endif