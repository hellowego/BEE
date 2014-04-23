#include "dbi/RateDb.h"
#include "Util.h"
#include <vector>
using namespace Poco::Data::Keywords;

void RateDb::insertRate(Rate& rate)
{

	Rate rateInDb;
	bool rateExit = getRate(rate.getSourceNo(), rate.getMoenyANo(), rate.getMoenyBNo(), rateInDb);
	if (rateExit)
	{
		if (rateInDb.getUpdateDate() != rate.getUpdateDate())
		{
			insertHistoryRate(rateInDb);
			updateRate(rate.getSourceNo(), rate.getMoenyANo(), rate.getMoenyBNo(), rate);
		}
	}
	else
	{		
		insertRate(rate, true);
	}

}

void RateDb::insertRate(Rate& rate, bool bl)
{

	Poco::Data::Session session(Util::getSession());

	session<<"INSERT INTO td_rate VALUES(?,?,?,?,?,?,?,?,?) ", use(rate), now;
	
}

void RateDb::insertHistoryRate(Rate& rate)
{

	Poco::DateTime dt;
	//Poco::LocalDateTime
	Poco::Data::Session session(Util::getSession());
	session<<"INSERT INTO td_historyrate ( "
		" sourceNo, moneyANo, moneyBNo, tradeUnit,"
		" midPrice, sellPrice, cashPrice, spotPrice,"
		" updateTime, inlisttime "
		" ) VALUES(?,?,?,?,?,?,?,?,?,now()) ", use(rate), now;
}

void RateDb::updateRate(std::string& sourceNo, std::string& moneyANo, std::string& moneyBNo, Rate& rate)
{

	std::string ss,s1,s2,s3;
	
	Poco::Data::Session session(Util::getSession());
	session<<	"UPDATE td_rate "
				"SET updateTime = ? "
		"WHERE sourceNo = ? AND moneyANo = ? AND moneyBNo = ?" ,use(rate.getUpdateDate()),
		use(sourceNo), use(moneyANo), use(moneyBNo), now;
}


bool RateDb::getRate(std::string& sourceNo, std::string& moneyANo, std::string& moneyBNo, Rate& rate)
{
	
	std::vector<Rate> rateVec;

	Poco::Data::Session session(Util::getSession());
	session<<	"SELECT * FROM td_rate WHERE sourceNo = ? AND moneyANo = ? AND moneyBNo = ?" ,into(rateVec),
		use(sourceNo), use(moneyANo), use(moneyBNo), now;
	
	bool bl(false);
	if (rateVec.size()==1)
	{
		bl = true;
		rate = rateVec.at(0);
	}

	return bl;
}