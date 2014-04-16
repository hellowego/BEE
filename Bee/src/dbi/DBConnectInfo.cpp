/***************************************************************
 * DBConnectInfo.cpp
 * ������  : ��������������
 * ��������: ����������(B)_������
 * ��������      ����           ����
 * ----------    -----------    --------------------------------
 * 2007/12/20    ����			��������
 ***************************************************************
 */
#include "dbi/DBConnectInfo.h"
#include "Poco/Format.h"


DBConnectInfo::DBConnectInfo() {
}

DBConnectInfo::DBConnectInfo(const string& dbName, 
							 const string& userName,
							 const string& password,
							 const string& dbkey)
//: _key(dbkey),_dbName(dbName), _userName(userName), _password(password)
{
	_key = dbkey;
	_dbName = dbName;
	_userName = userName;
	_password = password;
}

void DBConnectInfo::set(const string& dbName, 
						const string& userName, const string& password, const string& dbkey) {
	_key = dbkey;
	_dbName = dbName;
	_userName = userName;
	_password = password;
}

const string& DBConnectInfo::getDBName() const {
	return _dbName;
}

const string& DBConnectInfo::getUserName() const {
	return _userName;
}

const string& DBConnectInfo::getPassword() const {
	return _password;
}

string DBConnectInfo::getConnString()
{
	return Poco::format("user=%s;password=%s;db=%s;"
		"compress=true;auto-reconnect=true", _userName, _password, _dbName);
}
