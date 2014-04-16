#ifndef UTIL_H_
#define UTIL_H_

#include "Poco/Logger.h"
#include "Poco/Data/Session.h"
#include <string>
/**
 * 工具类
 * @author  CF
 * @version V1.0
 * @since V1.0
 */

class Util 
{
public:	
	/**
	 * 获取本通道跟踪日志记录器
	 * @return	日志记录器指针
	 */
	static Poco::Logger* getTraceLogger();


	//static Poco::Data::Session* getSession();

	/**
	 * 获取AES的密钥   add by cf 2012/4/5
	 */
	static std::string getAesKey();

	static Poco::Data::Session getSession();

	static std::string UnicodeToUTF8(const std::string& format);

	static std::string UTF8ToUnicode(const std::string& format);

	static std::string ws2s(const std::wstring& ws);

	static std::wstring s2ws(const std::string& s);
};

#endif