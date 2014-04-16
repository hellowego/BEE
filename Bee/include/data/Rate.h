#ifndef RATE_H_
#define RATE_H_
#include "Poco/Data/TypeHandler.h"
#include "Poco/DateTime.h"

class Rate
{
public:
	Rate(){}
	~Rate(){}
	const std::string& getSourceNo()const {return _sourceNo;}
	const std::string& getMoenyANo()const {return _moenyANo;}
	const std::string& getMoenyBNo()const {return _moenyBNo;}
	const std::string& getTradeUnit()const {return _tradeUnit;}
	const std::string& getMidPrice() const {return _midPrice;}
	const std::string& getSellPrice() const {return _sellPrice;}
	const std::string& getCashPrice() const {return _cashPrice;}
	const std::string& getSpotPrice() const {return _spotPrice;}
	const std::string& getUpdateDate() const {return _updateDate;}


	std::string& getSourceNo() {return _sourceNo;}
	std::string& getMoenyANo() {return _moenyANo;}
	std::string& getMoenyBNo() {return _moenyBNo;}
	std::string& getTradeUnit() {return _tradeUnit;}
	std::string& getMidPrice()  {return _midPrice;}
	std::string& getSellPrice()  {return _sellPrice;}
	std::string& getCashPrice()  {return _cashPrice;}
	std::string& getSpotPrice()  {return _spotPrice;}
	std::string& getUpdateDate()  {return _updateDate;}


	void setSourceNo(std::string& sourceNo) {_sourceNo = sourceNo;}
	void setMoenyANo(std::string& moenyANo) {_moenyANo = moenyANo;}
	void setMoenyBNo(std::string& moenyBNo) {_moenyBNo = moenyBNo;}
	void setTradeUnit(std::string& tradeUnit) {_tradeUnit = tradeUnit;}
	void setMidPrice(std::string& midPrice)			{_midPrice = midPrice;}
	void setSellPrice(std::string& sellPrice)		{_sellPrice = sellPrice;}
	void setCashPrice(std::string& cashPrice)		{_cashPrice = cashPrice;}
	void setSpotPrice(std::string& spotPrice)		{_spotPrice = spotPrice;}
	void setUpdateDate(std::string& updateDate)		{_updateDate = updateDate;}

	
protected:
private:

	std::string _sourceNo;
	std::string _moenyANo;
	std::string _moenyBNo;
	std::string _tradeUnit;
	std::string _midPrice;
	std::string _sellPrice;
	std::string _cashPrice;
	std::string _spotPrice;
	std::string _updateDate;
};



namespace Poco {
	namespace Data {

		template <>
		class TypeHandler<Rate>
		{
		public:
			static void bind(std::size_t pos, const Rate& obj, AbstractBinder::Ptr pBinder, AbstractBinder::Direction dir)				
			{
				// the table is defined as Rate (_sourceNo VARCHAR, _moenyANo VARCHAR, _moenyBNo VARCHAR, _ruleNo std::stringEGER(3))
				poco_assert_dbg (!pBinder.isNull());
				TypeHandler<std::string>::bind(pos++, obj.getSourceNo(), pBinder, dir);
				TypeHandler<std::string>::bind(pos++, obj.getMoenyANo(), pBinder, dir);
				TypeHandler<std::string>::bind(pos++, obj.getMoenyBNo(), pBinder, dir);
				TypeHandler<std::string>::bind(pos++, obj.getTradeUnit(), pBinder, dir);
				TypeHandler<std::string>::bind(pos++, obj.getMidPrice(), pBinder, dir);
				TypeHandler<std::string>::bind(pos++, obj.getSellPrice(), pBinder, dir);
				TypeHandler<std::string>::bind(pos++, obj.getCashPrice(), pBinder, dir);
				TypeHandler<std::string>::bind(pos++, obj.getSpotPrice(), pBinder, dir);
				TypeHandler<std::string>::bind(pos++, obj.getUpdateDate(), pBinder, dir);

			}


			static void prepare(std::size_t pos, const Rate& obj, AbstractPreparator::Ptr pPreparator)
			{
				// the table is defined as Rate (_sourceNo VARCHAR, _moenyANo VARCHAR, _moenyBNo VARCHAR, _ruleNo std::stringEGER(3))
				poco_assert_dbg (!pPreparator.isNull());				
				TypeHandler<std::string>::prepare(pos++, obj.getSourceNo(), pPreparator);
				TypeHandler<std::string>::prepare(pos++, obj.getMoenyANo(), pPreparator);
				TypeHandler<std::string>::prepare(pos++, obj.getMoenyBNo(), pPreparator);
				TypeHandler<std::string>::prepare(pos++, obj.getTradeUnit(), pPreparator);
				TypeHandler<std::string>::prepare(pos++, obj.getMidPrice(), pPreparator);
				TypeHandler<std::string>::prepare(pos++, obj.getSellPrice(), pPreparator);
				TypeHandler<std::string>::prepare(pos++, obj.getCashPrice(), pPreparator);
				TypeHandler<std::string>::prepare(pos++, obj.getSpotPrice(), pPreparator);
				TypeHandler<std::string>::prepare(pos++, obj.getUpdateDate(), pPreparator);
				

			}

			static std::size_t size()
			{
				return 9;
			}

			static void extract(std::size_t pos, Rate& obj, const Rate& defVal, AbstractExtractor::Ptr pExt)
			{
				poco_assert_dbg (!pExt.isNull());
				
				std::string sourceNo;
				std::string moenyANo;
				std::string moenyBNo;
				std::string tradeUnit;
				std::string midPrice;
				std::string sellPrice;
				std::string cashPrice;
				std::string spotPrice;				
				std::string updateDate;

				
				TypeHandler<std::string>::extract(pos++, sourceNo, defVal.getSourceNo(), pExt);
				TypeHandler<std::string>::extract(pos++, moenyANo, defVal.getMoenyANo(), pExt);
				TypeHandler<std::string>::extract(pos++, moenyBNo, defVal.getMoenyBNo(), pExt);
				TypeHandler<std::string>::extract(pos++, tradeUnit, defVal.getTradeUnit(), pExt);
				TypeHandler<std::string>::extract(pos++, midPrice, defVal.getMidPrice(), pExt);
				TypeHandler<std::string>::extract(pos++, sellPrice, defVal.getSellPrice(), pExt);
				TypeHandler<std::string>::extract(pos++, cashPrice, defVal.getCashPrice(), pExt);
				TypeHandler<std::string>::extract(pos++, spotPrice, defVal.getSpotPrice(), pExt);				
				TypeHandler<std::string>::extract(pos++, updateDate, defVal.getUpdateDate(), pExt);

				
				obj.setSourceNo(sourceNo);
				obj.setMoenyANo(moenyANo);
				obj.setMoenyBNo(moenyBNo);
				obj.setTradeUnit(tradeUnit);
				obj.setMidPrice(midPrice);
				obj.setSellPrice(sellPrice);
				obj.setCashPrice(cashPrice);
				obj.setSpotPrice(spotPrice);				
				obj.setUpdateDate(updateDate);
				

			}

		private:
			TypeHandler();
			~TypeHandler();
			TypeHandler(const TypeHandler&);
			TypeHandler& operator=(const TypeHandler&);
		};

	} } // namespace Poco::Data


#endif