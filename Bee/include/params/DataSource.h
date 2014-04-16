#ifndef DATASOURCE_H_
#define DATASOURCE_H_
#include <string>
#include "Poco/Data/TypeHandler.h"
#include "Poco/DateTime.h"

class DataSource
{
public:
	DataSource();
	
	DataSource(std::string sourceNo, std::string sourceName, std::string& hostName, std::string& url);
	

	~DataSource();
	

	std::string getSourceNo()const {return _sourceNo;}
	std::string getSourceName()const {return _sourceName;}
	std::string getHostName()const {return _hostName;}
	std::string getUrl()const {return _url;}
	std::string getState()const {return _state;}
	Poco::DateTime getDt()const {return _dt;}

	void setSourceNo(std::string& sourceNo) {_sourceNo = sourceNo;}
	void setSourceName(std::string& sourceName) {_sourceName = sourceName;}
	void setHostName(std::string& hostName) {_hostName = hostName;}
	void setUrl(std::string& url) {_url = url;}
	void setState(std::string& state) {_state = state;}
	void setDt(Poco::DateTime& dt) {_dt = dt;}


	
	
	

protected:
private:
	std::string _sourceNo;
	std::string _sourceName;
	std::string _hostName;
	std::string _url;	
	std::string _state;
	Poco::DateTime _dt;
};

namespace Poco {
	namespace Data {

		template <>
		class TypeHandler<DataSource>
		{
		public:
			static void bind(std::size_t pos, const DataSource& obj, AbstractBinder::Ptr pBinder, AbstractBinder::Direction dir)
			//static void bind(std::size_t pos, const DataSource& obj, AbstractBinder* pBinder, AbstractBinder::Direction dir)
			{
				// the table is defined as DataSource (_sourceNo VARCHAR(30), _sourceName VARCHAR, _hostName VARCHAR, _url INTEGER(3))
				poco_assert_dbg (!pBinder.isNull());
				TypeHandler<std::string>::bind(pos++, obj.getSourceNo(), pBinder, dir);
				TypeHandler<std::string>::bind(pos++, obj.getSourceName(), pBinder, dir);
				TypeHandler<std::string>::bind(pos++, obj.getHostName(), pBinder, dir);
				TypeHandler<std::string>::bind(pos++, obj.getUrl(), pBinder, dir);
				TypeHandler<std::string>::bind(pos++, obj.getState(), pBinder, dir);
				TypeHandler<Poco::DateTime>::bind(pos++, obj.getDt(), pBinder, dir);
			}


			static void prepare(std::size_t pos, const DataSource& obj, AbstractPreparator::Ptr pPreparator)
			{
				// the table is defined as DataSource (_sourceNo VARCHAR(30), _sourceName VARCHAR, _hostName VARCHAR, _url INTEGER(3))
				poco_assert_dbg (!pPreparator.isNull());
				TypeHandler<std::string>::prepare(pos++, obj.getSourceNo(), pPreparator);
				TypeHandler<std::string>::prepare(pos++, obj.getSourceName(), pPreparator);
				TypeHandler<std::string>::prepare(pos++, obj.getHostName(), pPreparator);
				TypeHandler<std::string>::prepare(pos++, obj.getUrl(), pPreparator);
				TypeHandler<std::string>::prepare(pos++, obj.getState(), pPreparator);
				TypeHandler<Poco::DateTime>::prepare(pos++, obj.getDt(), pPreparator);

			}

			static std::size_t size()
			{
				return 6;
			}

			static void extract(std::size_t pos, DataSource& obj, const DataSource& defVal, AbstractExtractor::Ptr pExt)
			//static void extract(std::size_t pos, DataSource& obj, const DataSource& defVal, AbstractExtractor* pExt)
			{
				poco_assert_dbg (!pExt.isNull());
				std::string sourceNo;
				std::string sourceName;
				std::string hostName;
				std::string url;	
				std::string state;
				Poco::DateTime dt;

				TypeHandler<std::string>::extract(pos++, sourceNo, defVal.getSourceNo(), pExt);
				TypeHandler<std::string>::extract(pos++, sourceName, defVal.getSourceName(), pExt);
				TypeHandler<std::string>::extract(pos++, hostName, defVal.getHostName(), pExt);
				TypeHandler<std::string>::extract(pos++, url, defVal.getUrl(), pExt);
				TypeHandler<std::string>::extract(pos++, state, defVal.getState(), pExt);
				TypeHandler<Poco::DateTime>::extract(pos++, dt, defVal.getDt(), pExt);
				obj.setSourceNo(sourceNo);
				obj.setSourceName(sourceName);
				obj.setHostName(hostName);
				obj.setUrl(url);
				obj.setState(state);
				obj.setDt(dt);
				
			}

		private:
			TypeHandler();
			~TypeHandler();
			TypeHandler(const TypeHandler&);
			TypeHandler& operator=(const TypeHandler&);
		};

	} } // namespace Poco::Data


#endif