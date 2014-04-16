#include "WorkerServer.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/NetException.h"
#include "Poco/StreamCopier.h"

#include "Poco/Data/MySQL/MySQL.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/MySQL/Connector.h"
//#include "Poco/Data/BLOB.h"
#include "Poco/Data/StatementImpl.h"
#include "Poco/Data/RecordSet.h"
#include "Poco/Data/MySQL/Connector.h"
#include "Poco/Data/MySQL/MySQLException.h"
#include "dbi/MysqlSessionFactory.h"
#include "Util.h"
#include "Poco/RegularExpression.h"
#include <vector>
#include "dbi/ParamsFromDb.h"
#include "params/DataSource.h"
#include "params/FieldPosition.h"
#include "params/TaskParams.h"

using namespace Poco::Data;
using Poco::Data::MySQL::ConnectionException;
using Poco::Data::MySQL::StatementException;
using Poco::Data::MySQL::MySQLException;

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::StreamCopier;
using Poco::RegularExpression;

WorkerServer::WorkerServer()
{

}

WorkerServer::~WorkerServer()
{

}

void WorkerServer::initialize(Application& self)
{

	BeeServer::initialize(self);
	// ��ʼ�����ݿ�����������Ϣ
	DBConnectInfoInitializer().initDBConnectInfo(_dbInfo);
	string dbConnString = _dbInfo.getConnString();

	//MySQL::Connector::registerConnector();
	//��ʼ�����ݿ�����
	//_pSessionPool = new Poco::Data::SessionPool(Poco::Data::MySQL::Connector::KEY, _dbInfo.getConnString());

	MysqlSessionFactory::instance().create(_dbInfo.getDBName(), _dbInfo.getUserName(), _dbInfo.getPassword(), 2, 5);
	//

	//_pSession = &_pSessionPool->get();

	//get data source
	std::vector<DataSource> dataSouceVec;
	ParamsFromDb::dataSource(dataSouceVec);

	// set field position rule
	std::vector<FieldPosition> fpvec;
	ParamsFromDb::filedPosition(fpvec);

	std::map<string, FieldPosition> fpMap;
	for (std::vector<FieldPosition>::iterator it = fpvec.begin(); it != fpvec.end(); it++)
	{
		fpMap.insert(std::make_pair(it->getRuleNo(), *it));
	}

	// create task
	for (std::vector<DataSource>::iterator it = dataSouceVec.begin();
		it != dataSouceVec.end(); it++)
	{
		// get money type from source 
		std::vector<MoneyRule> moneyRule;
		ParamsFromDb::moneyRule(moneyRule, it->getSourceNo());
		TaskParams taskParams(*it, fpMap, moneyRule);
		//BeeTask beeTask(taskParams);
		_taskVec.push_back(new BeeTask(taskParams));
	}
}

void WorkerServer::task()
{
	for (std::vector<BeeTask*>::iterator it = _taskVec.begin(); it!=_taskVec.end(); it++)
	{
		_tm.start(*it);
	}
	//while(1)
	//{
	//	try
	//	{
	//		string response = getUrlResponse("fx.cmbchina.com","/hq/");
	//		extractCmb(response, "�۱�"			, "�鿴��ʷ", 0);//��Ԫ
	//		extractCmb(response, "�Ĵ�����Ԫ"	, "�鿴��ʷ", 1);//�Ĵ�����Ԫ
	//		extractCmb(response, "��Ԫ"			, "�鿴��ʷ", 2);//��Ԫ
	//		extractCmb(response, "ŷԪ"			, "�鿴��ʷ", 3);//ŷԪ
	//		extractCmb(response, "���ô�Ԫ"		, "�鿴��ʷ", 4);//���ô�Ԫ
	//		extractCmb(response, "Ӣ��"			, "�鿴��ʷ", 5);//Ӣ��
	//		extractCmb(response, "��Ԫ"			, "�鿴��ʷ", 6);//��Ԫ
	//		extractCmb(response, "�¼���Ԫ"		, "�鿴��ʷ", 7);//�¼���Ԫ
	//		extractCmb(response, "��ʿ����"		, "�鿴��ʷ", 8);//��ʿ����
	//	}
	//	catch (Poco::Exception* e)
	//	{
	//		std::cout<<e->what()<<std::endl;
	//		
	//	}
	//	catch (std::exception& e)
	//	{
	//		std::cout<<e.what()<<std::endl;
	//	}

	//	Sleep(60*1000);
	//}

		
}

string WorkerServer::getUrlResponse(const string& hostName, const string& url)
{
	string responseStr("");
	try
	{
		HTTPClientSession s(hostName);
		HTTPRequest request(HTTPRequest::HTTP_GET, url);
		s.sendRequest(request);
		HTTPResponse response;
		std::istream& rs = s.receiveResponse(response);

		std::ostringstream ostr;
		StreamCopier::copyStream(rs, ostr);
		//std::cout<<ostr.str()<<std::endl;
		string str(ostr.str());
		responseStr = Util::UTF8ToUnicode(str);
	}
	catch(Poco::Net::NetException& ex)
	{
		std::cout << ex.message() << std::endl;
	}
	return responseStr;
}

void WorkerServer::extractCmb(const string& s1, const string& beginStr, const string& endStr, const int& type)
{
	int begin , end;

	begin = s1.find(beginStr);
	if(begin == string::npos) return;
	end = s1.find(endStr, begin);
	if(end == string::npos || begin > end) return;

	string destStr = s1.substr(begin, end - begin);

	std::vector<string> tds;
	extract(destStr, tds);

	string date = Poco::DateTimeFormatter::format(Poco::LocalDateTime(), "%Y-%m-%d");
	
	if(tds.size() >= 6)
	{
		tds[5] = date + " " + tds[5];
		try
		{
			Session session(Util::getSession());

			float current;

			/*session << " SELECT Current FROM TF_F_EXCHANGE A WHERE ExchangeType = ? "
					   " AND CreateDate = (SELECT MAX(CreateDate)                   " 
					   "                   FROM TF_F_EXCHANGE B                     "
					   "                   WHERE B.ExchangeType = A.ExchangeType)   "
					, into(current), use(type), now;*/

			if(Poco::NumberFormatter::format(current, 4) 
				== Poco::NumberFormatter::format(Poco::NumberParser::parseFloat(tds[2]), 4))
				return;

			/*session	<< "INSERT INTO TF_F_EXCHANGE (ExchangeType, Middle, Current, Spot, Cash, CreateDate) " 
					<< "VALUES (?, ?, ?, ?, ?, ?)"
					, use(type), use(tds[1]), use(tds[2]), use(tds[3]), use(tds[4]), use(tds[5]), now;
			session.commit();*/
		}
		catch(ConnectionException& ce)
		{ 
			std::cout << ce.displayText() << std::endl; 
		}
		catch(StatementException& se)
		{ 
			std::cout << se.displayText() << std::endl; 
		}
	}
}

void WorkerServer::extract(const string& str, std::vector<string>& subs)
{
	for(string::const_iterator it = str.begin(); it != str.end(); it ++)
	{
		string tmp("");
		while(Poco::Ascii::isDigit(*it) || *it == '.' || *it == ':')
		{
			tmp.push_back(*it);
			it ++;
		}
		if(!tmp.empty())
			subs.push_back(tmp);
	}
}



void WorkerServer::uninitialize()
{
	//MysqlSessionFactory::instance().close();
	BeeServer::uninitialize();
}

POCO_SERVER_MAIN(WorkerServer)