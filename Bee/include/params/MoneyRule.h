#ifndef MONEYRULE_H_
#define MONEYRULE_H_
#include <string>
#include "Poco/Data/TypeHandler.h"
class MoneyRule
{
	
public:
	MoneyRule();
	MoneyRule(const int& id, const std::string& sourceNo, const std::string& moneyANo,
		const std::string& moneyBNo, const std::string& ruleNo, const std::string& state)
	{
		_id = id;
		_sourceNo = sourceNo;
		_moenyANo = moneyANo;
		_moenyBNo = moneyBNo;
		_ruleNo = ruleNo;
		_state = state;
	}
	~MoneyRule();

	/*bool operator==(const MoneyRule& other) const
	{
		return _id == other._id && _sourceNo == other._sourceNo && _moenyANo == other._moenyANo && _moenyBNo == other._moenyBNo
			&& _ruleNo == other._ruleNo && _state == other._state;
	}*/

	const int& getId()const {return _id;}
	const std::string& getSourceNo()const {return _sourceNo;}
	const std::string& getMoenyANo()const {return _moenyANo;}
	const std::string& getMoenyBNo()const {return _moenyBNo;}
	const std::string& getRuleNo()const {return _ruleNo;}
	const std::string& getState()const {return _state;}

	int& getId() {return _id;}
	std::string& getSourceNo() {return _sourceNo;}
	std::string& getMoenyANo() {return _moenyANo;}
	std::string& getMoenyBNo() {return _moenyBNo;}
	std::string& getRuleNo() {return _ruleNo;}
	std::string& getState() {return _state;}

	void setId(int id) {_id = id;}
	void setSourceNo(std::string& sourceNo) {_sourceNo = sourceNo;}
	void setMoenyANo(std::string& moenyANo) {_moenyANo = moenyANo;}
	void setMoenyBNo(std::string& moenyBNo) {_moenyBNo = moenyBNo;}
	void setRuleNo(std::string& ruleNo) {_ruleNo = ruleNo;}
	void setState(std::string& state) {_state = state;}
//protected:
private:
	int _id;
	std::string _sourceNo;
	std::string _moenyANo;
	std::string _moenyBNo;
	std::string _ruleNo;
	std::string _state;

	
};


namespace Poco {
	namespace Data {

		template <>
		class TypeHandler<MoneyRule>
		{
		public:
			//static void bind(std::size_t pos, const Person& obj, AbstractBinder::Ptr pBinder, AbstractBinder::Direction dir)
			static void bind(std::size_t pos, const MoneyRule& obj, AbstractBinder::Ptr pBinder, AbstractBinder::Direction dir)				
			{
				// the table is defined as MoneyRule (_sourceNo VARCHAR, _moenyANo VARCHAR, _moenyBNo VARCHAR, _ruleNo INTEGER(3))
				poco_assert_dbg (!pBinder.isNull());
				TypeHandler<int>::bind(pos++, obj.getId(), pBinder, dir);
				TypeHandler<std::string>::bind(pos++, obj.getSourceNo(), pBinder, dir);
				TypeHandler<std::string>::bind(pos++, obj.getMoenyANo(), pBinder, dir);
				TypeHandler<std::string>::bind(pos++, obj.getMoenyBNo(), pBinder, dir);
				TypeHandler<std::string>::bind(pos++, obj.getRuleNo(), pBinder, dir);
				TypeHandler<std::string>::bind(pos++, obj.getState(), pBinder, dir);


				
				/*pBinder->bind(pos++, obj.getId(), dir);
				pBinder->bind(pos++, obj.getSourceNo(), dir);
				pBinder->bind(pos++, obj.getMoenyANo(), dir);
				pBinder->bind(pos++, obj.getMoenyBNo(), dir);
				pBinder->bind(pos++, obj.getRuleNo(), dir);
				pBinder->bind(pos++, obj.getState(), dir);*/

				/*pBinder->bind(pos++, obj._id, dir);
				pBinder->bind(pos++, obj._sourceNo, dir);
				pBinder->bind(pos++, obj._moenyANo, dir);
				pBinder->bind(pos++, obj._moenyBNo, dir);
				pBinder->bind(pos++, obj._ruleNo, dir);
				pBinder->bind(pos++, obj._state, dir);*/
				
			}


			static void prepare(std::size_t pos, const MoneyRule& obj, AbstractPreparator::Ptr pPreparator)
			{
				// the table is defined as MoneyRule (_sourceNo VARCHAR, _moenyANo VARCHAR, _moenyBNo VARCHAR, _ruleNo INTEGER(3))
				poco_assert_dbg (!pPreparator.isNull());
				TypeHandler<int>::prepare(pos++, obj.getId(), pPreparator);
				TypeHandler<std::string>::prepare(pos++, obj.getSourceNo(), pPreparator);
				TypeHandler<std::string>::prepare(pos++, obj.getMoenyANo(), pPreparator);
				TypeHandler<std::string>::prepare(pos++, obj.getMoenyBNo(), pPreparator);
				TypeHandler<std::string>::prepare(pos++, obj.getRuleNo(), pPreparator);
				TypeHandler<std::string>::prepare(pos++, obj.getState(), pPreparator);
				

				/*pPreparator->prepare(pos++, obj._id);
				pPreparator->prepare(pos++, obj._sourceNo);
				pPreparator->prepare(pos++, obj._moenyANo);
				pPreparator->prepare(pos++, obj._moenyBNo);
				pPreparator->prepare(pos++, obj._ruleNo);
				pPreparator->prepare(pos++, obj._state);*/
			}

			static std::size_t size()
			{
				return 6;
			}

			static void extract(std::size_t pos, MoneyRule& obj, const MoneyRule& defVal, AbstractExtractor::Ptr pExt)
			{
				poco_assert_dbg (!pExt.isNull());
				int id;
				std::string sourceNo;
				std::string moenyANo;
				std::string moenyBNo;
				std::string ruleNo;	
				std::string state;
				Poco::DateTime dt;

				TypeHandler<int>::extract(pos++, id, defVal.getId(), pExt);
				TypeHandler<std::string>::extract(pos++, sourceNo, defVal.getSourceNo(), pExt);
				TypeHandler<std::string>::extract(pos++, moenyANo, defVal.getMoenyANo(), pExt);
				TypeHandler<std::string>::extract(pos++, moenyBNo, defVal.getMoenyBNo(), pExt);
				TypeHandler<std::string>::extract(pos++, ruleNo, defVal.getRuleNo(), pExt);
				TypeHandler<std::string>::extract(pos++, state, defVal.getState(), pExt);
				
				obj.setId(id);
				obj.setSourceNo(sourceNo);
				obj.setMoenyANo(moenyANo);
				obj.setMoenyBNo(moenyBNo);
				obj.setRuleNo(ruleNo);		
				obj.setState(state);


				

				/*if (!pExt->extract(pos++, obj._id))
					obj._id = defVal._id;
				if (!pExt->extract(pos++, obj._sourceNo))
					obj._sourceNo = defVal._sourceNo;
				if (!pExt->extract(pos++, obj._moenyANo))
					obj._moenyANo = defVal._moenyANo;
				if (!pExt->extract(pos++, obj._moenyBNo))
					obj._moenyBNo = defVal._moenyBNo;
				if (!pExt->extract(pos++, obj._ruleNo))
					obj._ruleNo = defVal._ruleNo;
				if (!pExt->extract(pos++, obj._state))
					obj._state = defVal._state;*/

			}

		private:
			TypeHandler();
			~TypeHandler();
			TypeHandler(const TypeHandler&);
			TypeHandler& operator=(const TypeHandler&);
		};

	} } // namespace Poco::Data



#endif