#include "params/FieldPosition.h"


FieldPosition::FieldPosition()
{

}

FieldPosition::FieldPosition(string& ruleNo, int& tradeUnit,
			  int& midPrice, int& sellPrice, int& cashPrice, 
			  int& spotPrice, string& findBegin, string& findEnd, int& updateDate)
{
	_ruleNo = ruleNo;
	_tradeUnit = tradeUnit;
	_midPrice = midPrice;
	_sellPrice =sellPrice;
	_cashPrice = cashPrice;
	_spotPrice = spotPrice;
	_findBegin = findBegin;
	_findEnd = findEnd;
	_updateDate = updateDate;  

}