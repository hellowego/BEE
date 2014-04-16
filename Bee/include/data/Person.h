#ifndef PERSON_H_
#define PERSON_H_
#include <string>
#include "Poco/Data/TypeHandler.h"
struct Person
{
	std::string lastName;
	std::string firstName;
	std::string address;
	int age;
	Person(){age = 0;}
	Person(const std::string& ln, const std::string& fn, const std::string& adr, int a):lastName(ln), firstName(fn), address(adr), age(a)
	{
	}
	/*bool operator==(const Person& other) const
	{
		return lastName == other.lastName && firstName == other.firstName && address == other.address && age == other.age;
	}*/

	//bool operator < (const Person& p) const
	//{
	//	if (age < p.age)
	//		return true;
	//	if (lastName < p.lastName)
	//		return true;
	//	if (firstName < p.firstName)
	//		return true;
	//	return (address < p.address);
	//}

	//const std::string& operator () () const
	//	/// This method is required so we can extract data to a map!
	//{
	//	// we choose the lastName as examplary key
	//	return lastName;
	//}
};


namespace Poco {
	namespace Data {


		template <>
		class TypeHandler<Person>
		{
		public:
			static void bind(std::size_t pos, const Person& obj, AbstractBinder::Ptr pBinder, AbstractBinder::Direction dir)
			{
				// the table is defined as Person (LastName VARCHAR(30), FirstName VARCHAR, Address VARCHAR, Age INTEGER(3))
				poco_assert_dbg (!pBinder.isNull());
				pBinder->bind(pos++, obj.lastName, dir);
				pBinder->bind(pos++, obj.firstName, dir);
				pBinder->bind(pos++, obj.address, dir);
				pBinder->bind(pos++, obj.age, dir);
			}

			static void prepare(std::size_t pos, const Person& obj, AbstractPreparator::Ptr pPrepare)
			{
				// the table is defined as Person (LastName VARCHAR(30), FirstName VARCHAR, Address VARCHAR, Age INTEGER(3))
				poco_assert_dbg (!pPrepare.isNull());
				pPrepare->prepare(pos++, obj.lastName);
				pPrepare->prepare(pos++, obj.firstName);
				pPrepare->prepare(pos++, obj.address);
				pPrepare->prepare(pos++, obj.age);
			}

			static std::size_t size()
			{
				return 4;
			}

			static void extract(std::size_t pos, Person& obj, const Person& defVal, AbstractExtractor::Ptr pExt)
			{
				poco_assert_dbg (!pExt.isNull());
				if (!pExt->extract(pos++, obj.lastName))
					obj.lastName = defVal.lastName;
				if (!pExt->extract(pos++, obj.firstName))
					obj.firstName = defVal.firstName;
				if (!pExt->extract(pos++, obj.address))
					obj.address = defVal.address;
				if (!pExt->extract(pos++, obj.age))
					obj.age = defVal.age;
			}

		private:
			TypeHandler();
			~TypeHandler();
			TypeHandler(const TypeHandler&);
			TypeHandler& operator=(const TypeHandler&);
		};


	} } // namespace Poco::Data

#endif