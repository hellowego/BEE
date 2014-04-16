/***************************************************************
 * DBConnectInfo.h
 * ������  : ��������������
 * ��������: ����������(B)_������
 * ��������      ����           ����
 * ----------    -----------    --------------------------------
 * 2007/12/10    ����			��������
 ***************************************************************
 */
#ifndef DBCONNECTINFO_H_
#define DBCONNECTINFO_H_

#include <string>

using std::string;

/**
 * ��������������
 * @author  ����
 * @version V2.0.00
 * @since V2.0.00
 */
class DBConnectInfo {
public:
	
	/**
	 * ��������
	 */
	DBConnectInfo();

	/**
	 * ��������
	 * @param dbName	��������
	 * @param userName	������
	 * @param password	����
	 */
	DBConnectInfo(const string& dbName, const string& userName, const string& password, const string& dbkey = "mysql");
	
	/**
	 * ������������
	 * @return ��������
	 */
	const string& getDBName() const;

	/**
	 * ����������
	 * @return ������
	 */
	const string& getUserName() const;
	
	/**
	 * ��������
	 * @return ����
	 */
	const string& getPassword() const;
	
	/**
	 * ������
	 * @param ��������
	 * @param ������
	 * @param ����
	 */
	void set(const string& dbName, const string& userName, const string& password, const string& dbkey = "mysql");

	string getConnString();
private:
	/**
	 * ��������
	 */
	std::string _dbName;

	/**
	 * ������
	 */
	string _userName;

	/**
	 * ����
	 */
	string _password;

	string _key;
};

#endif /*DBCONNECTINFO_H_*/
