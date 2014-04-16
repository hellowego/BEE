#ifndef BEETASK_H_
#define BEETASK_H_

#include "Poco/Task.h"
#include "Poco/Util/Application.h"
#include "Poco/DateTimeFormatter.h"
#include <vector>
#include <string>
#include "params/TaskParams.h"
using std::string;
using Poco::Task;
using Poco::Util::Application;
using Poco::DateTimeFormatter;

class BeeTask: public Task
{
public:
	BeeTask(TaskParams& taskParams): Task("BeeTask")
	{
		_taskParams = taskParams;
	}

	~BeeTask(){}

	void runTask();

	string getUrlResponse(const string& hostName, const string& url);

	void extractNum(const string& str, std::vector<string>& subs);

	void extractNumStr(const string& html, const string& beginStr, const string& endStr, std::vector<string>& numVec);

	void extract(const string& s1, const string& beginStr, const string& endStr);

	void extract(const string& html, MoneyRule& moneyRule, FieldPosition& fieldPosition);
	
	void setRule(const string& rule);

	void init();

	void getMoneyType();

	void stringToVec(const string& instr, std::vector<std::string>& vec);



private:
	string _rule;

	std::map<string, int> _filedmap;
	std::map<string, string> _filedData;

	TaskParams _taskParams;
};

#endif
