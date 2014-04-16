#if !defined(CONTEXT_HEADER)
#define  CONTEXT_HEADER

#include <map>
#include <string>
#include <list>
#include "Poco/Any.h"
#include "Poco/Exception.h"
#include "tool/RefWrapper.h"

// Usage Samples:
// 
// Context context;
// context.set("key1",  "value1");
// std::string a = context.get<std::string>("key1");
// 
// std::string& b = a;
// context.setRef("key2", b);
// std::string& c = context.getRef<std::string>("key2");
// 
// const std::string& b1 = a;
// context.setRef("key3", b1);
// const std::string& c1 = context.getConstRef<std::string>("key3");
// 
// context.set("num1", 12);
// int num1 = context.get<int>("num1");

class Context
{
public:
	typedef std::map<std::string, Poco::Any> ContextMap;


	template<typename T>
	T& get(const std::string& key)
		//		throw(Poco::NotFoundException)
	{
		ContextMap::iterator it = _context.find(key);

		if (it == _context.end())
		{
			throw Poco::NotFoundException(key 
				+ " is not found in the context");
		}

		return Poco::RefAnyCast<T>(it->second);
	}

	template<typename T>
	const T& get(const std::string& key)const
		//		throw(Poco::NotFoundException)
	{
		return getConst<T>(key);
	}

	template<typename T>
	const T& getConst(const std::string& key)const
		//		throw(Poco::NotFoundException)
	{
		ContextMap::const_iterator it = _context.find(key);

		if (it == _context.end())
		{
			throw Poco::NotFoundException(key 
				+ " is not found in the context");
		}

		return Poco::RefAnyCast<T>(it->second);
	}

	bool exists(const std::string& key)const
	{
		return _context.find(key) != _context.end();
	}

	void set(const std::string& key, const char* any)
	{
		set(key, std::string(any));
	}

	void set(const std::string& key, const Poco::Any& any)
	{
		_context[key] = any;
	}

	template<typename T>
	void setRef(const std::string& key, T& any)
	{
		_context[key] = Poco::Any(ref(any));
	}

	template<typename T>
	void setRef(const std::string& key, const T& any)
	{
		_context[key] = Poco::Any(ref(any));
	}


	template<typename T>
	T& getRef(const std::string& key)
	{
		return unwrap(get<reference_wrapper<T> >(key));
	}

	template<typename T>
	const T& getRef(const std::string& key)const
	{
		return getConstRef<T>(key);
	}

	template<typename T>
	const T& getConstRef(const std::string& key)const
	{
		return unwrap(getConst<const_reference_wrapper<T> >(key));
	}


	std::list<std::string> keys()const
	{
		const ContextMap& m = _context;
		ContextMap::const_iterator it;
		std::list<std::string> lst;
		for (it = m.begin(); it != m.end(); ++it)
		{
			lst.push_back(it->first);
		}

		return lst;
	}

	const ContextMap& context()const
	{
		return _context;
	}

private:
	ContextMap _context;
};


#endif // CONTEXT_HEADER
