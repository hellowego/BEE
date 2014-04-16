#ifndef TASKPARAMS_H_
#define TASKPARAMS_H_
#include "params/DataSource.h"
#include "params/FieldPosition.h"
#include "params/MoneyRule.h"
#include <map>
class TaskParams
{
public:
	TaskParams();
	TaskParams(DataSource& dataSource, std::map<std::string, FieldPosition>& filedPositionMap, std::vector<MoneyRule>& moneyRuleVec);
	~TaskParams();

	DataSource getDataSource(){ return _dataSource;}
	std::map<std::string, FieldPosition> getFieldPosition() {return _filedPositionMap;}
	std::vector<MoneyRule> getMoneyRule() {return _moneyRuleVec;}


protected:
private:
	DataSource _dataSource;
	std::map<std::string, FieldPosition> _filedPositionMap;
	std::vector<MoneyRule> _moneyRuleVec;
};
#endif