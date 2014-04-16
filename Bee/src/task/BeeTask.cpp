#include "task/BeeTask.h"
//#include "Util.h"
#include "dbi/RateDb.h"


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
#include "Poco/StringTokenizer.h"
#include <vector>
#include "data/Rate.h"


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

void BeeTask::init()
{
	
}

void BeeTask::getMoneyType()
{

}

void BeeTask::runTask()
{
	std::string hostName = _taskParams.getDataSource().getHostName();
	std::string url = _taskParams.getDataSource().getUrl();
	string response = getUrlResponse(hostName, url);
	/*Application& app = Application::instance();
	while (!sleep(5000))
	{
		Util::getTraceLogger()->information("log");
		Application::instance().logger().information("busy doing nothing... " + DateTimeFormatter::format(app.uptime()));
	}*/

	
	std::vector<MoneyRule> moneyRuleVec = _taskParams.getMoneyRule();
	for (std::vector<MoneyRule>::iterator it = moneyRuleVec.begin(); it != moneyRuleVec.end(); it++)
	{
		FieldPosition fp = _taskParams.getFieldPosition().find(it->getRuleNo())->second;
		extract(response, *it, fp);
	}

	//string response = getUrlResponse("fx.cmbchina.com","/hq/");
	//extract(response, "�۱�"			, "�鿴��ʷ", 0);//��Ԫ
	//extract(response, "�Ĵ�����Ԫ"		, "�鿴��ʷ", 1);//�Ĵ�����Ԫ
	//extract(response, "��Ԫ"			, "�鿴��ʷ", 2);//��Ԫ
	//extract(response, "ŷԪ"			, "�鿴��ʷ", 3);//ŷԪ
	//extract(response, "���ô�Ԫ"		, "�鿴��ʷ", 4);//���ô�Ԫ
	//extract(response, "Ӣ��"			, "�鿴��ʷ", 5);//Ӣ��
	//extract(response, "��Ԫ"			, "�鿴��ʷ", 6);//��Ԫ
	//extract(response, "�¼���Ԫ"		, "�鿴��ʷ", 7);//�¼���Ԫ
	//extract(response, "��ʿ����"		, "�鿴��ʷ", 8);//��ʿ����
}

void BeeTask::extract(const string& html, MoneyRule& moneyRule, FieldPosition& fieldPosition)
{

	std::vector<string> numVec;
	extractNumStr(html, fieldPosition.getFindBegin(), fieldPosition.getFindEnd(), numVec);
	Rate rate;
	rate.setSourceNo(moneyRule.getSourceNo());
	rate.setMoenyANo(moneyRule.getMoenyANo());
	rate.setMoenyBNo(moneyRule.getMoenyBNo());
	rate.setTradeUnit(numVec.at(fieldPosition.getTradeUnit()));
	rate.setMidPrice(numVec.at(fieldPosition.getMidPrice()));
	rate.setSellPrice(numVec.at(fieldPosition.getSellPrice()));
	rate.setCashPrice(numVec.at(fieldPosition.getCashPrice()));
	rate.setSpotPrice(numVec.at(fieldPosition.getSpotPrice()));
	rate.setUpdateDate(numVec.at(fieldPosition.getUpdateDate()));

	RateDb::insertRate(rate);
}

void BeeTask::extractNumStr(const string& html, const string& beginStr, const string& endStr, std::vector<string>& numVec)
{
	int begin , end;

	begin = html.find(beginStr);
	if(begin == string::npos) return;
	end = html.find(endStr, begin);
	if(end == string::npos || begin > end) return;

	string destStr = html.substr(begin, end - begin);

	std::vector<string> tds;
	extractNum(destStr, numVec);

	
}


string BeeTask::getUrlResponse(const string& hostName, const string& url)
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
		string str(ostr.str());
		responseStr = Util::UTF8ToUnicode(str);
	}
	catch(Poco::Net::NetException& ex)
	{
		std::cout << ex.message() << std::endl;
	}
	return responseStr;
}

void BeeTask::extractNum(const string& str, std::vector<string>& subs)
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


void BeeTask::extract(const string& s1, const string& beginStr, const string& endStr)
{
	int begin , end;

	begin = s1.find(beginStr);
	if(begin == string::npos) return;
	end = s1.find(endStr, begin);
	if(end == string::npos || begin > end) return;

	string destStr = s1.substr(begin, end - begin);

	std::vector<string> tds;
	extractNum(destStr, tds);

	for (std::map<string, int>::iterator it = _filedmap.begin(); it != _filedmap.end(); it++)
	{
		_filedData.insert(make_pair(it->first, tds.at(it->second)));
	}


}


void BeeTask::setRule(const string& rule)
{
	std::vector<string> vec;
	stringToVec(rule, vec);
	
	for (std::vector<string>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		int beginPostion = it->find("(");
		int endPostion = it->find(")");
		string field = Poco::toUpper(Poco::trim(it->substr(0, beginPostion)));
		int len = Poco::NumberParser::parse(Poco::trim(it->substr(beginPostion+1, endPostion - beginPostion-1))) ;		
		_filedmap.insert(std::make_pair(field, len));
		//fieldsVec.push_back(field);		
	}

	_rule = rule;
}

void BeeTask::stringToVec(const string& instr, std::vector<std::string>& vec)
{
	Poco::StringTokenizer tokenizer(instr, ",", Poco::StringTokenizer::TOK_TRIM);
	for (Poco::StringTokenizer::Iterator it = tokenizer.begin(); it != tokenizer.end(); ++it)
	{	
		// ת���ɴ�д
		vec.push_back( Poco::toUpper(Poco::trim(*it)) );
	}
}