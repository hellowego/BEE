#include "dbi/ParamsFromDb.h"
#include "Util.h"
#include "data/Person.h"

using namespace Poco::Data::Keywords;

void ParamsFromDb::dataSource(std::vector<DataSource>& dataSouceVec)
{
	Poco::Data::Session session(Util::getSession());
	std::string state="1";
	std::vector<DataSource> vec;
	
	try
	{
		session<<	"SELECT * FROM tp_datasource WHERE state= ? " ,into(dataSouceVec),use(state), now;
	}
	catch (std::exception& e)
	{
		std::cout<<e.what()<<std::endl;
		
	}
	
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