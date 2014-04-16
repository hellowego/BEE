#ifndef PARAMSFROMDB_H_
#define PARAMSFROMDB_H_

#include "params/DataSource.h"
#include "params/FieldPosition.h"
#include "params/MoneyRule.h"
class ParamsFromDb
{
public:
	static void dataSource(std::vector<DataSource>& dataSouceVec);

	static void filedPosition(std::vector<FieldPosition>& fieldPositionVec);

	static void moneyRule(std::vector<MoneyRule>& moneyRule, std::string& sourceNo);

	static void test();
protected:
private:
};



#endif