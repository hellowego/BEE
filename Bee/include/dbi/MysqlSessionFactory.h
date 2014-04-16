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
	 * ��ȡOracle������
	 */
	static MysqlSessionFactory&  instance();

	/*
	 * ��ʼ�����ӳ�
	 * @dbName		���ݿ�ʵ����
	 * @userName	���ݿ��û�
	 * @password	���ݿ�����
	 * @min			��С������ Ĭ��10��
	 * @max			��������� Ĭ��50��
	 * @idleTime	���������Զ�����ʱ��	Ĭ��1����
	 */
	void create(const std::string& dbName,const std::string& userName,const std::string& password,const int& min = 10,const int& max = 50,const int& idleTime = 60);

	/*
	 * ��ȡ���ݿ�Session����
	 */
	Session getSession();

	int getUsed() const;

	/*
	 * �رչ����࣬�ͷ����ӳ�
	 */
	static void close();
protected:
private:

	/*
	 * ��̬����
	 */
	static MysqlSessionFactory* _mysqlSessionFactory;

	/*
	 * ������С������
	 */
	static void generateMinSession();
	/*
	 * �жϻỰ��Ч��
	 */
	void onJudgeSession(Poco::Timer&);
	/*
	 * ��ʼ��
	 */
	void initialize();

	/*
	 * �����ַ���
	 */
	std::string	 _connectionString;
	/*
	 * ���ݿ����ӳ�
	 */
	Poco::Data::SessionPool* _pool;	
	
	/*
	 * �ж������Ƿ���Ч
	 */
	Poco::Timer _janitorTimer;

	mutable Poco::FastMutex _mutex;

	int	_min;
	int _max;
	int _idleTime;
	//�Ѿ����Դ���
	int _hasAttemptTimes;
	//�Ƿ��Ѿ���ʼ��
	bool _isInitialized;
};


#endif