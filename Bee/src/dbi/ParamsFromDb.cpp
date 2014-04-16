#include "dbi/ParamsFromDb.h"
#include "Util.h"
#include "data/Person.h"

using namespace Poco::Data::Keywords;

void ParamsFromDb::dataSource(std::vector<DataSource>& dataSouceVec)
{
	Poco::Data::Session session(Util::getSession());

	Person p1("LN1", "FN1", "ADDR1", 1);
	Person p2("LN2", "FN2", "ADDR2", 2);

	session << "INSERT INTO Person VALUES (?,?,?,?)", use(p1), now; 

	
	
	std::string state="1";

	std::vector<DataSource> vec;

	Poco::DateTime dt;
	std::string dt1;
	MoneyRule moneyRule;
	session<<	"SELECT * FROM tp_moneyRule  " ,into(moneyRule), now;

	//MoneyRule moneyRule1(11, "ss", "aa", "da", "sss", "1");
	//moneyRule.setId(moneyRule.getId() + 1);
	//session<< "INSERT INTO tp_moneyRule VALUES(?,?,?,?,?,?) ", use(moneyRule), now;


	/*session<<	"SELECT sourceNo, sourceName, hostName, url "
				"FROM tp_datasource "
				"WHERE state= ?",
				into(sourceNo), into(sourceName), into(hostName), into(url),
				use(state), now;*/

	//session<<	"SELECT createDate FROM tp_datasource WHERE state= ? " ,into(dt),use(state), now;
	try
	{
		session<<	"SELECT * FROM tp_datasource WHERE state= ? " ,into(dataSouceVec),use(state), now;
	}
	catch (std::exception& e)
	{
		std::cout<<e.what()<<std::endl;
		
	}
	
	

	//session<<	"SELECT createdate FROM testDate  " ,into(dt), now;

	//DataSource ds(sourceNo, sourceName, hostName, url);
	//dataSouce = ds;

}

void ParamsFromDb::filedPosition(std::vector<FieldPosition>& fieldPositionVec)
{

	Poco::Data::Session session(Util::getSession());
	string dd;

	Poco::LocalDateTime dt;
	//std::vector<FieldPosition> fieldPositionVec;
	session<<	"SELECT * FROM tp_fieldposition  ", into(fieldPositionVec), now;

	for (std::vector<FieldPosition>::iterator it = fieldPositionVec.begin(); it != fieldPositionVec.end(); it++)
	{
		it->setFindBegin(Util::UTF8ToUnicode(it->getFindBegin()));
		it->setFindEnd(Util::UTF8ToUnicode(it->getFindEnd()));
	}
	string st1=fieldPositionVec.at(0).getFindEnd();
	string str=Util::UTF8ToUnicode(st1);
	//session<<	"SELECT * FROM tp_fieldposition  ", into(fieldPositionVec), now;
	
}

void ParamsFromDb::moneyRule(std::vector<MoneyRule>& moneyRule, std::string& sourceNo)
{

	Poco::Data::Session session(Util::getSession());
	std::string state="1";
	session<<	"SELECT * FROM tp_moneyRule WHERE state= ? and sourceNo = ? " ,
		into(moneyRule), use(state), use(sourceNo), now;
}

void ParamsFromDb::test()
{

	/*Poco::Data::Session session(Util::getSession());
	Person p1;
	std::vector<Person> result;*/
	//session << "SELECT * FROM Person", into(p1), now; 

}