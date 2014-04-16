#include "Util.h"
#include "dbi/MysqlSessionFactory.h"
#include "Poco/UnicodeConverter.h"
Poco::Logger* Util::getTraceLogger() 
{
	//const string& TRACE_LOGGER_NAME = "trace_";
	return &Poco::Logger::get("trace_bee");
}



std::string Util::getAesKey()
{
	return "11111111111111111111111111111111";
}

Poco::Data::Session Util::getSession()
{

	return MysqlSessionFactory::instance().getSession();
}


std::string Util::UnicodeToUTF8(const std::string& format)
{
	std::string nformat;
	std::wstring wformat = s2ws(format);
	Poco::UnicodeConverter::toUTF8(wformat,nformat);
	return nformat;
}

std::string Util::UTF8ToUnicode(const std::string& format)
{
	std::string nformat;
	std::wstring wformat;
	Poco::UnicodeConverter::toUTF16(format, wformat);
	nformat = ws2s(wformat);
	return nformat;
}



std::string Util::ws2s(const std::wstring& ws)
{
	std::string curLocale = setlocale(LC_ALL, NULL);        // curLocale = "C";
	setlocale(LC_ALL, "chs");
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = 2 * ws.size() + 1;
	char *_Dest = new char[_Dsize];
	memset(_Dest,0,_Dsize);
	wcstombs(_Dest,_Source,_Dsize);
	std::string result = _Dest;
	delete []_Dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}

std::wstring Util::s2ws(const std::string& s)
{
	setlocale(LC_ALL, "chs"); 
	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1;
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest,_Source,_Dsize);
	std::wstring result = _Dest;
	delete []_Dest;
	setlocale(LC_ALL, "C");
	return result;
}