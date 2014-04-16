/***************************************************************
 * DBConnectInfoInitializer.cpp
 * 系统名  : 城市一卡通系统
 * 子系统名: 结算子系统(B)_通用库
 * 更改日期      姓名           摘要
 * ----------    -----------    --------------------------------
 * 2007/12/20    谢琨			初次开发
 ***************************************************************
 */
#include "Poco/Util/Application.h"
#include "dbi/DBConnectInfoInitializer.h"
#include "Util.h"
// database encrypt add by cf 2012/4/5
//#include "aes.h"  

void DBConnectInfoInitializer::initDBConnectInfo(DBConnectInfo& info) 
throw (BalException) {
	//Util::getTraceLogger()->information("Initializing DataBase Connect Info");

	try {
		string dbName	= 
			Poco::Util::Application::instance().config().getString("dbinfo.dbname");
		string userName = 
			Poco::Util::Application::instance().config().getString("dbinfo.username");
		string password = 
			Poco::Util::Application::instance().config().getString("dbinfo.password");

		//Util::getTraceLogger()->information("oracle password decrypt");
		// database encrypt add by cf 2012/4/5
		//////////////////////////////////////////////////////////////////////////
		/*int outputlen = (password.length() >> 1 )+ 1;
		char* output = new  char[outputlen] ;
		memset(output,0,sizeof(char)*outputlen);
		XEncrypt::AES(1,password.c_str(),Util::getAesKey().c_str(),output);
		password = string(output);
		delete output;*/
		//////////////////////////////////////////////////////////////////////////
		//Util::getTraceLogger()->information("decryption complete");

		info.set(dbName,userName,password);
	} catch (Poco::NotFoundException& e) {
		throw BalException(e.message(),"B000A00101");
	} catch (Poco::SyntaxException& e) {
		throw BalException(e.message(),"B000S00101");
	}
}


