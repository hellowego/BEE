#ifndef FIELDPOSITION_H_
#define FIELDPOSITION_H_
#include <string>
#include "Poco/Data/TypeHandler.h"
using std::string;
class FieldPosition
{
public:
	FieldPosition();
	FieldPosition(string& ruleNo, int& tradeUnit,
		int& midPrice, int& sellPrice, int& cashPrice, 
		int& spotPrice, string& findBegin, string& findEnd, int& updateDate);

	bool operator==(const FieldPosition& other) const
	{
		return _ruleNo == other._ruleNo && _tradeUnit == other._tradeUnit && 
			_midPrice == other._midPrice && _sellPrice == other._sellPrice &&
			_cashPrice == other._cashPrice && _spotPrice == other._spotPrice &&
			_findBegin == other._findBegin && _findEnd == other._findEnd &&
			_updateDate == other._updateDate ;
			
	}

	std::string getRuleNo() const {return _ruleNo;}
	int getTradeUnit() const {return _tradeUnit;}
	int getMidPrice() const {return _midPrice;}
	int getSellPrice() const {return _sellPrice;}
	int getCashPrice() const {return _cashPrice;}
	int getSpotPrice() const {return _spotPrice;}
	std::string getFindBegin() const {return _findBegin;}
	std::string getFindEnd() const {return _findEnd;}
	int getUpdateDate() const {return _updateDate;}

	void setRuleNo(std::string& ruleNo)		{_ruleNo = ruleNo;}
	void setTradeUnit(int& tradeUnit)		{_tradeUnit = tradeUnit;}
	void setMidPrice(int& midPrice)			{_midPrice = midPrice;}
	void setSellPrice(int& sellPrice)		{_sellPrice = sellPrice;}
	void setCashPrice(int& cashPrice)		{_cashPrice = cashPrice;}
	void setSpotPrice(int& spotPrice)		{_spotPrice = spotPrice;}
	void setFindBegin(std::string& findBegin){_findBegin = findBegin;}
	void setFindEnd(std::string& findEnd)	{_findEnd = findEnd;}
	void setUpdateDate(int& updateDate)		{_updateDate = updateDate;}

	std::string _ruleNo;
	int _tradeUnit;
	int _midPrice;
	int _sellPrice;
	int _cashPrice;
	int _spotPrice;
	std::string _findBegin;
	std::string _findEnd;
	int _updateDate;
protected:
private:
	
};



namespace Poco {
	namespace Data {

		template <>
		class TypeHandler<FieldPosition>
		{
		public:
			static void bind(std::size_t pos, const FieldPosition& obj, AbstractBinder::Ptr pBinder, AbstractBinder::Direction dir)				
			{
				// the table is defined as FieldPosition (_sourceNo VARCHAR(30), _sourceName VARCHAR, _hostName VARCHAR, _url INTEGER(3))
				poco_assert_dbg (!pBinder.isNull());
				TypeHandler<std::string>::bind(pos++, obj.getRuleNo(), pBinder, dir);
				TypeHandler<int>::bind(pos++, obj.getTradeUnit(), pBinder, dir);
				TypeHandler<int>::bind(pos++, obj.getMidPrice(), pBinder, dir);
				TypeHandler<int>::bind(pos++, obj.getSellPrice(), pBinder, dir);
				TypeHandler<int>::bind(pos++, obj.getCashPrice(), pBinder, dir);
				TypeHandler<int>::bind(pos++, obj.getSpotPrice(), pBinder, dir);
				TypeHandler<std::string>::bind(pos++, obj.getFindBegin(), pBinder, dir);
				TypeHandler<std::string>::bind(pos++, obj.getFindEnd(), pBinder, dir);
				TypeHandler<int>::bind(pos++, obj.getUpdateDate(), pBinder, dir);
				//TypeHandler<Poco::DateTime>::bind(pos++, obj.getDt(), pBinder, dir);
			}

			static void prepare(std::size_t pos, const FieldPosition& obj, AbstractPreparator::Ptr pPreparator)
			{
				// the table is defined as FieldPosition (_sourceNo VARCHAR(30), _sourceName VARCHAR, _hostName VARCHAR, _url INTEGER(3))
				poco_assert_dbg (!pPreparator.isNull());
				TypeHandler<std::string>::prepare(pos++, obj.getRuleNo(), pPreparator);
				TypeHandler<int>::prepare(pos++, obj.getTradeUnit(), pPreparator);
				TypeHandler<int>::prepare(pos++, obj.getMidPrice(), pPreparator);
				TypeHandler<int>::prepare(pos++, obj.getSellPrice(), pPreparator);
				TypeHandler<int>::prepare(pos++, obj.getCashPrice(), pPreparator);
				TypeHandler<int>::prepare(pos++, obj.getSpotPrice(), pPreparator);
				TypeHandler<std::string>::prepare(pos++, obj.getFindBegin(), pPreparator);
				TypeHandler<std::string>::prepare(pos++, obj.getFindEnd(), pPreparator);
				TypeHandler<int>::prepare(pos++, obj.getUpdateDate(), pPreparator);
				//TypeHandler<Poco::DateTime>::prepare(pos++, obj.getDt(), pPreparator);

			}

			static std::size_t size()
			{
				return 9;
			}

			static void extract(std::size_t pos, FieldPosition& obj, const FieldPosition& defVal, AbstractExtractor::Ptr pExt)
				//static void extract(std::size_t pos, FieldPosition& obj, const FieldPosition& defVal, AbstractExtractor* pExt)
			{
				poco_assert_dbg (!pExt.isNull());

				std::string ruleNo;
				int tradeUnit;
				int midPrice;
				int sellPrice;
				int cashPrice;
				int spotPrice;
				std::string findBegin;
				std::string findEnd;
				int updateDate;

				TypeHandler<std::string>::extract(pos++, ruleNo, defVal.getRuleNo(), pExt);
				TypeHandler<int>::extract(pos++, tradeUnit, defVal.getTradeUnit(), pExt);
				TypeHandler<int>::extract(pos++, midPrice, defVal.getMidPrice(), pExt);
				TypeHandler<int>::extract(pos++, sellPrice, defVal.getSellPrice(), pExt);
				TypeHandler<int>::extract(pos++, cashPrice, defVal.getCashPrice(), pExt);
				TypeHandler<int>::extract(pos++, spotPrice, defVal.getSpotPrice(), pExt);
				TypeHandler<std::string>::extract(pos++, findBegin, defVal.getFindBegin(), pExt);
				TypeHandler<std::string>::extract(pos++, findEnd, defVal.getFindEnd(), pExt);
				TypeHandler<int>::extract(pos++, updateDate, defVal.getUpdateDate(), pExt);

				//TypeHandler<Poco::DateTime>::extract(pos++, dt, defVal.getDt(), pExt);
				obj.setRuleNo(ruleNo);
				obj.setTradeUnit(tradeUnit);
				obj.setMidPrice(midPrice);
				obj.setSellPrice(sellPrice);
				obj.setCashPrice(cashPrice);
				obj.setSpotPrice(spotPrice);
				obj.setFindBegin(findBegin);
				obj.setFindEnd(findEnd);
				obj.setUpdateDate(updateDate);
				

			}

		private:
			TypeHandler();
			~TypeHandler();
			TypeHandler(const TypeHandler&);
			TypeHandler& operator=(const TypeHandler&);
		};

	} // namespace Poco
} // namespace Poco::Data



#endif