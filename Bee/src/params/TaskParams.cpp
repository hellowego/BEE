#include "params/TaskParams.h"

TaskParams::TaskParams(DataSource& dataSource, std::map<std::string, FieldPosition>& filedPositionMap, std::vector<MoneyRule>& moneyRuleVec)
{
	_dataSource = dataSource;
	_filedPositionMap = filedPositionMap;
	_moneyRuleVec = moneyRuleVec;

}

TaskParams::~TaskParams()
{

}

TaskParams::TaskParams()
{

}