#ifndef RATEDB_H_
#define RATEDB_H_


#include "data/Rate.h"
#include "data/HistoryRate.h"
class RateDb
{
public:
	static void insertRate(Rate& rate);
	static void insertRate(Rate& rate, bool bl);
	static void insertHistoryRate(Rate& rate);
	static void updateRate(std::string& sourceNo, std::string& moneyANo, std::string& moneyBNo, Rate& rate);
	static bool getRate(std::string& sourceNo, std::string& moneyANo, std::string& moneyBNo, Rate& rate);
protected:
private:
};

#endif